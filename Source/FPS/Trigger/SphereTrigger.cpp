// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereTrigger.h"


// Sets default values
ASphereTrigger::ASphereTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(m_Collider);

	m_Collider->SetCollisionProfileName(*m_TriggerName);
}

// Called when the game starts or when spawned
void ASphereTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_Collider->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::BeginOverlap);
	m_Collider->OnComponentEndOverlap.AddDynamic(this, &ATrigger::EndOverlap);

	m_Collider->SetCollisionProfileName(*m_TriggerName);
}

// Called every frame
void ASphereTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASphereTrigger::BeginOverlapOverride(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ASphereTrigger::EndOverlapOverride(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}