// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DecalEffect.generated.h"

UCLASS()
class FPS_API ADecalEffect : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADecalEffect();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UDecalComponent* m_Decal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetMaterial(const FString& Path);
};
