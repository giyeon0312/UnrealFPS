// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoxTrigger.h"
#include "LevelSequenceTrigger.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ALevelSequenceTrigger : public ABoxTrigger
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ALevelSequenceTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ULevelSequence* m_SequenceAsset;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<AActor*>	m_DeleteActorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool	m_Once;

	bool	m_Play;

	ULevelSequencePlayer* m_SequencePlayer;
	ALevelSequenceActor* m_SequenceActor;	// 레벨시퀀스 배치했을 때 생기는 액터

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void BeginOverlapOverride(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void EndOverlapOverride(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION()
	void SequenceFinish();

protected:
	virtual void SequenceFinishOverride();
};
