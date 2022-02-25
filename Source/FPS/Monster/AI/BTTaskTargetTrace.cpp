// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskTargetTrace.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTTaskTargetTrace::UBTTaskTargetTrace()
{
	NodeName = TEXT("TargetTrace");
	bNotifyTick = true; //TickTask�� ���� ����
}

EBTNodeResult::Type UBTTaskTargetTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) // ����� �� �ѹ� ������
{
	EBTNodeResult::Type	result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); //�����̺�� Ʈ�������� �ڽ��� ����ϴ� AIController�� �׻�˰��ִ�.

	if (!Controller)
		return EBTNodeResult::Failed;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn()); // AIController�� ���ǵǾ��ִ� pawn�� ���� pawn�� Monster�� �ƴ϶�� ��ȯ�Ѵ�.

	if (!Monster)
		return EBTNodeResult::Failed;

	//Ÿ���� �Ѿư����ϹǷ� �����忡�� Ÿ���� ���;��Ѵ�.
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!Target) //Ÿ���� �����Ƿ� �̵��� �����.
	{
		//Monster->ChangeAnim(EMonsterAnim::Idle);

		//������̼� �޽��� �־ ��θ� ã�ƿ� �״�� �̵��ϰԲ� ���������� ���������.
		//�̵��� ����ϴ°��� AIController.AIController�� ��θ� ������̼� �޽����� ã�ƿ� �̵��ϰԲ��ϴ� ��.
		Controller->StopMovement();


		//���и� �����Ѵ�.
		return EBTNodeResult::Failed;
	}

	//Ÿ���� �ִٸ� Ÿ���� ��ġ�� ���� ã�Ƽ� �̵��ϵ��� �Ѵ�.
	// Controller->MoveToActor();
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target); // Blueprint/AIBlueprintHelperLibrary ���̺귯�� �ȿ� �ִ�.

	Monster->ChangeAnim(EMonsterAnim::Run);

	return EBTNodeResult::InProgress; //Tick���� �����ߴ��� üũ�ϰ� �½�ũ�� ������(FinishLatenTask)
}


void UBTTaskTargetTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) // �Ź� ������
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); // �����̺�� Ʈ�������� �ڽ��� ����ϴ� AIController�� �׻�˰��ִ�.
	if (!Controller)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);								   // �½�ũ�θ��� �������� �������� �����ϵ���
		return;
	}

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());							   // AIController�� ���ǵǾ��ִ� pawn�� ���� pawn�� Monster�� �ƴ϶�� ��ȯ�Ѵ�.
	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);								  // �½�ũ�θ��� �������� �������� �����ϵ���
		return;
	}

	//Ÿ���� �Ѿư����ϹǷ� �����忡�� Ÿ���� ���;��Ѵ�.
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!Target) //Ÿ���� �����Ƿ� �̵��� �����.
	{
		Monster->ChangeAnim(EMonsterAnim::Idle);
		Controller->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	// Ÿ�ٰ��� �Ÿ��� ���Ѵ�. 
	// Ÿ�ٰ� ������ ũ�Ⱑ ���� �ٸ� ��� ��ġ�� �����Ǿ� �ִ� �κ��� ���Ŀ� ���� �Ÿ��� ���Ұ�� �Ÿ��� �޶� �� �� �ִ�. (������ ��ġ�� ���̳��Ƿ�)
	// =>�ٴڿ� �پ��ִ� ���� �Ÿ��� ���ؼ� ���ݰŸ� ������ ������ üũ�Ѵ�.
	const FMonsterInfo* Info = Monster->GetInfo();

	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	// �ܼ��� z���� ��������� ������ �Ÿ�ó�� ���Ѵ�.
	MonsterLoc.Z = TargetLoc.Z;
	float Distance = FVector::Distance(MonsterLoc, TargetLoc);


	if (Distance <= Info->AttackDistance)
	{
		// ���ݰŸ� �ȿ� �����Ƿ� �̵��� ���߰� �������� ��ȯ�Ѵ�.
		Controller->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // �½�ũ �������� ó���Ѵ�.
		return;
	}
}
