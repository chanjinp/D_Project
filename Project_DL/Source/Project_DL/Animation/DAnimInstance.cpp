// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimInstance.h"
#include "Character/DCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UDAnimInstance::UDAnimInstance(const FObjectInitializer& ObjectInitializer)
{
}

void UDAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ADCharacter>(TryGetPawnOwner()); //내가	소유하고 있는 Pawn을 캐릭터로 캐스팅

	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement(); //캐릭터의 Movement Component를 가져옴
	}
}

void UDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
	{
		return;
	}
	if (MovementComponent == nullptr)
	{
		return;
	}

	Velocity = MovementComponent->Velocity; //캐릭터의 속도
	//GroundSpeed = Velocity.Size(); //속도의 크기 -> 제곱근 연산이 필요
	GroundSpeed = Velocity.SizeSquared();

	bShouldMove = (GroundSpeed > 9.f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);
	bIsFalling = MovementComponent->IsFalling();
}
