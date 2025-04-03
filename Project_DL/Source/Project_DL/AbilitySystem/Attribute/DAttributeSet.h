// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DAttributeSet.generated.h"

/**
 *  상태 관리 클래스
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)            \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)  \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)                \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)                \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class PROJECT_DL_API UDAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UDAttributeSet();

public:
    ATTRIBUTE_ACCESSORS(ThisClass, Health);
    ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);
    ATTRIBUTE_ACCESSORS(ThisClass, BaseDamage);
    ATTRIBUTE_ACCESSORS(ThisClass, BaseDefense);

private:
    //AllowPrivateAccess -> Private 접근 제한자를 가지고 있음에도 블루프린트에서 사용할 때 접근 가능하도록
    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData Health; //float로 관리

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData MaxHealth;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData BaseDamage;

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    FGameplayAttributeData BaseDefense;
};
