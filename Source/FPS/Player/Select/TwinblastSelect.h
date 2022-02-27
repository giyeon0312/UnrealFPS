// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SelectCharacter.h"
#include "TwinblastSelect.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ATwinblastSelect : public ASelectCharacter
{
	GENERATED_BODY()

public:
	ATwinblastSelect();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
