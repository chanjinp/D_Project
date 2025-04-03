// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attribute/DAttributeSet.h"
#include "DPlayerSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_DL_API UDPlayerSet : public UDAttributeSet
{
	GENERATED_BODY()

public:
	UDPlayerSet();

public:
	//마나는 플레이어만 가지고 있음
	ATTRIBUTE_ACCESSORS(ThisClass, Mana);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMana;
	
};
