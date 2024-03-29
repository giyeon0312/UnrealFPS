// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskPatrol.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTTaskPatrol : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskPatrol();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float m_WaitTime;																					// 대기시간

	float m_AccTime;																					// 누적 시간

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	
};
