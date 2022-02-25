// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskTargetTrace.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTTaskTargetTrace::UBTTaskTargetTrace()
{
	NodeName = TEXT("TargetTrace");
	bNotifyTick = true; //TickTask를 쓸지 여부
}

EBTNodeResult::Type UBTTaskTargetTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) // 실행될 때 한번 들어오는
{
	EBTNodeResult::Type	result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); //비헤이비어 트리에서는 자신을 사용하는 AIController를 항상알고있다.

	if (!Controller)
		return EBTNodeResult::Failed;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn()); // AIController가 빙의되어있는 pawn을 얻어와 pawn이 Monster가 아니라면 반환한다.

	if (!Monster)
		return EBTNodeResult::Failed;

	//타겟을 쫓아가야하므로 블랙보드에서 타겟을 얻어와야한다.
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!Target) //타겟이 없으므로 이동을 멈춘다.
	{
		//Monster->ChangeAnim(EMonsterAnim::Idle);

		//내비게이션 메쉬가 있어서 경로를 찾아와 그대로 이동하게끔 내부적으로 만들어진다.
		//이동을 담당하는것이 AIController.AIController가 경로를 내비게이션 메쉬에서 찾아와 이동하게끔하는 것.
		Controller->StopMovement();


		//실패를 리턴한다.
		return EBTNodeResult::Failed;
	}

	//타겟이 있다면 타겟의 위치로 길을 찾아서 이동하도록 한다.
	// Controller->MoveToActor();
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target); // Blueprint/AIBlueprintHelperLibrary 라이브러리 안에 있다.

	Monster->ChangeAnim(EMonsterAnim::Run);

	return EBTNodeResult::InProgress; //Tick에서 도착했는지 체크하고 태스크를 끝내자(FinishLatenTask)
}


void UBTTaskTargetTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) // 매번 들어오는
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()); // 비헤이비어 트리에서는 자신을 사용하는 AIController를 항상알고있다.
	if (!Controller)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);								   // 태스크부모인 셀렉터의 오른쪽을 실행하도록
		return;
	}

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());							   // AIController가 빙의되어있는 pawn을 얻어와 pawn이 Monster가 아니라면 반환한다.
	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);								  // 태스크부모인 셀렉터의 오른쪽을 실행하도록
		return;
	}

	//타겟을 쫓아가야하므로 블랙보드에서 타겟을 얻어와야한다.
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!Target) //타겟이 없으므로 이동을 멈춘다.
	{
		Monster->ChangeAnim(EMonsterAnim::Idle);
		Controller->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	// 타겟과의 거리를 구한다. 
	// 타겟과 몬스터의 크기가 서로 다를 경우 위치로 지정되어 있는 부분이 어디냐에 따라 거리를 구할경우 거리가 달라 질 수 있다. (중점의 위치가 차이나므로)
	// =>바닥에 붙어있는 순수 거리를 구해서 공격거리 안으로 들어갔는지 체크한다.
	const FMonsterInfo* Info = Monster->GetInfo();

	FVector MonsterLoc = Monster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	// 단순히 z값을 맞취버려서 평면상의 거리처럼 구한다.
	MonsterLoc.Z = TargetLoc.Z;
	float Distance = FVector::Distance(MonsterLoc, TargetLoc);


	if (Distance <= Info->AttackDistance)
	{
		// 공격거리 안에 들어갔으므로 이동을 멈추고 공격으로 전환한다.
		Controller->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // 태스크 성공으로 처리한다.
		return;
	}
}
