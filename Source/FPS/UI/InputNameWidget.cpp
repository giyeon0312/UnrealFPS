// Fill out your copyright notice in the Description page of Project Settings.


#include "InputNameWidget.h"

void UInputNameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_InputName = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("InputName")));
}

void UInputNameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
