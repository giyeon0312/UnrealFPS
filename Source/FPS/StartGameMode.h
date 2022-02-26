// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "UI/StartWidget.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AStartGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AStartGameMode();

protected:
	TSubclassOf<UStartWidget>	m_StartWidgetClass;
	UStartWidget* m_StartWidget;

public:
	UStartWidget* GetStartWidget()
	{
		return m_StartWidget;
	}

protected:
	virtual void BeginPlay() override;
};
