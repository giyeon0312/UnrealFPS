// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemDescOption.h"
#include "InventoryItemDescData.h"

void UInventoryItemDescOption::NativeConstruct()
{
	Super::NativeConstruct();

	m_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("Option")));
}

void UInventoryItemDescOption::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryItemDescOption::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventoryItemDescData* Item = Cast<UInventoryItemDescData>(ListItemObject);

	if (Item)
	{
		m_Text->SetText(FText::FromString(FString::Printf(TEXT("%s : %d"), *Item->GetItemName(), Item->GetOption())));
	}
}
