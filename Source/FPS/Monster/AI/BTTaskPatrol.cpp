// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskPatrol.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTTaskPatrol::UBTTaskPatrol()
{
	NodeName = TEXT("Patrol");
	bNotifyTick = true; //TickTask를 쓸지 여부

	m_AccTime = 0.f;
	m_WaitTime = 5.f;
}


EBTNodeResult::Type UBTTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type	result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());  //비헤이비어 트리에서는 자신을 사용하는 AIController를 항상알고있다.

	if (!Controller)
		return EBTNodeResult::Failed;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());								// AIController가 빙의되어있는 pawn을 얻어와 pawn이 Monster가 아니라면 반환한다.

	if (!Monster)
		return EBTNodeResult::Failed;

	Monster->ChangeAnim(EMonsterAnim::Run);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Monster->GetPatrolPoint());	//  위치로 길을 찾아서 이동하도록 한다.
	//PrintViewport(1.f, FColor::Red, TEXT("moving"));
	return EBTNodeResult::InProgress; //Tick에서 도착했는지 체크하고 태스크를 끝내자(FinishLatenTask)
}



void UBTTaskPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// 도착했는지를 거리비교로 판단한다.
	// Z값을 같은 값으로 맞추는 이유는 중점에서거리는 대각선이 나오므로 정확한 직선거리 구하려구
	FVector PatrolPoint = Monster->GetPatrolPoint();
	FVector MonsterLoc = Monster->GetActorLocation();

	float CasuleHalfHeight = Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	float CapsuleRadius = Monster->GetCapsuleComponent()->GetScaledCapsuleRadius();

	//MonsterLoc.Z -= CasuleHalfHeight;//단순히 z값을 맞취버려서 평면상의 거리처럼 구한다.

	// 몬스터의 위치와 패트롤의위티의 거리를 구해준다.
	float Distance = FVector::Distance(MonsterLoc, PatrolPoint);


	// 둘 사이의 거리가 몬스터 캡슐의 절반 길이 + 캡슐의 반경보다 작거나 같아졌다면 제대로 도착한것으로 판단한다.
	if (Distance <= CapsuleRadius + CasuleHalfHeight)
	{
		// 다음 패트롤의 위치로 이동한다.
		Monster->NextPatrolPoint();
		//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Monster->GetPatrolPoint());

	}

	// 타겟을 발견하지 못했으면
	m_AccTime += DeltaSeconds;
	if (m_AccTime >= m_WaitTime)
	{
		m_AccTime = 0.f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed); // patrol태스크가 동작되도록
	}
}
