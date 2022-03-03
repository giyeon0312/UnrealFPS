// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPawn.h"

ASelectPawn::ASelectPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(m_Root);

	m_Root->SetRelativeLocation(FVector(0.f, 0.f, 40.f));

}

// Called when the game starts or when spawned
void ASelectPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASelectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelectPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

