// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(m_Mesh);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::SetMesh(const FString& Path)
{
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(this, *Path);

	if (Mesh)
		m_Mesh->SetStaticMesh(Mesh);
}

void AItem::SetMesh(UStaticMesh* Mesh)
{
	if (Mesh)
		m_Mesh->SetStaticMesh(Mesh);
}

void  AItem::SimulatePhysics(bool Simulate)
{
	m_Mesh->SetSimulatePhysics(Simulate);
}