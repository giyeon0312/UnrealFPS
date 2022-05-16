// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetPathManagement.h"

UAssetPathManagement::UAssetPathManagement()
{
}


void UAssetPathManagement::ConvertPath()
{
	LOG(TEXT("ConvertPath"));
	for (auto& result : ParticlePathArray)
	{
		m_mapParticlePath.Add(result.Name, result.Path);
		LOG(TEXT("Name : %s Path : %s"), *result.Name, *result.Path.ToString());
	}

	for (auto& result : SoundPathArray)
	{
		m_mapSoundPath.Add(result.Name, result.Path);
		LOG(TEXT("Name : %s Path : %s"), *result.Name, *result.Path.ToString());
	}
}

const FSoftObjectPath* UAssetPathManagement::FindParticlePath(const FString& Name)
{
	return m_mapParticlePath.Find(Name);
}

const FSoftObjectPath* UAssetPathManagement::FindSoundPath(const FString& Name)
{
	return m_mapSoundPath.Find(Name);
}
