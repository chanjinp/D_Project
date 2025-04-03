// Fill out your copyright notice in the Description page of Project Settings.


#include "System/DGameInstance.h"

UDGameInstance::UDGameInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UDGameInstance::Init()
{
	Super::Init(); //실제 게임 플레이를 실행할 때 호출
}

void UDGameInstance::Shutdown()
{
	Super::Shutdown(); //실제 게임 플레이를 중단했을 때 호출
}
