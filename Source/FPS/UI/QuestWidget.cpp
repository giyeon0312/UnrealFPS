// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestWidget.h"
#include "QuestCategoryData.h"
#include "QuestCategoryWidget.h"
#include "../FPSGameInstance.h"

void UQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	m_Category = Cast<UTreeView>(GetWidgetFromName(TEXT("Category")));
	
	m_CloseButton->OnClicked.AddDynamic(this, &UQuestWidget::CloseButtonClicked);

	m_Category->OnItemClicked().AddUObject(this, &UQuestWidget::ItemClick);
	m_Category->OnItemDoubleClicked().AddUObject(this, &UQuestWidget::ItemDoubleClick);
	m_Category->OnItemIsHoveredChanged().AddUObject(this, &UQuestWidget::ItemHovered);
	//m_Category->OnItemSelectionChanged().AddUObject(this, &UQuestWidget::ItemSelectionChanged);
	m_Category->SetOnGetItemChildren(this, &UQuestWidget::ItemChildren);

	m_PrevSelect = nullptr;

	InitList();
}

void UQuestWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UQuestWidget::InitList()
{
	UFPSGameInstance* GameInst = Cast<UFPSGameInstance>(GetWorld()->GetGameInstance());

	// ù ��° ��Ʈ
	UQuestCategoryData* Category = NewObject<UQuestCategoryData>(this,UQuestCategoryData::StaticClass());

	Category->SetCategory(EQuestCategory::Part1);

	const FQuestTableInfo* Info = GameInst->FindQuestInfo(TEXT("Quest1"));
	Category->CreateChild(Info);
	//m_ProgressQuest.Add(Category->CreateChild(Info));
	m_Category->AddItem(Category);

	// �� ��° ��Ʈ
	Category = NewObject<UQuestCategoryData>(this,UQuestCategoryData::StaticClass());

	Category->SetCategory(EQuestCategory::Part2);

	Info = GameInst->FindQuestInfo(TEXT("Quest2"));
	Category->CreateChild(Info);
	//m_ProgressQuest.Add(Category->CreateChild(Info));

	Info = GameInst->FindQuestInfo(TEXT("Quest4"));
	Category->CreateChild(Info);
	//m_ProgressQuest.Add(Category->CreateChild(Info));
	
	m_Category->AddItem(Category);

	// �� ��° ��Ʈ
	Category = NewObject<UQuestCategoryData>(this,UQuestCategoryData::StaticClass());

	Category->SetCategory(EQuestCategory::Part3);

	Info = GameInst->FindQuestInfo(TEXT("Quest3"));

	Category->CreateChild(Info);
	//m_ProgressQuest.Add(Category->CreateChild(Info));
	m_Category->AddItem(Category);
}


// InitList���� AddItem���� �߰��� �������� 10����� �� �Լ��� ���� 10���� ȣ���� �ȴ�.
// �� �Ŀ� ListEntry�� �Լ����� ���� ȣ���� �Ǵ� ����̴�.
// ������ AddItem�� Category���� �߰����־���.
// �׷��Ƿ� ����� ī�װ����� ������ ���̴�.
void UQuestWidget::ItemChildren(UObject* Item, TArray<UObject*>& ItemArray)
{
	UQuestCategoryData* Data = Cast<UQuestCategoryData>(Item);

	if (Data)
		ItemArray = Data->GetChildArray();

}

void UQuestWidget::CloseButtonClicked()
{
	SetVisibility(ESlateVisibility::Collapsed);
}


void UQuestWidget::ItemClick(UObject* Item)
{

}

void UQuestWidget::ItemDoubleClick(UObject* Item)
{

}

void UQuestWidget::ItemHovered(UObject* Item, bool IsHovered)
{
	if (m_PrevSelect != Item)
	{
		UQuestCategoryData* Data = Cast<UQuestCategoryData>(Item);

		EListSelect IsSelected = IsHovered ? EListSelect::MouseOn : EListSelect::None;

		Data->GetLinkWidget()->SetListSelect(IsSelected);
	}
}

void UQuestWidget::ItemSelectionChanged(UObject* Item, bool IsSelection)
{
	if (m_PrevSelect == Item)
		return;

	if (m_PrevSelect)
		m_PrevSelect->GetLinkWidget()->SetListSelect(EListSelect::None);

	UQuestCategoryData* Data = Cast<UQuestCategoryData>(Item);

	Data->GetLinkWidget()->SetListSelect(EListSelect::Select);
	m_PrevSelect = Data;
}
