// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UButton* m_CloseButton;

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	//UFUNCTION() //��������Ʈ�� �Լ��� ����� ���̹Ƿ�
	//void ItemClick(UObject* Item);

	//UFUNCTION()
	//void ItemDoubleClick(UObject* Item);

	//UFUNCTION()
	//void ItemHovered(UObject* Item, bool IsHobered);

	//UFUNCTION()
	//void ItemSelectionChange(UObject* Item, bool IsSelection);
	
	void SetGold(int32 Gold)
	{
		//m_GoldText->SetText(FText::FromString(Fstring::Printf("%d", Gold)));
	}

public:
	UFUNCTION()
	void CloseButtonClicked();
};
