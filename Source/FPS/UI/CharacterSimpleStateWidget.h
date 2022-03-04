// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSimpleStateWidget.generated.h"

DECLARE_DELEGATE(FNameSetDelegate)

UCLASS()
class FPS_API UCharacterSimpleStateWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UTextBlock* m_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UProgressBar* m_HPBar;

	FNameSetDelegate	m_NameSetDelegate;

public:
	void SetCharacterName(const FString& Name)
	{
		m_Name->SetText(FText::FromString(Name));
	}

	void SetHPPercent(float Percent)
	{
		m_HPBar->SetPercent(Percent);
	}

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	template <typename T>
	void SetNameSetDelegate(T* Obj, void(T::* Func)())
	{
		m_NameSetDelegate.BindUObject(Obj, Func);
	}
};
