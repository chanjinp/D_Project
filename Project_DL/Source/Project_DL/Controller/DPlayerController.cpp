// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
}

void ADPlayerController::OnSetDestinationTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds(); //누른 시간 체크

	FHitResult Hit;
	bool bHitSuccessful = false;
	//TODO 땅바닥을 누르고 있을 때 충돌 처리를 통해 해당 위치와 나의 위치를 가지고 계산
}

void ADPlayerController::OnSetDestinationReleased()
{
	//TODO 임계값과 누른 Trigger 호출되었을 때의 시간을 통해 보다 임계값보다 짧다면 AIController를 통한 길찾기 자동 이동
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
