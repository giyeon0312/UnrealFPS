// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"


UCLASS()
class FPS_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float m_MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float m_MoveDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool m_AttackEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EPlayerAnim m_AnimType;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true))
	bool m_Ground;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true))
	float m_FallRecoveryAdditive;

	bool m_AttackCombo; // 애니메이션 노티파이에서 콤보 가능상태인지 알아낸다.

public:
	bool GetAttackCombo()
	{
		return m_AttackCombo;
	}


public:
	void SetDir(float Dir)
	{
		m_MoveDir = Dir;
	}

	float GetDir()
	{
		return m_MoveDir;
	}

	void SetAttackEnable(bool Enable)
	{
		m_AttackEnable = Enable;
	}

	void ChangeAnim(EPlayerAnim Anim)
	{
		m_AnimType = Anim;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_AttackCombo();

	UFUNCTION()
	void AnimNotify_JumpEnd();

	UFUNCTION()
	void AnimNotify_FallEnd();

	UFUNCTION()
	void AnimNotify_FallRecoveryEnd();

	UFUNCTION()
	void AnimNotify_Skill1Enable();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_FootLeft();

	UFUNCTION()
	void AnimNotify_FootRight();

};
