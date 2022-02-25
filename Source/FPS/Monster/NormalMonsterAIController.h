// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterAIController.h"
#include "NormalMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ANormalMonsterAIController : public AMonsterAIController
{
	GENERATED_BODY()
	
public:
	ANormalMonsterAIController();

protected:
	virtual void OnPossess(APawn* InPawn); //AI컨트롤러가 폰에 빙의되고 빙의 해제될때 호출되는 함수
	virtual void OnUnPossess();
};

