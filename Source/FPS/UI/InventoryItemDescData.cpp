// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemDescData.h"

UInventoryItemDescData::UInventoryItemDescData()
{
}

void UInventoryItemDescData::SetItemOption(const FItemOptionInfo& Info)
{
	switch (Info.OptionType)
	{
	case EItemOption::Attack:
		m_Name = TEXT("공격력");
		break;
	case EItemOption::Armor:
		m_Name = TEXT("방어력");
		break;
	case EItemOption::HP:
		m_Name = TEXT("체력");
		break;
	case EItemOption::MP:
		m_Name = TEXT("마나");
		break;
	case EItemOption::Critical:
		m_Name = TEXT("치명타");
		break;
	case EItemOption::HPRecovery:
		m_Name = TEXT("체력회복");
		break;
	case EItemOption::MPRecovery:
		m_Name = TEXT("마나회복");
		break;
	}

	m_Option = Info.Option;
}