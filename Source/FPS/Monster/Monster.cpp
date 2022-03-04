// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAnimInstance.h"
#include "MonsterSpawnPoint.h"
#include "NormalMonsterAIController.h"
#include "../FPSGameInstance.h"
#include "../UI/CharacterSimpleStateWidget.h"

// Sets default values
AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No; //�÷��̾ ��� �ö� �� ������
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// ���� �� ���� ��
	m_SimpleStateWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SimpleState"));
	m_SimpleStateWidget->SetupAttachment(GetMesh());

	static ConstructorHelpers::FClassFinder<UUserWidget>	SimpleCharacterState(TEXT("WidgetBlueprint'/Game/UI/UI_CharacterSimpleState.UI_CharacterSimpleState_C'"));

	if (SimpleCharacterState.Succeeded())
		m_SimpleStateWidget->SetWidgetClass(SimpleCharacterState.Class);

	m_SimpleStateWidget->SetWidgetSpace(EWidgetSpace::Screen);
	m_SimpleStateWidget->SetDrawSize(FVector2D(200.f, 60.f));


	m_MonsterAnim = nullptr;
	m_SpawnPoint = nullptr;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;			 // pawnŬ������ �ִ�
	AIControllerClass = ANormalMonsterAIController::StaticClass();   // pawnŬ������ �ִ�

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
	GetMesh()->SetReceivesDecals(false);	// ��Į ������ �ȵǰ� �Ѵ�.


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

	m_CharacterSimpleStateWidget = Cast<UCharacterSimpleStateWidget>(m_SimpleStateWidget->GetWidget());

	if (m_CharacterSimpleStateWidget)
		m_CharacterSimpleStateWidget->SetNameSetDelegate<AMonster>(this, &AMonster::SetPlayerNameWidget);
}

void AMonster::SetPlayerNameWidget()
{
	m_CharacterSimpleStateWidget->SetCharacterName(m_Info.Name);
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
	float Dmg = DamageAmount - m_Info.Armor; // ������ - ������ ����

	Dmg = Dmg <= 0.f ? 1.f : Dmg;			 //�ּҵ����� 1

	Dmg = Super::TakeDamage(Dmg, DamageEvent, EventInstigator, DamageCauser); //Dmg���� �־ 0�� ������ �����̰� �ƴ� �������� �״�� ������ ���� ���ٰ��̴�.

	m_Info.HP -= (int32)Dmg;

	if (m_Info.HP <= 0)
	{
		m_Info.HP = 0.f;
		m_MonsterAnim->ChangeAnim(EMonsterAnim::Death);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// �׾��� �� �ΰ������� ������ �Ѵ�.
		AAIController* AI = Cast<AAIController>(GetController());

		if (AI)
			AI->BrainComponent->StopLogic(TEXT("Dead"));

	}
	else if (Dmg > 0.f)				// ������ Hit ���ϵ���
		m_MonsterAnim->Hit();

	m_CharacterSimpleStateWidget->SetHPPercent((float)m_Info.HP / m_Info.HPMax);

	return Dmg;
}


void  AMonster::NormalAttack()
{

}