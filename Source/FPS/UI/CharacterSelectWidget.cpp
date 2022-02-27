// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"


void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*m_StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	m_BackButton = Cast<UButton>(GetWidgetFromName(TEXT("BackButton")));
	m_InputName = Cast<UInputNameWidget>(GetWidgetFromName(TEXT("UI_InputName")));

	m_StartButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::StartClick);
	m_BackButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::BackClick);*/
}

void UCharacterSelectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
//
//void UCharacterSelectWidget::StartEnable(bool Enable)
//{
//	m_StartButton->SetIsEnabled(Enable);
//}
//
//void UCharacterSelectWidget::StartClick()
//{
//	UFPSGameInstance* GameInst = Cast<UFPSGameInstance>(GetWorld()->GetGameInstance());
//
//	if (GameInst)
//		GameInst->SetSelectName(m_InputName->GetNameText());
//
//	UGameplayStatics::OpenLevel(GetWorld(),
//		TEXT("Main"));
//}
//
//void UCharacterSelectWidget::BackClick()
//{
//	UGameplayStatics::OpenLevel(GetWorld(),
//		TEXT("Start"));
//}


