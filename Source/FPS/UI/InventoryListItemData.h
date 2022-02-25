// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "InventoryListItemData.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UInventoryListItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UInventoryListItemData();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FString		m_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		EItemType	m_Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UTexture2D* m_IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UStaticMesh* m_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		TArray<FItemOptionInfo>	m_OptionArray;

public:
	const FString& GetItemName()	const
	{
		return m_Name;
	}

	EItemType GetItemType()	const
	{
		return m_Type;
	}

	UTexture2D* GetIconTexture()	const
	{
		return m_IconTexture;
	}

	UStaticMesh* GetItemMesh()	const
	{
		return m_Mesh;
	}

	const FItemOptionInfo* GetItemOption(EItemOption Option)	const
	{
		for (auto& Info : m_OptionArray)
		{
			if (Info.OptionType == Option)
				return &Info;
		}

		return nullptr;
	}

	const TArray<FItemOptionInfo>* GetItemOption()	const
	{
		return &m_OptionArray;
	}

public:
	void SetItemName(const FString& Name)
	{
		m_Name = Name;
	}

	void SetItemType(EItemType Type)
	{
		m_Type = Type;
	}

	void SetIconTexture(UTexture2D* Texture)
	{
		m_IconTexture = Texture;
	}

	void SetMesh(UStaticMesh* Mesh)
	{
		m_Mesh = Mesh;
	}

	void AddItemOption(EItemOption OptionType, int32 Option)
	{
		FItemOptionInfo	Info;
		Info.Option = Option;
		Info.OptionType = OptionType;

		m_OptionArray.Add(Info);
	}

	void AddItemOption(const FItemOptionInfo& Info)
	{
		m_OptionArray.Add(Info);
	}

	void SetItemOption(const TArray<FItemOptionInfo>& InfoArray)
	{
		m_OptionArray = InfoArray;
	}
};
