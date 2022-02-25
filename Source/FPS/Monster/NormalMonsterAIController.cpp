// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonsterAIController.h"


ANormalMonsterAIController::ANormalMonsterAIController() 
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITreeAsset(TEXT("BehaviorTree'/Game/Monster/AI/BTMonster.BTMonster'"));

	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BlackBoardAsset(TEXT("BlackboardData'/Game/Monster/AI/BBMonster.BBMonster'"));

	if (BlackBoardAsset.Succeeded())
		m_AIData = BlackBoardAsset.Object;

}

void ANormalMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ANormalMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}