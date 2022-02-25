// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UCLASS()
class FPS_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EMonsterAnim m_AnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))	// HitAdditive에서 블루프린트에서 사용하려고 한 것인데 리소스가 없다.. 
	float m_Hit;

public:
	void ChangeAnim(EMonsterAnim Anim)
	{
		m_AnimType = Anim;
	}

	void Hit()
	{
		m_Hit = 1.f;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
		void AnimNotify_Attack();

	UFUNCTION()
		void AnimNotify_AttackEnd();

	//UFUNCTION()
	//	void AnimNotify_HitEnd();	//Hit애니메이션이 없어서 스킵이다.

	UFUNCTION()
		void AnimNotify_DeathEnd();
};
