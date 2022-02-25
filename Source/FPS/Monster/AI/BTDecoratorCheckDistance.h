// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecoratorCheckDistance.generated.h"

UENUM(BlueprintType)
enum class ECheckDistanceType : uint8
{
	Trace,
	Attack
};

UCLASS()
class FPS_API UBTDecoratorCheckDistance : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecoratorCheckDistance();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ECheckDistanceType m_Type;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

};
