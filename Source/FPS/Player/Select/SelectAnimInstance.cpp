// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectAnimInstance.h"

USelectAnimInstance::USelectAnimInstance()
{
	m_Anim = ESelectAnim::Idle;
}

void USelectAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void USelectAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void USelectAnimInstance::AnimNotify_SelectEnd()
{
	m_Anim = ESelectAnim::Idle;
}
