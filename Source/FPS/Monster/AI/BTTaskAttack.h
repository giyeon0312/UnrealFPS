// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskAttack.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTTaskAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
