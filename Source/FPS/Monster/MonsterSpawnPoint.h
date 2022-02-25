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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true)) //spawn클래스를 외부에서 설정할수 있도록
	TSubclassOf<AMonster> m_SpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true)) //spawn된 몬스터가 죽으면 일정 시간 후에 다시 spawn될수 있도록
	float m_SpawnTime; //몇 초뒤에 spawn될지

	float m_AccTime;   //누적시간

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<APatrolPoint*> m_PatrolPointArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EMonsterPatrolType m_PatrolType;

	AMonster* m_SpawnMonster; //spawn된 몬스터

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
