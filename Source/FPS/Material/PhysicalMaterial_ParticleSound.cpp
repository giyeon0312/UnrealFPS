// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalMaterial_ParticleSound.h"
#include "../Effect/Effect.h"

UPhysicalMaterial_ParticleSound::UPhysicalMaterial_ParticleSound()
{
	m_Sound = nullptr;
	m_Volume = 30;
	m_Particle = nullptr;
}

void UPhysicalMaterial_ParticleSound::SetSound(const FString& Path)
{
	m_Sound = LoadObject<USoundBase>(this, *Path);
}

void UPhysicalMaterial_ParticleSound::SetParticle(const FString& Path)
{
	m_Particle = LoadObject<UParticleSystem>(this, *Path);
}

void UPhysicalMaterial_ParticleSound::PlaySound()
{
	if (!m_Sound)
		return;

	UGameplayStatics::PlaySound2D(GetWorld(), m_Sound, m_Volume);
}

void UPhysicalMaterial_ParticleSound::PlaySound(const FVector& Loc)
{
	if (!m_Sound)
		return;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), m_Sound, Loc, m_Volume);
}

AEffect* UPhysicalMaterial_ParticleSound::CreateParitcle(const FVector& Loc)
{
	if (!m_Particle)
		return nullptr;

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEffect* ParticleActor = GetWorld()->SpawnActor<AEffect>
		(AEffect::StaticClass(), Loc, FRotator::ZeroRotator, param);

	ParticleActor->SetParticle(m_Particle);

	return ParticleActor;
}