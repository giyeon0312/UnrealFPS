// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStateHUD.h"


void UCharacterStateHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	m_MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
}

void UCharacterStateHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCharacterStateHUD::SetHPPercent(float Percent)
{
	if (m_HPBar)
	{

		PrintViewport(2.f, FColor::Red, TEXT("YesHP"));
		m_HPBar->SetPercent(Percent);
	}
	else
		PrintViewport(2.f, FColor::Red, TEXT("NoHP"));
}

void UCharacterStateHUD::SetMPPercent(float Percent)
{
	m_MPBar->SetPercent(Percent);
}

void UCharacterStateHUD::SetNameText(const FString& NameText)
{
	m_NameText->SetText(FText::FromString(NameText));//String으로부터 문자열을 받아와서 Text를 만들어내는 방식
}
