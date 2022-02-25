// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "FPSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UFPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UDataTable* m_MonsterInfoTable;

	UPROPERTY()
	UDataTable* m_PlayerInfoTable;

	UPROPERTY()
	UDataTable* m_ItemInfoTable;

	UPROPERTY()
	UDataTable* m_QuestInfoTable;

public:
	UFPSGameInstance();

public:
	const FMonsterTableInfo* FindMonsterInfo(const FString& Name);
	const FPlayerTableInfo* FindPlayerInfo(const FString& Name);
	const FItemTableInfo* FindItemInfo(const FString& Name);
	const FQuestTableInfo* FindQuestInfo(const FString& Name);
};
