// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/DPlayer.h"
#include "Character/DCharacter.h"

ADPlayerController::ADPlayerController()
{
	bShowMouseCursor = true; // 마우스 커서를 보여준다
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.0f;
}

void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Input Mapping Context 추가
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0); //(MappingContext, 우선순위 0)
	}

	DPlayer = Cast<ADPlayer>(GetCharacter()); //자기 자신 캐싱
}

void ADPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TickCursorTrace();
}

void ADPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Action Binding
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//Click Action
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ThisClass::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ThisClass::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ThisClass::OnSetDestinationReleased);

		//Touch Action
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ThisClass::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ThisClass::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ThisClass::OnTouchReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADPlayerController::OnInputStarted()
{
	StopMovement(); //이벤트가 시작할 때
	bMousePressed = true;
}

void ADPlayerController::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds(); //누른 시간 체크

	FHitResult Hit;																																	
	bool bHitSuccessful = false;
	//TODO 땅바닥을 누르고 있을 때 충돌 처리를 통해 해당 위치와 나의 위치를 가지고 계산

	if (bIsTouch) // Touch를 했다면
	{
		//ECollisionChannel::ECC_Visibility은 보이는 것을 의미 => 기본적으로 바닥
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, OUT Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);
	}

	if (bHitSuccessful) //표면을 Hit하는데 성공했다면 -> CachedDestination에 Hit의 위치를 저장
	{
		CachedDestination = Hit.Location; //위치 저장 [내가 클릭한 위치]
	}

	//해당 위치로 이동
	if (DPlayer)
	{
		FVector WorldDirection = (CachedDestination - DPlayer->GetActorLocation()).GetSafeNormal(); //(내가 클릭한 위치 - 내 현재 위치)의 정규화
		DPlayer->AddMovementInput(WorldDirection); //나온 방향 벡터로 이동
	}
}

void ADPlayerController::OnSetDestinationReleased()
{
	bMousePressed = false;

	//TODO 임계값과 누른 Trigger 호출되었을 때의 시간을 통해 보다 임계값보다 짧다면 AIController를 통한 길찾기 자동 이동

	if (FollowTime <= ShortPressThreshold) //짧게 눌렀다면?
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination); //AIController를 통해 길찾기
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true); //FXSpawn
		/*
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		this,              // WorldContextObject
		FXCursor,          // NiagaraSystem (이게 파티클 이펙트 에셋)
		CachedDestination, // 위치
		FRotator::ZeroRotator, // 회전
		FVector(1.f),      // 스케일
		true,              // bAutoDestroy
		true,              // bAutoActivate
		ENCPoolMethod::None, // 풀링 방식
		true               // bPreCullCheck
		);
		*/
	}

	FollowTime = 0.f; //누른 시간 초기화
}

void ADPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ADPlayerController::OnTouchReleased()
{
	bIsTouch = true;
	OnSetDestinationReleased();
}

void ADPlayerController::TickCursorTrace()
{
	if (bMousePressed) //마우스를 누르고 있다면?
	{
		return;
	}

	FHitResult CursorHit;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT CursorHit) == false)
	{
		return;
	}

	ADCharacter* LocalHighlightActor = Cast<ADCharacter>(CursorHit.GetActor()); //내가 클릭한 Actor
	if (LocalHighlightActor == nullptr) //마우스로 주시한 것이 없다면?
	{
		if (HighlightActor) //강조된 것이 있다면 -> 강조 해제
		{
			HighlightActor->UnHighlightOn(); //강조 해제
		}
	}
	else
	{
		if (HighlightActor) //주시하면서 강조한다면?
		{
			if (HighlightActor != LocalHighlightActor) //내가 클릭한 Actor와 같지 않다면?
			{
				HighlightActor->UnHighlightOn(); //강조 해제
				LocalHighlightActor->HighlightOn(); //강조
			}
		}
		else //강조한 것이 없다면?
		{
			LocalHighlightActor->HighlightOn(); //강조
		}
	}
	HighlightActor = LocalHighlightActor; //내가 클릭한 Actor
}
