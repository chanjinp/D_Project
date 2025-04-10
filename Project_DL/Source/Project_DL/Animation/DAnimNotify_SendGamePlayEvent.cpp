// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DAnimNotify_SendGamePlayEvent.h"
#include "Character/DCharacter.h"

UDAnimNotify_SendGamePlayEvent::UDAnimNotify_SendGamePlayEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDAnimNotify_SendGamePlayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ADCharacter* LocalCharacter = Cast<ADCharacter>(MeshComp->GetOwner()); //MeshComponent의 주체자 => Return AActor
	if (LocalCharacter)
	{
		//LocalCharacter->HandleGameplayEvent(EventTag);
	}
}
