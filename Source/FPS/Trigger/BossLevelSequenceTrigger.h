// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Monster/Monster.h"
#include "LevelSequenceTrigger.h"
#include "BossLevelSequenceTrigger.generated.h"


UCLASS()
class FPS_API ABossLevelSequenceTrigger : public ALevelSequenceTrigger
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABossLevelSequenceTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<AMonster>	m_SpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FVector					m_SpawnPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SequenceFinishOverride();
};
