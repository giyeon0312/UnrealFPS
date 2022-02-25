// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"

// Sets default values
AMonsterSpawnPoint::AMonsterSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SpawnTime = 1.f;
	m_AccTime = 0.f;
	m_SpawnMonster = nullptr;

	m_PatrolType = EMonsterPatrolType::Loop;
}

// Called when the game starts or when spawned
void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_SpawnClass))
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; //spawn포인트가 캡슐의 가운데에 있어 AlwaysSpawn으로하면 파묻힐수도 있으므로 충돌하면 다른곳에 spawn하도록한다.

		m_SpawnMonster = GetWorld()->SpawnActor<AMonster>(m_SpawnClass, GetActorLocation(), GetActorRotation(), param);

		m_SpawnMonster->SetSpawnPoint(this);

		m_SpawnMonster->SetPatrolType(m_PatrolType);

		// patrol point추가
		m_SpawnMonster->AddPatrolPoint(GetActorLocation()); // 첫 SpawnPoint
		for (auto& Point : m_PatrolPointArray)				// PatrolPoint도 actor이므로 GetActorLocation이 가능하다
		{
			m_SpawnMonster->AddPatrolPoint(Point->GetActorLocation());
		}
	}

}

// Called every frame
void AMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_SpawnMonster)
	{
		m_AccTime += DeltaTime;

		if (m_AccTime >= m_SpawnTime) // 몬스터가 없어진지 오랜 시간이 지났으면 다시 만들어낸다.
		{
			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; //spawn포인트가 캡슐의 가운데에 있어 AlwaysSpawn으로하면 파묻힐수도 있으므로 충돌하면 다른곳에 spawn하도록한다.

			m_SpawnMonster = GetWorld()->SpawnActor<AMonster>(m_SpawnClass, GetActorLocation(), GetActorRotation(), param);

			m_SpawnMonster->SetSpawnPoint(this);

			m_SpawnMonster->SetPatrolType(m_PatrolType);

			// patrol point추가
			m_SpawnMonster->AddPatrolPoint(GetActorLocation()); // 첫 SpawnPoint
			for (auto& Point : m_PatrolPointArray)				// PatrolPoint도 actor이므로 GetActorLocation이 가능하다
			{
				m_SpawnMonster->AddPatrolPoint(Point->GetActorLocation());
			}

			m_AccTime = 0.f;
		}
	}
}

