// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "QuestCategoryData.h"
#include "QuestCategoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UQuestCategoryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UTextBlock* m_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UImage* m_Selection;

	EListSelect m_Select;

public:
	void SetListSelect(EListSelect Select)
	{
		m_Select = Select;

		FLinearColor	color;

		switch (m_Select)
		{
		case EListSelect::None:
			color.A = 0.f;
			break;
		case EListSelect::MouseOn:
			color.A = 0.3f;
			color.R = 0.2f;
			color.G = 0.2f;
			color.B = 0.2f;
			break;
		case EListSelect::Select:
			color.A = 0.3f;
			color.R = 1.f;
			color.G = 0.7f;
			color.B = 0.f;
			break;
		}

		m_Selection->SetBrushTintColor(color);
	}

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);
};
