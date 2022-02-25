// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceMonsterDetect.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTServiceMonsterDetect::UBTServiceMonsterDetect()
{
	NodeName = TEXT("MonsterDetect");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTServiceMonsterDetect::TickNode(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
		return;

	const FMonsterInfo* MonsterInfo = Monster->GetInfo();

	FCollisionQueryParams	param(NAME_None, false, Monster);

	FHitResult	result;
	bool Collision = GetWorld()->SweepSingleByChannel(result,
		Monster->GetActorLocation(), Monster->GetActorLocation(),
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel7,
		FCollisionShape::MakeSphere(MonsterInfo->TraceDistance),
		param);

	// #if�� ���� ��ó���Ⱑ ������ �Ǿ��ִ����� �Ǵ��Ѵ�.
#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = Collision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), Monster->GetActorLocation(),MonsterInfo->TraceDistance, 20, DrawColor, false, 0.3f);

#endif

	// �浹�̵Ǹ� �����忡 Target���� �������ش�. 
	// �����̺��Ʈ�������� �����忡 Target���� ������ �Ѿư��� ������ �����ϵ��� �Ѵ�.
	if (Collision)
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), result.GetActor());
		UE_LOG(LogTemp, Log, TEXT("yesTarget"));
	}
	else
	{ 
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
		UE_LOG(LogTemp, Log, TEXT("NoTarget"));
	}
}
