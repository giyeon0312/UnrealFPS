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
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; //spawn����Ʈ�� ĸ���� ����� �־� AlwaysSpawn�����ϸ� �Ĺ������� �����Ƿ� �浹�ϸ� �ٸ����� spawn�ϵ����Ѵ�.

		m_SpawnMonster = GetWorld()->SpawnActor<AMonster>(m_SpawnClass, GetActorLocation(), GetActorRotation(), param);

		m_SpawnMonster->SetSpawnPoint(this);

		m_SpawnMonster->SetPatrolType(m_PatrolType);

		// patrol point�߰�
		m_SpawnMonster->AddPatrolPoint(GetActorLocation()); // ù SpawnPoint
		for (auto& Point : m_PatrolPointArray)				// PatrolPoint�� actor�̹Ƿ� GetActorLocation�� �����ϴ�
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

		if (m_AccTime >= m_SpawnTime) // ���Ͱ� �������� ���� �ð��� �������� �ٽ� ������.
		{
			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; //spawn����Ʈ�� ĸ���� ����� �־� AlwaysSpawn�����ϸ� �Ĺ������� �����Ƿ� �浹�ϸ� �ٸ����� spawn�ϵ����Ѵ�.

			m_SpawnMonster = GetWorld()->SpawnActor<AMonster>(m_SpawnClass, GetActorLocation(), GetActorRotation(), param);

			m_SpawnMonster->SetSpawnPoint(this);

			m_SpawnMonster->SetPatrolType(m_PatrolType);

			// patrol point�߰�
			m_SpawnMonster->AddPatrolPoint(GetActorLocation()); // ù SpawnPoint
			for (auto& Point : m_PatrolPointArray)				// PatrolPoint�� actor�̹Ƿ� GetActorLocation�� �����ϴ�
			{
				m_SpawnMonster->AddPatrolPoint(Point->GetActorLocation());
			}

			m_AccTime = 0.f;
		}
	}
}

