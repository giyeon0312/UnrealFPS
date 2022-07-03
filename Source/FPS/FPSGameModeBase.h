// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameInfo.h"
#include "UI/MainWidget.h"
#include "UI/MouseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AFPSGameModeBase();

protected:
	TSubclassOf<UMainWidget>		m_MainWidgetClass;
	UMainWidget* m_MainWidget;

	TSubclassOf<UMouseWidget>		m_MouseWidgetClass;
	UMouseWidget* m_MouseWidget;

public:
	UMainWidget* GetMainWidget()
	{
		return m_MainWidget;
	}

	UMouseWidget* GetMouseWidget()
	{
		return m_MouseWidget;
	}

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void BeginPlay() override;
};
