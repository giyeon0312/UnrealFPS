// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PhysicalMaterial_ParticleSound.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UPhysicalMaterial_ParticleSound : public UPhysicalMaterial
{
	GENERATED_BODY()
	

public:
	UPhysicalMaterial_ParticleSound();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USoundBase* m_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float m_Volume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UParticleSystem* m_Particle;

public:
	void SetSound(const FString& Path);
	void SetParticle(const FString& Path);
	void PlaySound();						// 전체 재생
	void PlaySound(const FVector& Loc);		// 특정 위치 중심 재생

public:
	USoundBase* GetSound() const
	{
		return m_Sound;
	}

	UParticleSystem* GetParticle() const
	{
		return m_Particle;
	}

public:
	class AEffect* CreateParitcle(const FVector& Loc);
};
