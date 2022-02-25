// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItemDescData.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UInventoryItemDescData : public UObject
{
	GENERATED_BODY()
	
public:
	UInventoryItemDescData();

private:
	FString		m_Name;
	int32		m_Option;

public:
	const FString& GetItemName()	const
	{
		return m_Name;
	}

	int32 GetOption()	const
	{
		return m_Option;
	}

public:
	void SetItemOption(const FItemOptionInfo& Info);
};
