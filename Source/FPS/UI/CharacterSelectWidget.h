// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
//#include "InputNameWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UButton* m_StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UButton* m_BackButton;

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void StartEnable(bool Enable);

public:
	UFUNCTION()
	void StartClick();

	UFUNCTION()
	void BackClick();
};
