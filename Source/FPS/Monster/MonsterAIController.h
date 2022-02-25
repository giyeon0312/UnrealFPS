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
	virtual void OnPossess(APawn* InPawn); //AI��Ʈ�ѷ��� ���� ���ǵǰ� ���� �����ɶ� ȣ��Ǵ� �Լ�
	virtual void OnUnPossess();
};
