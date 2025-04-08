// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DMonster.h"

ADMonster::ADMonster()
{
	//Tick 함수가 실행되게끔
	PrimaryActorTick.bCanEverTick = true;
	//시작 시에 Tick 함수가 실행되게끔
	PrimaryActorTick.bStartWithTickEnabled = true;

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
}

void ADMonster::BeginPlay()
{
	Super::BeginPlay();
}

void ADMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
