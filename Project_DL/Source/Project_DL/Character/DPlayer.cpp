// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADPlayer::ADPlayer()
{
	//카메라 시점 고정
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//클릭 시 캐릭터가 클릭한 방향으로 보게끔
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//자연스레 넘어가게 회전할 때 속도를 지정
	//FRotator(x축, z축, y축) => 캐릭터가 좌 우 회전할 때 초당 최대 640도 속도로 회전
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent()); //캡슐컴포넌트에 SpringArm을 붙여준다.
	
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));
	SpringArm->TargetArmLength = 800.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->bUsePawnControlRotation = false;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
}

void ADPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ADPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ADPlayer::InitAbilitySystem()
{
	Super::InitAbilitySystem();
}

void ADPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
