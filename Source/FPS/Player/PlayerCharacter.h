// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FPS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USpringArmComponent* m_Arm;

	// 몽타주를 배열로 가져온다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<class UAnimMontage*> m_AttackMontageArr;
	int32						m_AttackIndex;

	// 스킬 몽타주
	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivate = true));
	TArray<class UAnimMontage*> m_SkillMontageArr;

	class UAnimMontage* m_FallRecoveryMontage;

	bool m_AttackEnable;

	class UPlayerAnimInstance* m_AnimInstance;
	bool m_MoveKey;		// 아예 안움직이는지 체크

	bool m_Death;		// 죽었는지 체크

	class AWeapon* m_Weapon;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivate = true));
	FPlayerInfo m_Info;


public:
	const FPlayerInfo* GetInfo() const
	{
		return &m_Info;
	}

	void SetAttackEnable(bool Enable)
	{
		m_AttackEnable = Enable;
	}

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void RotationZ(float Scale);
	void CameraLookUp(float Scale);
	void CameraZoom(float Scale);
	void MoveFront(float Scale);
	void MoveSide(float Scale);
	void NormalAttackKey();
	void JumpKey();
	void PlayFallRecovery();
	void Skill1Key();
	void WeaponAttachKey();
	void WeaponDetachKey();
	void SetWeapon(UStaticMesh* WeaponMesh);
	void AddHP(int32 HP);
	void AddMP(int32 MP);

public:
	virtual void NormalAttack();
	virtual void AttackEnd();
	virtual void Skill1();
	virtual void AttackEnable();
};
