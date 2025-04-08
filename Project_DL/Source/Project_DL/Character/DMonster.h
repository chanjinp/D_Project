// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DCharacter.h"
#include "DMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_DL_API ADMonster : public ADCharacter
{
	GENERATED_BODY()

public:
	ADMonster();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
