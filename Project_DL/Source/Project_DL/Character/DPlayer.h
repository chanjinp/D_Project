// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DCharacter.h"
#include "DPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_DL_API ADPlayer : public ADCharacter
{
	GENERATED_BODY()

public:
	ADPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilitySystem() override;

	class USpringArmComponent* GetSpringArm() const;
	class UCameraComponent* GetCameraComponent() const;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> CameraComponent;
	
};
