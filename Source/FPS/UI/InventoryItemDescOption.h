// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemDescOption.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UInventoryItemDescOption : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UTextBlock* m_Text;

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);
	
};
