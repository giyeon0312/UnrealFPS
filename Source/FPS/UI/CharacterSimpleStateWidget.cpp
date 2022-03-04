// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSimpleStateWidget.h"

void UCharacterSimpleStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));

	if (m_NameSetDelegate.IsBound())
		m_NameSetDelegate.Execute();
}

void UCharacterSimpleStateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
