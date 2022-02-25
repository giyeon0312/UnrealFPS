// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameInstance.h"


UFPSGameInstance::UFPSGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterInfoTableAsset(TEXT("DataTable'/Game/Monster/DTMonsterInfo.DTMonsterInfo'"));

	if (MonsterInfoTableAsset.Succeeded())
		m_MonsterInfoTable = MonsterInfoTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerInfoTableAsset(TEXT("DataTable'/Game/Player/DTPlayerInfo.DTPlayerInfo'"));

	if (PlayerInfoTableAsset.Succeeded())
		m_PlayerInfoTable = PlayerInfoTableAsset.Object;
	//else
	//	m_PlayerInfoTable = nullptr;
	static  ConstructorHelpers::FObjectFinder<UDataTable> ItemInfoTableAsset(TEXT("DataTable'/Game/Item/DTItem.DTItem'"));

	if (ItemInfoTableAsset.Succeeded())
		m_ItemInfoTable = ItemInfoTableAsset.Object;

	static  ConstructorHelpers::FObjectFinder<UDataTable> QuestInfoTableAsset(TEXT("DataTable'/Game/Quest/DTQuest.DTQuest'"));

	if (QuestInfoTableAsset.Succeeded())
		m_QuestInfoTable = QuestInfoTableAsset.Object;
}


const FMonsterTableInfo* UFPSGameInstance::FindMonsterInfo(const FString& Name)
{
	if (m_MonsterInfoTable)
		return m_MonsterInfoTable->FindRow<FMonsterTableInfo>(*Name, TEXT(""));

	return nullptr;
}


const FPlayerTableInfo* UFPSGameInstance::FindPlayerInfo(const FString& Name)
{
	if (m_PlayerInfoTable)
		return m_PlayerInfoTable->FindRow<FPlayerTableInfo>(*Name, TEXT(""));

	return nullptr;
}

const FItemTableInfo* UFPSGameInstance::FindItemInfo(const FString& Name)
{
	if (m_ItemInfoTable)
		return m_ItemInfoTable->FindRow<FItemTableInfo>(*Name, TEXT(""));

	return nullptr;
}

const FQuestTableInfo* UFPSGameInstance::FindQuestInfo(const FString& Name)
{
	if (m_QuestInfoTable)
		return m_QuestInfoTable->FindRow<FQuestTableInfo>(*Name, TEXT(""));

	return nullptr;
}