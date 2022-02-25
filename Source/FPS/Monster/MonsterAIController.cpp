// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"

AMonsterAIController::AMonsterAIController() :
	m_AITree(nullptr),
	m_AIData(nullptr)
{

}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (m_AIData)
		UseBlackboard(m_AIData, Blackboard); // m_AIData�� Blackboard()�� ���ڴٴ� �ǹ�

	if (m_AITree)
		RunBehaviorTree(m_AITree);
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}