// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestClearListWidget.h"
//#include "QuestClearListData.h"

void UQuestClearListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_Type = Cast<UTextBlock>(GetWidgetFromName(TEXT("Type")));
	m_Dest = Cast<UTextBlock>(GetWidgetFromName(TEXT("Dest")));
	m_Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("Count")));
}

void UQuestClearListWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UQuestClearListWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	/*UQuestClearListData* Item = Cast<UQuestClearListData>(ListItemObject);

	if (Item)
	{
		SetType(Item->GetTypeName());
		SetDesc(Item->GetClearDesc());
		SetCount(Item->GetCount(), Item->GetCountMax());
	}*/
}


