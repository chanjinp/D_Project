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
	//캐릭터가 특정 평면에서만 가능하도록
	GetCharacterMovement()->bConstrainToPlane = true; //즉, Y축 이동이 불가
	//게임 시작 시 캐릭터를 평면에 정렬되도록 -> 평면이 아니라면 자동으로 평면 위치에 정렬
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent()); //캡슐컴포넌트에 SpringArm을 붙여준다.
	
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));
	SpringArm->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	SpringArm->TargetArmLength = 700.f;
	SpringArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->bUsePawnControlRotation = false;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	//Tick 함수가 실행되게끔
	PrimaryActorTick.bCanEverTick = true;
	//시작 시에 Tick 함수가 실행되게끔
	PrimaryActorTick.bStartWithTickEnabled = true;
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

USpringArmComponent* ADPlayer::GetSpringArm() const
{
	return SpringArm.Get();
}

UCameraComponent* ADPlayer::GetCameraComponent() const
{
	return CameraComponent.Get();
}

void ADPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
