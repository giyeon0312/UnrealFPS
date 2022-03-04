// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/EditableTextBox.h"
#include "Blueprint/UserWidget.h"
#include "InputNameWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UInputNameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UEditableTextBox* m_InputName;

public:
	FString GetNameText()
	{
		return m_InputName->GetText().ToString();
	}

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

};
