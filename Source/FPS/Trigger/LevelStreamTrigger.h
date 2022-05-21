// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoxTrigger.h"
#include "LevelStreamTrigger.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ALevelStreamTrigger : public ABoxTrigger
{
	GENERATED_BODY()

public:
	ALevelStreamTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString	m_LevelName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void BeginOverlapOverride(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void EndOverlapOverride(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
