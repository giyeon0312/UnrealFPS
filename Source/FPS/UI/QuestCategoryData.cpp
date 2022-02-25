// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestCategoryData.h"

UQuestCategoryData::UQuestCategoryData()
{
	m_TreeLevel = 0;
	m_Category = EQuestCategory::Part1;
	m_LinkWidget = nullptr;
}

UQuestCategoryData* UQuestCategoryData::CreateChild(const FQuestTableInfo* Info)
{
	UQuestCategoryData* Child = NewObject<UQuestCategoryData>(this,
		UQuestCategoryData::StaticClass());

	Child->m_TreeLevel = m_TreeLevel + 1;
	Child->m_QuestName = Info->Name;
	Child->m_QuestDesc = Info->QuestDesc;
	Child->m_Category = Info->Category;
	Child->m_Parent = this;

	for (auto& QuestInfo : Info->InfoArray)
	{
		Child->m_QuestInfoArray.Add(QuestInfo);
	}

	//for (auto& Compensation : Info->CompensationArray)
	//{
	//	Child->m_CompensationArray.Add(Compensation);
	//}

	m_ChildArray.Add(Child);

	return Child;
}
