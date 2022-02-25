// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "QuestContentWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UQuestContentWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UListView* m_QuestOptionList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UTextBlock* m_NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UTextBlock* m_DescText;

public:
	void SetQuestName(const FString& QuestName)
	{
		m_NameText->SetText(FText::FromString(QuestName));
	}

	void SetQuestDesc(const FString& QuestDesc)
	{
		m_DescText->SetText(FText::FromString(QuestDesc));
	}

	void ClearOptionList();
	void AddOptionList(EQuestType Type, const FString& Desc, int32 Count, int32 CountMax);

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
	void InitList();

public:
	UFUNCTION()
	void CloseButtonClicked();

public:
	UFUNCTION() //델리게이트용 함수로 사용할 것이므로
	void ItemClick(UObject* Item);

	UFUNCTION()
	void ItemDoubleClick(UObject* Item);

	UFUNCTION()
	void ItemHovered(UObject* Item, bool IsHobered);

	UFUNCTION()
	void ItemSelectionChanged(UObject* Item);
};
