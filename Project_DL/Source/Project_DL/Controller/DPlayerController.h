// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class PROJECT_DL_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold; //짧게 눌렀을 때의 임계값

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor; //커서 파티클

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* MappingContext; //Mapping Context

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SetDestinationClickAction; //Click Action

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SetDestinationTouchAction; //Touch Action

protected:
	// :1의 의미는 32비트 중 1비트만 내가 사용하겠다
	// 나머지 비트의 경우에는 같은 형식으로 사용하고자 하는 비트를 지정해서 사용 가능
	// ex: uint32 Test : 21 => 21비트만큼 해당 변수를 사용하겠다라는 의미
	// 왜 uint32로 했는가? => CPU 처리 효율성 때문 => 왜? 한 번에 처리하는 레지스터 크기가 정해져 있는데 그게 보통 32비트이기 때문
	uint32 bMoveToMouseCursor : 1;

	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;

	virtual void BeginPlay();
	virtual void PlayerTick(float DeltaTime) override;

	//Input handlers for SetDestination action
	//Action Event에 따른 콜백 함수들
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

private:
	//몬스터 위에 내가 마우스를 가져가 대고 있는가?
	void TickCursorTrace();

private:
	FVector CachedDestination; //기존 내 위치 저장

	bool bIsTouch; //터치했는가?
	float FollowTime; //얼마나 누르고 있었는가?
	bool bMousePressed; //마우스 클릭했는가?

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class ADCharacter> TargetActor; //내가 클릭한 Actor

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class ADCharacter> HighlightActor; //내가 강조할 Actor

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class ADPlayer> DPlayer;
};
