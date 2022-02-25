// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemDesc.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UInventoryItemDesc : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UListView* m_OptionList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UTextBlock* m_ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UTextBlock* m_ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UTextBlock* m_ItemDesc;

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetItemInfo(const FString& Name, EItemType Type, const FString& Desc,
		const TArray<FItemOptionInfo>* OptionArray);
};
