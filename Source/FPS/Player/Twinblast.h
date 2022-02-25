// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "Twinblast/Skill1.h"
#include "Twinblast.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ATwinblast : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ATwinblast();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void NormalAttack();
	virtual void AttackEnd();
	virtual void Skill1();
	virtual void AttackEnable();
};

