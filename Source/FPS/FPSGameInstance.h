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

	EPlayerJob	m_SelectJob;
	FString		m_SelectName;

public:
	UFPSGameInstance();

public:
	void SetSelectJob(EPlayerJob Job)
	{
		m_SelectJob = Job;
	}

	EPlayerJob GetSelectJob()	const
	{
		return m_SelectJob;
	}

	void SetSelectName(const FString& Name)
	{
		m_SelectName = Name;
	}

public:
	const FMonsterTableInfo* FindMonsterInfo(const FString& Name);
	const FPlayerTableInfo* FindPlayerInfo(const FString& Name);
	const FItemTableInfo* FindItemInfo(const FString& Name);
	const FQuestTableInfo* FindQuestInfo(const FString& Name);
};
