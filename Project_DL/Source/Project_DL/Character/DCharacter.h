// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "DHighlightInterface.h"
#include "DCharacter.generated.h"

UCLASS()
class PROJECT_DL_API ADCharacter : public ACharacter, public IAbilitySystemInterface, public IDHighlightInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void OnDamaged(int32 Damage, TObjectPtr<ADCharacter> Attacker);
	virtual void OnDead(TObjectPtr<ADCharacter> Attacker);

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void InitAbilitySystem();

protected:
	//스킬
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UDAbilitySystemComponent> AbilitySystemComponent;

	//스탯
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UDAttributeSet> AttributeSet;


public:
	virtual void HighlightOn() override;
	virtual void UnHighlightOn() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighed = false; //강조 여부
};
