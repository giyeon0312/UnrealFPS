// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

AMainPlayerController::AMainPlayerController()
{
	bShowMouseCursor = true;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI mode;
	SetInputMode(mode);
}

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}