// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "DAnimNotify_SendGamePlayEvent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_DL_API UDAnimNotify_SendGamePlayEvent : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UDAnimNotify_SendGamePlayEvent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//Notify가 왔을 때 함수 호출
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;
};
