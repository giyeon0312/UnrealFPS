// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Character.h"
#include "SelectCharacter.generated.h"

UCLASS()
class FPS_API ASelectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASelectCharacter();

protected:
	EPlayerJob	m_Job;
	class USelectAnimInstance* m_AnimInstance;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void EnableOutLine(bool Enable);
};
