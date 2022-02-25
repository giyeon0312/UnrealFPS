// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskPatrolWait.h"
#include "../MonsterAIController.h"
#include "../Monster.h"


UBTTaskPatrolWait::UBTTaskPatrolWait()
{
	NodeName = TEXT("PatrolWait");
	bNotifyTick = true; //TickTask를 쓸지 여부

	m_AccTime = 0.f;
	m_WaitTime = 2.f;
}


EBTNodeResult::Type UBTTaskPatrolWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type	result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); //비헤이비어 트리에서는 자신을 사용하는 AIController를 항상알고있다.

	if (!Controller)
		return EBTNodeResult::Failed;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn()); // AIController가 빙의되어있는 pawn을 얻어와 pawn이 Monster가 아니라면 반환한다.

	if (!Monster)
		return EBTNodeResult::Failed;

	Monster->ChangeAnim(EMonsterAnim::Idle);
	Controller->StopMovement();

	return EBTNodeResult::InProgress; //Tick에서 도착했는지 체크하고 태스크를 끝내자(FinishLatenTask)
}



void UBTTaskPatrolWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); //비헤이비어 트리에서는 자신을 사용하는 AIController를 항상알고있다.
	if (!Controller)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);    //태스크부모인 셀렉터의 오른쪽을 실행하도록
		return;
	}

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn()); // AIController가 빙의되어있는 pawn을 얻어와 pawn이 Monster가 아니라면 반환한다.
	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);    // 태스크부모인 셀렉터의 오른쪽을 실행하도록
		return;
	}

	//타겟감지를 위해 블랙보드에서 타겟을 얻어와야한다.
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	// 만약 대기 상태에서 타겟이 발견되었다면 이 Task는 멈춤으로 처리해버린다.
	// Patrol자체를 나가서 다시 Trace혹은 Attack으로 가도록한다.
	if (Target)
	{
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// 타겟을 발견하지 못했으면
	m_AccTime += DeltaSeconds;
	if (m_AccTime >= m_WaitTime)
	{
		m_AccTime = 0.f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed); // patrol태스크가 동작되도록
	}
}