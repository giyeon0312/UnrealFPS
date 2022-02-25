// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Monster.h"
#include "AI/PatrolPoint.h"
#include "MonsterSpawnPoint.generated.h"



UCLASS()
class FPS_API AMonsterSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	AMonsterSpawnPoint();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true)) //spawnŬ������ �ܺο��� �����Ҽ� �ֵ���
	TSubclassOf<AMonster> m_SpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true)) //spawn�� ���Ͱ� ������ ���� �ð� �Ŀ� �ٽ� spawn�ɼ� �ֵ���
	float m_SpawnTime; //�� �ʵڿ� spawn����

	float m_AccTime;   //�����ð�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<APatrolPoint*> m_PatrolPointArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EMonsterPatrolType m_PatrolType;

	AMonster* m_SpawnMonster; //spawn�� ����

public:
	void Clear()
	{
		m_SpawnMonster = nullptr;
		m_AccTime = 0.f;
	}

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
