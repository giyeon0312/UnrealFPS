// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "AssetPathManagement.generated.h"

/**
 * 
 */
UCLASS(config = AssetPathManagement)
class FPS_API UAssetPathManagement : public UObject
{
	GENERATED_BODY()
public:
	UAssetPathManagement();

private:
	UPROPERTY(Config)
	TArray<FAssetPathInfo>	ParticlePathArray;

	UPROPERTY(Config)
	TArray<FAssetPathInfo>	SoundPathArray;

	TMap<FString, FSoftObjectPath>	m_mapParticlePath;
	TMap<FString, FSoftObjectPath>	m_mapSoundPath;

public:
	void ConvertPath();
	const FSoftObjectPath* FindParticlePath(const FString& Name);
	const FSoftObjectPath* FindSoundPath(const FString& Name);
};
