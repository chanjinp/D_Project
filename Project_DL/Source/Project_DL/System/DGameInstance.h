// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_DL_API UDGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void Init() override;
	virtual void Shutdown() override;
	
};
