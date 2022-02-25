// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "Zombie.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AZombie : public AMonster
{
	GENERATED_BODY()
	
public:
	AZombie();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void NormalAttack();
};

