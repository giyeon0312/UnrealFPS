// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "SelectAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ESelectAnim : uint8
{
	Idle,
	Select
};

UCLASS()
class FPS_API USelectAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USelectAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ESelectAnim	m_Anim;

public:
	void Select()
	{
		m_Anim = ESelectAnim::Select;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
		void AnimNotify_SelectEnd();
};
