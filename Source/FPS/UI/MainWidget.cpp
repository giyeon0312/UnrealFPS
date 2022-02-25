// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_CharacterStateHUD = Cast<UCharacterStateHUD>(GetWidgetFromName(TEXT("UI_CharacterState")));
	m_Inventory = Cast<UInventoryWidget>(GetWidgetFromName(TEXT("UI_Inventory")));
	m_Quest = Cast<UQuestWidget>(GetWidgetFromName(TEXT("UI_Quest")));
	m_InventoryButton = Cast<UButton>(GetWidgetFromName(TEXT("InventoryButton")));
	m_SkillButton = Cast<UButton>(GetWidgetFromName(TEXT("SkillButton")));
	m_QuestButton = Cast<UButton>(GetWidgetFromName(TEXT("QuestButton")));
	m_OptionButton = Cast<UButton>(GetWidgetFromName(TEXT("OptionButton")));

	m_InventoryButton->OnClicked.AddDynamic(this, &UMainWidget::InventoryButtonClick);
	m_SkillButton->OnClicked.AddDynamic(this, &UMainWidget::SkillButtonClick);
	m_OptionButton->OnClicked.AddDynamic(this, &UMainWidget::OptionButtonClick);
	m_QuestButton->OnClicked.AddDynamic(this, &UMainWidget::QuestButtonClick);
}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

FReply UMainWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	return result;
}

FReply UMainWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return result;
}

FReply UMainWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	FVector2D MousePos = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	//PrintViewport(2.f, FColor::Red, FString::Printf(TEXT("Mouse : %s"), *MousePos.ToString()));

	//PrintViewport(2.f, FColor::Red, FString::Printf(TEXT("Mouse : %s"), *InMouseEvent.GetScreenSpacePosition().ToString()));

	return result;
}

FReply UMainWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseWheel(InGeometry, InMouseEvent);

	return result;
}

void UMainWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void  UMainWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
}

void  UMainWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}

bool  UMainWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool result = Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	
	return result;
}

bool  UMainWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	return result;
}

void  UMainWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

void UMainWidget::InventoryButtonClick()
{
	if (m_Inventory)
	{
		if (m_Inventory->GetVisibility() == ESlateVisibility::Visible)
			m_Inventory->SetVisibility(ESlateVisibility::Collapsed);
		else
			m_Inventory->SetVisibility(ESlateVisibility::Visible);
	}
	else
		PrintViewport(2.f, FColor::Red, TEXT("NO Inventory"));

}


void UMainWidget::SkillButtonClick()
{
}

void UMainWidget::QuestButtonClick()
{
	if (m_Quest)
	{
		if (m_Quest->GetVisibility() == ESlateVisibility::Visible)
			m_Quest->SetVisibility(ESlateVisibility::Collapsed);
		else
			m_Quest->SetVisibility(ESlateVisibility::Visible);
	}
	else
		PrintViewport(2.f, FColor::Red, TEXT("NO Quest"));
}

void UMainWidget::OptionButtonClick()
{
}