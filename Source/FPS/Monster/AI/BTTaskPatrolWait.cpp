// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskPatrolWait.h"
#include "../MonsterAIController.h"
#include "../Monster.h"


UBTTaskPatrolWait::UBTTaskPatrolWait()
{
	NodeName = TEXT("PatrolWait");
	bNotifyTick = true; //TickTask�� ���� ����

	m_AccTime = 0.f;
	m_WaitTime = 2.f;
}


EBTNodeResult::Type UBTTaskPatrolWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type	result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); //�����̺�� Ʈ�������� �ڽ��� ����ϴ� AIController�� �׻�˰��ִ�.

	if (!Controller)
		return EBTNodeResult::Failed;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn()); // AIController�� ���ǵǾ��ִ� pawn�� ���� pawn�� Monster�� �ƴ϶�� ��ȯ�Ѵ�.

	if (!Monster)
		return EBTNodeResult::Failed;

	Monster->ChangeAnim(EMonsterAnim::Idle);
	Controller->StopMovement();

	return EBTNodeResult::InProgress; //Tick���� �����ߴ��� üũ�ϰ� �½�ũ�� ������(FinishLatenTask)
}



void UBTTaskPatrolWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); //�����̺�� Ʈ�������� �ڽ��� ����ϴ� AIController�� �׻�˰��ִ�.
	if (!Controller)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);    //�½�ũ�θ��� �������� �������� �����ϵ���
		return;
	}

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn()); // AIController�� ���ǵǾ��ִ� pawn�� ���� pawn�� Monster�� �ƴ϶�� ��ȯ�Ѵ�.
	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);    // �½�ũ�θ��� �������� �������� �����ϵ���
		return;
	}

	//Ÿ�ٰ����� ���� �����忡�� Ÿ���� ���;��Ѵ�.
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	// ���� ��� ���¿��� Ÿ���� �߰ߵǾ��ٸ� �� Task�� �������� ó���ع�����.
	// Patrol��ü�� ������ �ٽ� TraceȤ�� Attack���� �������Ѵ�.
	if (Target)
	{
		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// Ÿ���� �߰����� ��������
	m_AccTime += DeltaSeconds;
	if (m_AccTime >= m_WaitTime)
	{
		m_AccTime = 0.f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed); // patrol�½�ũ�� ���۵ǵ���
	}
}