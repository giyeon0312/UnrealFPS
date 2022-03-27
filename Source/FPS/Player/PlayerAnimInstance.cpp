// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	m_MoveSpeed = 0.f;
	m_MoveDir = 0.f;

	m_AttackEnable = false;
	m_AttackCombo = false;

	m_AnimType = EPlayerAnim::Ground;


	m_FallRecoveryAdditive = 0.f;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	// ĳ���͸� �����ͼ� ĳ���� �����Ʈ���� �̵��ӵ��� �ִ����� �Ǵ��Ѵ�.
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner()); // �� �ִ��ν��Ͻ��� �����ϰ� �ִ� �� ��ü�� ���´�.

	if (Player)
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();
		
		if (Movement)
		{
			// velocity�� MovementComponent�� ������ �ִ� ������ �ӵ� �����̴�.
			// �� �ӵ������� ũ�⸦ ���ϸ� ������ �̵��ӵ��� ������ �ȴ�.
			m_MoveSpeed = Movement->Velocity.Size();

			m_Ground = Movement->IsMovingOnGround(); // �� ���� �ִ��� �ǽð����� �����´�.

			if (!m_Ground && m_AnimType != EPlayerAnim::Jump)
			{
				m_AnimType = EPlayerAnim::Fall;
			}
		}
	}

}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	m_AttackEnable = false;
	m_AttackCombo = false;

	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
		Player->AttackEnd();


	//PrintViewport(1.f, FColor::Red, TEXT("AttackEndNotify"));
}

void UPlayerAnimInstance::AnimNotify_AttackCombo()
{
	m_AttackCombo = true;

	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
		Player->SetAttackEnable(true);

	//PrintViewport(1.f, FColor::Red, TEXT("AttackComboNotify"));
}

void UPlayerAnimInstance::AnimNotify_JumpEnd()
{
	m_AnimType = EPlayerAnim::Fall;
}

void UPlayerAnimInstance::AnimNotify_FallEnd()
{
	m_AnimType = EPlayerAnim::Ground;

	m_FallRecoveryAdditive = 1.f;

	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
		Player->PlayFallRecovery();
}

void UPlayerAnimInstance::AnimNotify_FallRecoveryEnd()
{
	m_FallRecoveryAdditive = 0.f;
}

void UPlayerAnimInstance::AnimNotify_Skill1Enable()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
		Player->Skill1();
}


void UPlayerAnimInstance::AnimNotify_Attack()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
		Player->AttackEnable();
}


void UPlayerAnimInstance::AnimNotify_FootLeft()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
		Player->Foot(true);
}

void UPlayerAnimInstance::AnimNotify_FootRight()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (Player)
		Player->Foot(false);
}