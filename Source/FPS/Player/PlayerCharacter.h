// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/SceneCaptureComponent2D.h"
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

	void SetPlayerNameWidget();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USpringArmComponent* m_Arm;

	// ĳ���� ���� ���¹�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UWidgetComponent* m_SimpleStateWidget;

	class UCharacterSimpleStateWidget* m_CharacterSimpleStateWidget;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USceneCaptureComponent2D* m_FaceCapture;*/


	// ��Ÿ�ָ� �迭�� �����´�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<class UAnimMontage*> m_AttackMontageArr;
	int32						m_AttackIndex;

	// ��ų ��Ÿ��
	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivate = true));
	TArray<class UAnimMontage*> m_SkillMontageArr;

	class UAnimMontage* m_FallRecoveryMontage;

	bool m_AttackEnable;

	class UPlayerAnimInstance* m_AnimInstance;
	bool m_MoveKey;		// �ƿ� �ȿ����̴��� üũ

	bool m_Death;		// �׾����� üũ

	class AWeapon* m_Weapon;

	// ��ƮƮ���� ȿ������ ������Ʈ��
	USkeletalMesh* m_MeshAsset;

	bool		m_Ghost;
	float		m_GhostTime;
	float		m_GhostTimeMax;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivate = true));
	FPlayerInfo m_Info;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivate = true));
	FString m_HitParticleName;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivate = true));
	FString m_HitSoundName;

public:
	const FPlayerInfo* GetInfo() const
	{
		return &m_Info;
	}

	void SetAttackEnable(bool Enable)
	{
		m_AttackEnable = Enable;
	}

	FVector GetCameraPosition()	const
	{
		return m_Camera->GetComponentLocation();
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

public:
	void Foot(bool Left);
};
