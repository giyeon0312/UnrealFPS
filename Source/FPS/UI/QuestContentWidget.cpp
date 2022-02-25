// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestWidget.h"
//#include "QuestCategoryData.h"
#include "QuestCategoryWidget.h"
#include "../FPSGameInstance.h"
#include "QuestContentWidget.h"

void UQuestContentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_QuestOptionList = Cast<UListView>(GetWidgetFromName(TEXT("ClearList")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
	m_DescText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Desc")));


	//m_GoldText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GoldText")));

	/*m_QuestOptionList->OnItemClicked().AddUObject(this, &UQuestContentWidget::ItemClick);
	m_QuestOptionList->OnItemDoubleClicked().AddUObject(this, &UQuestContentWidget::ItemDoubleClick);
	m_QuestOptionList->OnItemIsHoveredChanged().AddUObject(this, &UQuestContentWidget::ItemHoveredChange);
	m_QuestOptionList->OnItemSelectionChanged().AddUObject(this, &UQuestContentWidget::ItemSelectionChange);*/
}

void UQuestContentWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UQuestContentWidget::ClearOptionList()
{
	m_QuestOptionList->ClearListItems();
}

void UQuestContentWidget::AddOptionList(EQuestType Type, const FString& Desc, int32 Count, int32 CountMax)
{
	/*UQuestClearListData* Item = NewObject<UQuestClearListData>(this,
		UQuestClearListData::StaticClass());

	Item->SetClearType(Type);
	Item->SetClearDesc(Desc);
	Item->SetClearCountMax(CountMax);
	Item->AddCount(Count);

	m_QuestOptionList->AddItem(Item);*/
}

void UQuestContentWidget::CloseButtonClicked()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UQuestContentWidget::ItemClick(UObject* Item)
{
}

void UQuestContentWidget::ItemDoubleClick(UObject* Item)
{
}

void UQuestContentWidget::ItemHovered(UObject* Item, bool IsHovered)
{
}

void UQuestContentWidget::ItemSelectionChanged(UObject* Item)
{
}


