// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseWidget.h"

void UMouseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_MouseImage = Cast<UImage>(GetWidgetFromName(TEXT("Mouse")));
}

void UMouseWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMouseWidget::ChangeMouse(EMouseState State)
{
	m_MouseImage->SetBrushFromMaterial(m_MouseMtrlArray[(int)State]);
}
