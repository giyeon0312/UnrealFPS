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

	// 컨트롤러와 몬스터, 타겟을 가져온다.
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); //비헤이비어 트리에서는 자신을 사용하는 AIController를 항상알고있다.
	if (!Controller)
		return false;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn()); // AIController가 빙의되어있는 pawn을 얻어와 pawn이 Monster가 아니라면 반환한다.
	if (!Monster)
		return false;

	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!Target)
		return false;

	const FMonsterInfo* Info = Monster->GetInfo();

	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	// 단순히 z값을 맞취버려서 평면상의 거리처럼 구한다.
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

	return Distance <= CheckDistance; //셀렉터에 성공인지 아닌지 여부로 넣어주기 위해 
}
