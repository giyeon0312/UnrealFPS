// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemDesc.h"
#include "InventoryItemDescData.h"

void UInventoryItemDesc::NativeConstruct()
{
	Super::NativeConstruct();

	m_OptionList = Cast<UListView>(GetWidgetFromName(TEXT("OptionList")));
	m_ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	m_ItemDesc = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescText")));
	m_ItemType = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemType")));
}

void UInventoryItemDesc::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryItemDesc::SetItemInfo(const FString& Name, EItemType Type,
	const FString& Desc,
	const TArray<FItemOptionInfo>* OptionArray)
{
	m_ItemName->SetText(FText::FromString(Name));
	m_ItemDesc->SetText(FText::FromString(Desc));

	switch (Type)
	{
	case EItemType::Weapon:
		m_ItemType->SetText(FText::FromString(TEXT("무기")));
		break;
	case EItemType::Armor:
		m_ItemType->SetText(FText::FromString(TEXT("방어구")));
		break;
	case EItemType::HPPotion:
		m_ItemType->SetText(FText::FromString(TEXT("체력포션")));
		break;
	case EItemType::MPPotion:
		m_ItemType->SetText(FText::FromString(TEXT("마나포션")));
		break;
	}

	m_OptionList->ClearListItems();

	for (auto& Option : *OptionArray)
	{
		UInventoryItemDescData* Item = NewObject<UInventoryItemDescData>(this,
			UInventoryItemDescData::StaticClass());

		Item->SetItemOption(Option);

		m_OptionList->AddItem(Item);
	}
}
