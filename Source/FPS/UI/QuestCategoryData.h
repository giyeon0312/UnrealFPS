// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "QuestCategoryData.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UQuestCategoryData : public UObject
{
	GENERATED_BODY()
	
public:
	UQuestCategoryData();

private:
	EQuestCategory	m_Category;
	int32			m_TreeLevel;
	FString			m_QuestName;
	FString			m_QuestDesc;
	TArray<FQuestInfo>	m_QuestInfoArray;
	TArray<FQuestCompensation>	m_CompensationArray;
	TArray<UObject*>	m_ChildArray;		  // 계층구조
	UQuestCategoryData* m_Parent;			  // 부모
	class UQuestCategoryWidget* m_LinkWidget; // 연결된 카테고리 위젯
	bool				m_Complete;


public:
	void SetCategory(EQuestCategory Category)
	{
		m_Category = Category;
	}

	void SetComplete()
	{
		m_Complete = true;
	}

	void SetLinkWidget(class UQuestCategoryWidget* LinkWidget)
	{
		m_LinkWidget = LinkWidget;
	}

	UQuestCategoryData* CreateChild(const FQuestTableInfo* Info);

public:
	EQuestCategory GetCategory() const
	{
		return m_Category;
	}

	int32 GetTreeLevel() const
	{
		return m_TreeLevel;
	}
	bool IsComplete()	const
	{
		return m_Complete;
	}

	class UQuestCategoryWidget* GetLinkWidget()	const
	{
		return m_LinkWidget;
	}

	TArray<UObject*>& GetChildArray()
	{
		return m_ChildArray;
	}

	FString GetQuestName()	const
	{
		return m_QuestName;
	}

	FString GetQuestDesc()	const
	{
		return m_QuestDesc;
	}

	const TArray<FQuestInfo>* GetQuestInfoArray()	const
	{
		return &m_QuestInfoArray;
	}

	const TArray<FQuestCompensation>* GetCompensationArray()	const
	{
		return &m_CompensationArray;
	}

	bool EmptyQuest()	const
	{
		return m_QuestInfoArray.Num() == 0;
	}

	bool QuestComplete(int32 Index)
	{
		return m_QuestInfoArray[Index].Complete;
	}

	void AddCount(int32 Index)
	{
		++m_QuestInfoArray[Index].Count;

		if (m_QuestInfoArray[Index].Count >= m_QuestInfoArray[Index].CountMax)
		{
			m_QuestInfoArray[Index].Count = m_QuestInfoArray[Index].CountMax;
			m_QuestInfoArray[Index].Complete = true;
		}
	}
};
