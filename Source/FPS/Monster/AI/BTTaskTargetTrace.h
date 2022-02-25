// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskTargetTrace.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTTaskTargetTrace : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskTargetTrace();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
