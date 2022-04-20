// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();

private:
	TArray<class AEnvironmentActor*>	m_CameraCollisionEnvironmentActor;

protected:
	virtual void BeginPlay() override;

public:
	virtual void PlayerTick(float DeltaTime) override;

};
