// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Zombie.h"
#include "ZombieCop.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AZombieCop : public AZombie
{
	GENERATED_BODY()

public:
	AZombieCop();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void NormalAttack();
};