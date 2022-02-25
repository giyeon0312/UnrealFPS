// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Blueprint/UserWidget.h"
#include "QuestClearListWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UQuestClearListWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UTextBlock* m_Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UTextBlock* m_Dest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UTextBlock* m_Count;
public:
	void SetType(const FString& Type)
	{
		m_Type->SetText(FText::FromString(Type));
	}

	void SetDesc(const FString& Desc)
	{
		m_Dest->SetText(FText::FromString(Desc));
	}

	void SetCount(int32 Count, int32 CountMax)
	{
		m_Count->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), Count, CountMax)));
	}

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);

};
