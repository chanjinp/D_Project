// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DHighlightInterface.generated.h"

//강조하기 위한 인터페이스
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDHighlightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_DL_API IDHighlightInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// =0; //순수 가상함수로 선언하여 이 인터페이스를 상속받는 클래스에서 반드시 구현해야 한다는 것을 의미
	virtual void HighlightOn() = 0; //강조하기
	virtual void UnHighlightOn() = 0; //강조 해제하기
};
