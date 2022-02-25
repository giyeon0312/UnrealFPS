// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceMonsterDetect.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTServiceMonsterDetect : public UBTService
{
	GENERATED_BODY()

public:
	UBTServiceMonsterDetect();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
