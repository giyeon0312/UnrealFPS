// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestCategoryWidget.h"

void UQuestCategoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
	m_Selection = Cast<UImage>(GetWidgetFromName(TEXT("Selection")));

	m_Select = EListSelect::None;
}

void UQuestCategoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UQuestCategoryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UQuestCategoryData* Item = Cast< UQuestCategoryData>(ListItemObject);

	if (Item)
	{
		Item->SetLinkWidget(this);

		if (Item->GetTreeLevel() == 0)
		{
			FString	Category;

			switch (Item->GetCategory())
			{
			case EQuestCategory::Part1:
				Category = TEXT("Part1");
				break;
			case EQuestCategory::Part2:
				Category = TEXT("Part2");
				break;
			case EQuestCategory::Part3:
				Category = TEXT("Part3");
				break;
			}

			m_Name->SetText(FText::FromString(Category));
		}
		else
		{ 
			m_Name->SetText(FText::FromString(Item->GetQuestName()));
		}

		// TreeLevel에 따라서 기존 부모의 +1레벨에 들어가게 했으므로 위치도 다르게 잡아준다.
		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(m_Name->Slot);	// Slot은 전역변수

		if (PanelSlot)
			PanelSlot->SetPosition(FVector2D(Item->GetTreeLevel() * 30.f, 0.f));
		
		PanelSlot = Cast<UCanvasPanelSlot>(m_Selection->Slot);	

		if (PanelSlot)
			PanelSlot->SetPosition(FVector2D(Item->GetTreeLevel() * 30.f, 0.f));
	}
}
