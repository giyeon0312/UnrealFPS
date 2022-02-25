// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskPatrol.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTTaskPatrol::UBTTaskPatrol()
{
	NodeName = TEXT("Patrol");
	bNotifyTick = true; //TickTask�� ���� ����

	m_AccTime = 0.f;
	m_WaitTime = 5.f;
}


EBTNodeResult::Type UBTTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type	result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());  //�����̺�� Ʈ�������� �ڽ��� ����ϴ� AIController�� �׻�˰��ִ�.

	if (!Controller)
		return EBTNodeResult::Failed;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());								// AIController�� ���ǵǾ��ִ� pawn�� ���� pawn�� Monster�� �ƴ϶�� ��ȯ�Ѵ�.

	if (!Monster)
		return EBTNodeResult::Failed;

	Monster->ChangeAnim(EMonsterAnim::Run);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Monster->GetPatrolPoint());	//  ��ġ�� ���� ã�Ƽ� �̵��ϵ��� �Ѵ�.
	//PrintViewport(1.f, FColor::Red, TEXT("moving"));
	return EBTNodeResult::InProgress; //Tick���� �����ߴ��� üũ�ϰ� �½�ũ�� ������(FinishLatenTask)
}



void UBTTaskPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// �����ߴ����� �Ÿ��񱳷� �Ǵ��Ѵ�.
	// Z���� ���� ������ ���ߴ� ������ ���������Ÿ��� �밢���� �����Ƿ� ��Ȯ�� �����Ÿ� ���Ϸ���
	FVector PatrolPoint = Monster->GetPatrolPoint();
	FVector MonsterLoc = Monster->GetActorLocation();

	float CasuleHalfHeight = Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	float CapsuleRadius = Monster->GetCapsuleComponent()->GetScaledCapsuleRadius();

	//MonsterLoc.Z -= CasuleHalfHeight;//�ܼ��� z���� ��������� ������ �Ÿ�ó�� ���Ѵ�.

	// ������ ��ġ�� ��Ʈ������Ƽ�� �Ÿ��� �����ش�.
	float Distance = FVector::Distance(MonsterLoc, PatrolPoint);


	// �� ������ �Ÿ��� ���� ĸ���� ���� ���� + ĸ���� �ݰ溸�� �۰ų� �������ٸ� ����� �����Ѱ����� �Ǵ��Ѵ�.
	if (Distance <= CapsuleRadius + CasuleHalfHeight)
	{
		// ���� ��Ʈ���� ��ġ�� �̵��Ѵ�.
		Monster->NextPatrolPoint();
		//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Monster->GetPatrolPoint());

	}

	// Ÿ���� �߰����� ��������
	m_AccTime += DeltaSeconds;
	if (m_AccTime >= m_WaitTime)
	{
		m_AccTime = 0.f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed); // patrol�½�ũ�� ���۵ǵ���
	}
}
