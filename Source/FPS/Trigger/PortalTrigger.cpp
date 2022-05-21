// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalTrigger.h"

// Sets default values
APortalTrigger::APortalTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	m_Particle->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APortalTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APortalTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalTrigger::BeginOverlapOverride(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PrintViewport(1.f, FColor::Red, TEXT("LevelStreamTrigger On"));

	UGameplayStatics::OpenLevel(GetWorld(), *m_LevelName);
}

void APortalTrigger::EndOverlapOverride(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	PrintViewport(1.f, FColor::Red, TEXT("LevelStreamTrigger Off"));

}
