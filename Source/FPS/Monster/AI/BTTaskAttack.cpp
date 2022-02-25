// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskAttack.h"
#include "../MonsterAIController.h"
#include "../Monster.h"


UBTTaskAttack::UBTTaskAttack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true; //TickTask�� ���� ����
}


EBTNodeResult::Type UBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		Monster->ChangeAnim(EMonsterAnim::Idle);

		//������̼� �޽��� �־ ��θ� ã�ƿ� �״�� �̵��ϰԲ� ���������� ���������.
		//�̵��� ����ϴ°��� AIController.AIController�� ��θ� ������̼� �޽����� ã�ƿ� �̵��ϰԲ��ϴ� ��.
		Controller->StopMovement();


		//���и� �����Ѵ�.
		return EBTNodeResult::Failed;
	}

	Monster->ChangeAnim(EMonsterAnim::Attack);

	return EBTNodeResult::InProgress; //Tick���� �����ߴ��� üũ�ϰ� �½�ũ�� ������(FinishLatenTask)
}



void UBTTaskAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); //�����̺�� Ʈ�������� �ڽ��� ����ϴ� AIController�� �׻�˰��ִ�.
	if (!Controller)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed); //�½�ũ�θ��� �������� �������� �����ϵ���
		return;
	}

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn()); // AIController�� ���ǵǾ��ִ� pawn�� ���� pawn�� Monster�� �ƴ϶�� ��ȯ�Ѵ�.
	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed); //�½�ũ�θ��� �������� �������� �����ϵ���
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

	//���ݸ���� ������ ���. �������̸� ȸ������ �ʴ´�.
	if (Monster->IsAttackEnd())
	{
		//���� �Ÿ��� ���ݰŸ����� ����� ��� �� Task�� �����Ų��.
		if (Distance > Info->AttackDistance)
		{
			UE_LOG(LogTemp, Log, TEXT("out of attack distance"));
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		else
		{
			// ����� ���� ���ݰŸ� �ȿ� ������ ��� ��� ������ �ٶ� �� �ֵ��� ȸ����Ų��.
			// ȸ�� ó���� ���ؼ� ���Ͱ� ����� �ٶ󺼼� �մ� ������ �����ֵ��� �Ѵ�.
			FVector Dir = TargetLoc - MonsterLoc; // Ÿ���� ��ġ���� ���� ��ġ�� ���� ������ ������
			Dir.Normalize(); // normalize�� ũ�⸦ ������ ũ�� 1¥�� ���⺤�ͷ� ���������

			Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f)); // Ÿ�������� ���� �����Ƿ� �� ȸ��
		}

		Monster->SetAttackEnd(false);

		return;
	}
}
