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

	class UAssetPathManagement* m_AssetManagement;

public:
	UFPSGameInstance();

public:
	virtual void Init();

public:
	void SetSelectName(const FString& Name)
	{
		m_SelectName = Name;
	}
	
	const FString GetSelectName()
	{
		return m_SelectName;
	}

	void SetSelectJob(EPlayerJob Job)
	{
		m_SelectJob = Job;
	}

	EPlayerJob GetSelectJob()	const
	{
		return m_SelectJob;
	}

	// 비동기로 로드하는 에셋의 경로를 얻기 위해 전체 매니지먼트를 리턴한다.
	class UAssetPathManagement* GetAssetPathManagement()
	{
		return m_AssetManagement;
	}

public:
	const FMonsterTableInfo* FindMonsterInfo(const FString& Name);
	const FPlayerTableInfo* FindPlayerInfo(const FString& Name);
	const FItemTableInfo* FindItemInfo(const FString& Name);
	const FQuestTableInfo* FindQuestInfo(const FString& Name);
};
