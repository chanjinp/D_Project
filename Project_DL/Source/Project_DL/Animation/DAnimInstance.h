// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_DL_API UDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDAnimInstance(const FObjectInitializer& ObjectInitializer);
	
public:
	//Begin처럼 초기화 함수
	virtual void NativeInitializeAnimation() override;
	//매 프레임 별 업데이트 해주는 함수
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	//캐릭터
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class ADCharacter> Character;
	//무브먼트
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;

protected:
	//각각의 상태
	UPROPERTY(BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling = false;
};
