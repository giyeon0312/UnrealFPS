// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAnimInstance.h"
#include "MonsterSpawnPoint.h"
#include "../FPSGameInstance.h"

// Sets default values
AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No; //플레이어가 밟고 올라설 수 없도록
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_MonsterAnim = nullptr;
	m_SpawnPoint = nullptr;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;			 // pawn클래스에 있다
	AIControllerClass = ANormalMonsterAIController::StaticClass();   // pawn클래스에 있다

	m_AttackEnd = false;

	m_PatrolIndex = 0;

	m_PatrolType = EMonsterPatrolType::Loop;
	m_PatrolDir = 1;						//Loop : 1, Inverse : -1
}

void AMonster::ChangeAnim(EMonsterAnim Anim)
{
	m_MonsterAnim->ChangeAnim(Anim);
}


void AMonster::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetReceivesDecals(false);	// 데칼 적용이 안되게 한다.


	m_MonsterAnim = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());

	UFPSGameInstance* GameInst = Cast<UFPSGameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		const FMonsterTableInfo* TableInfo = GameInst->FindMonsterInfo(m_Info.Name);

		if (TableInfo)
		{
			m_Info.Name = TableInfo->Name;
			m_Info.Attack = TableInfo->Attack;
			m_Info.Armor = TableInfo->Armor;
			m_Info.HP = TableInfo->HP;
			m_Info.HPMax = TableInfo->HPMax;
			m_Info.MP = TableInfo->MP;
			m_Info.MPMax = TableInfo->MPMax;
			m_Info.Level = TableInfo->Level;
			m_Info.Gold = TableInfo->Gold;
			m_Info.Exp = TableInfo->Exp;
			m_Info.AttackDistance = TableInfo->AttackDistance;
			m_Info.TraceDistance = TableInfo->TraceDistance;
			m_Info.AttackSpeed = TableInfo->AttackSpeed;
			m_Info.MoveSpeed = TableInfo->MoveSpeed;

			GetCharacterMovement()->MaxWalkSpeed = m_Info.MoveSpeed;
		}
	}
}

void AMonster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (m_SpawnPoint)
		m_SpawnPoint->Clear();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Dmg = DamageAmount - m_Info.Armor; // 데미지 - 몬스터의 방어력

	Dmg = Dmg <= 0.f ? 1.f : Dmg;			 //최소데미지 1

	Dmg = Super::TakeDamage(Dmg, DamageEvent, EventInstigator, DamageCauser); //Dmg값을 넣어서 0이 나오면 무적이고 아님 원본값이 그대로 나오면 값을 빼줄것이다.

	m_Info.HP -= (int32)Dmg;

	if (m_Info.HP <= 0)
	{
		m_Info.HP = 0.f;
		m_MonsterAnim->ChangeAnim(EMonsterAnim::Death);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else if (Dmg > 0.f)				// 죽을땐 Hit 못하도록
		m_MonsterAnim->Hit();

	return Dmg;

}


void  AMonster::NormalAttack()
{

}