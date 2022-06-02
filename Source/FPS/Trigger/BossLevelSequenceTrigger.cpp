// Fill out your copyright notice in the Description page of Project Settings.


#include "BossLevelSequenceTrigger.h"


// Sets default values
ABossLevelSequenceTrigger::ABossLevelSequenceTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABossLevelSequenceTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABossLevelSequenceTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossLevelSequenceTrigger::SequenceFinishOverride()
{
	Super::SequenceFinishOverride();

	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AMonster>(m_SpawnClass,
		m_SpawnPoint, FRotator::ZeroRotator,
		param);
}

