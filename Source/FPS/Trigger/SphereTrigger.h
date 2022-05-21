// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Trigger.h"
#include "SphereTrigger.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ASphereTrigger : public ATrigger
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASphereTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USphereComponent* m_Collider;

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
