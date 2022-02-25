// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMonsterAIController();

protected:
	UBehaviorTree* m_AITree;
	UBlackboardData* m_AIData;

protected:
	virtual void OnPossess(APawn* InPawn); //AI컨트롤러가 폰에 빙의되고 빙의 해제될때 호출되는 함수
	virtual void OnUnPossess();
};
