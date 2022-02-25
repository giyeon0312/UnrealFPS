// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Weapon.generated.h"

UCLASS()
class FPS_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
