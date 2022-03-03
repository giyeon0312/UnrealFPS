// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "SelectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ASelectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASelectPlayerController();

private:
	class ASelectCharacter* m_SelectCharacter;

protected:
	virtual void BeginPlay() override;

public:
	virtual void PlayerTick(float DeltaTime);
	virtual void SetupInputComponent();

protected:
	void Picking();

	UFUNCTION()
	void MouseLClick();

	UFUNCTION()
	void MouseLUp();
};
