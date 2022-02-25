// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTileItem.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UInventoryTileItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UImage* m_Icon;

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);
};
