// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DCharacter.h"
#include "AbilitySystem/DAbilitySystemComponent.h"
#include "AbilitySystem/Attribute/DAttributeSet.h"

// Sets default values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADCharacter::OnDamaged(int32 Damage, TObjectPtr<ADCharacter> Attacker)
{
}

void ADCharacter::OnDead(TObjectPtr<ADCharacter> Attacker)
{
}

UAbilitySystemComponent* ADCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ADCharacter::InitAbilitySystem()
{
}

