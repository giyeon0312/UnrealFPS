// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecoratorCheckDistance.h"
#include "../MonsterAIController.h"
#include "../Monster.h"


UBTDecoratorCheckDistance::UBTDecoratorCheckDistance()
{
	NodeName = TEXT("CheckDistance");
}


bool UBTDecoratorCheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// ��Ʈ�ѷ��� ����, Ÿ���� �����´�.
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); //�����̺�� Ʈ�������� �ڽ��� ����ϴ� AIController�� �׻�˰��ִ�.
	if (!Controller)
		return false;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn()); // AIController�� ���ǵǾ��ִ� pawn�� ���� pawn�� Monster�� �ƴ϶�� ��ȯ�Ѵ�.
	if (!Monster)
		return false;

	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!Target)
		return false;

	const FMonsterInfo* Info = Monster->GetInfo();

	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	// �ܼ��� z���� ��������� ������ �Ÿ�ó�� ���Ѵ�.
	MonsterLoc.Z = TargetLoc.Z;
	float Distance = FVector::Distance(MonsterLoc, TargetLoc);

	float CheckDistance = 0.f;

	switch (m_Type)
	{
	case ECheckDistanceType::Trace:
		CheckDistance = Info->TraceDistance;
		break;
	case ECheckDistanceType::Attack:
		CheckDistance = Info->AttackDistance;
		break;
	}

	return Distance <= CheckDistance; //�����Ϳ� �������� �ƴ��� ���η� �־��ֱ� ���� 
}
