// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Monster.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	m_AnimType = EMonsterAnim::Idle;
	m_Hit = 0.f;
}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}


void UMonsterAnimInstance::AnimNotify_Attack()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster)
		Monster->NormalAttack();
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster)
		Monster->SetAttackEnd(true);

}

//void UMonsterAnimInstance::AnimNotify_HitEnd()
//{
//	m_Hit = 0.f;
//}


void UMonsterAnimInstance::AnimNotify_DeathEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster)
		Monster->MonsterDeath();
}