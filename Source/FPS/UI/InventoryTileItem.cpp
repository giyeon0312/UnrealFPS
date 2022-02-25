// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTileItem.h"
#include "InventoryListItemData.h"

void UInventoryTileItem::NativeConstruct()
{
	Super::NativeConstruct();

	m_Icon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
}

void UInventoryTileItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryTileItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventoryListItemData* Item = Cast<UInventoryListItemData>(ListItemObject);

	if (Item)
	{
		m_Icon->SetBrushFromTexture(Item->GetIconTexture());
	}
}
