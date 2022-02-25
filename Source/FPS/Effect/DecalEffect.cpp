// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalEffect.h"

// Sets default values
ADecalEffect::ADecalEffect()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	SetRootComponent(m_Decal);

	m_Decal->SetRelativeRotation(FRotator(90.f, 0.f, 90.f));
	//m_Decal->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

// Called when the game starts or when spawned
void ADecalEffect::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADecalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADecalEffect::SetMaterial(const FString& Path)
{
	UMaterialInstance* Material = LoadObject<UMaterialInstance>(this, *Path);

	if (Material)
	{
		m_Decal->SetDecalMaterial(Material);
	}
}

