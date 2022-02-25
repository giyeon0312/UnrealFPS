// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Zombie.h"
#include "ZombieGirl.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AZombieGirl : public AZombie
{
	GENERATED_BODY()

public:
	AZombieGirl();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void NormalAttack();
};
