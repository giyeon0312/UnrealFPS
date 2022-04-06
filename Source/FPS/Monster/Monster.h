// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "NormalMonsterAIController.h"
#include "Monster.generated.h"

UCLASS()
class FPS_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	AMonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FMonsterInfo				m_Info;

	class UMonsterAnimInstance* m_MonsterAnim;
	class AMonsterSpawnPoint* m_SpawnPoint;

	TArray<FVector>				m_PatrolPointArray;
	int32						m_PatrolIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EMonsterPatrolType			m_PatrolType;

	int32						m_PatrolDir;			// m_PatrolType Inverse : -1, Loop : 1

	bool						m_AttackEnd;

	bool						m_DissolveEnable;
	float						m_Dissolve;			// Dissolve ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float m_DissolveMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float m_DissolveMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float m_DissolveTime;								// Dissolve ����ð�

	float m_DissolveAccTime;
	float m_DissolveRange;								// Dissolve �ð�����


	TArray<UMaterialInstanceDynamic*>	m_DynamicMaterialArray; // �������� ���� ��Ƽ���� �ν��Ͻ�

protected:
	// ���� �� ���¹�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UWidgetComponent* m_SimpleStateWidget;

	class UCharacterSimpleStateWidget* m_CharacterSimpleStateWidget;

	void SetPlayerNameWidget();

public:
	bool IsAttackEnd() const
	{
		return m_AttackEnd;
	}

	void SetAttackEnd(bool AttackEnd)
	{
		m_AttackEnd = AttackEnd;
	}

	void SetSpawnPoint(class AMonsterSpawnPoint* Point)
	{
		m_SpawnPoint = Point;
	}

	const FMonsterInfo* GetInfo() const
	{
		return &m_Info;
	}

	void AddPatrolPoint(FVector Point)
	{
		m_PatrolPointArray.Add(Point);
	}

	void SetPatrolType(EMonsterPatrolType Type)
	{
		m_PatrolType = Type;
	}

	FVector GetPatrolPoint()
	{
		return m_PatrolPointArray[m_PatrolIndex];
	}

	void NextPatrolPoint()
	{
		m_PatrolIndex += m_PatrolDir;

		if (m_PatrolType == EMonsterPatrolType::Loop)
		{
			m_PatrolIndex %= m_PatrolPointArray.Num();
		}
		else						//EMonsterPatrolType::Inverse
		{
			if (m_PatrolDir == 1)  // ������
			{
				if (m_PatrolIndex == m_PatrolPointArray.Num())
				{
					m_PatrolIndex = m_PatrolPointArray.Num() - 1;
					m_PatrolDir = -1;
				}
			}
			else				   // ������
			{
				if (m_PatrolIndex == -1)
				{
					m_PatrolIndex = 0;
					m_PatrolDir = 1;
				}
			}
		}
	}

	void ChangeAnim(EMonsterAnim Anim);


protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void NormalAttack();

public:
	void MonsterDeath();
};
