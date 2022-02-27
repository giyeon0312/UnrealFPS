// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "UI/CharacterSelectWidget.h"
#include "GameFramework/GameModeBase.h"
#include "CharacterSelectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ACharacterSelectGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACharacterSelectGameMode();

protected:
	TSubclassOf<UCharacterSelectWidget>	m_CharacterSelectWidgetClass;
	UCharacterSelectWidget* m_CharacterSelectWidget;

public:
	UCharacterSelectWidget* GetCharacterSelectWidget()
	{
		return m_CharacterSelectWidget;
	}

protected:
	virtual void BeginPlay() override;
};
