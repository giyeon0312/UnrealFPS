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
	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No; //플레이어가 밟고 올라설 수 없도록
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->bReceivesDecals = false;

	// 몬스터 위 상태 바
	m_SimpleStateWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SimpleState"));
	m_SimpleStateWidget->SetupAttachment(GetMesh());

	static ConstructorHelpers::FClassFinder<UUserWidget>	SimpleCharacterState(TEXT("WidgetBlueprint'/Game/UI/UI_CharacterSimpleState.UI_CharacterSimpleState_C'"));

	if (SimpleCharacterState.Succeeded())
		m_SimpleStateWidget->SetWidgetClass(SimpleCharacterState.Class);

	m_SimpleStateWidget->SetWidgetSpace(EWidgetSpace::Screen);
	m_SimpleStateWidget->SetDrawSize(FVector2D(200.f, 60.f));


	m_MonsterAnim = nullptr;
	m_SpawnPoint = nullptr;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;			 // pawn클래스에 있다
	AIControllerClass = ANormalMonsterAIController::StaticClass();   // pawn클래스에 있다

	m_AttackEnd = false;

	m_PatrolIndex = 0;

	m_PatrolType = EMonsterPatrolType::Loop;
	m_PatrolDir = 1;						//Loop : 1, Inverse : -1

	// Dissolve 관련 변수들
	m_DissolveEnable = false;
	m_Dissolve = 1.5;
	m_DissolveTime = 3.f;								// Dissolve 재생시간
	m_DissolveAccTime = 0.f;
	m_DissolveMin = -1.5f;
	m_DissolveMax = 1.5;
	
	m_DissolveRange = m_DissolveMax - m_DissolveMin;

	GetMesh()->bRenderCustomDepth = true;
	GetMesh()->CustomDepthStencilWriteMask = ERendererStencilMask::ERSM_Default;
	GetMesh()->SetCustomDepthStencilValue(2);
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

	m_CharacterSimpleStateWidget = Cast<UCharacterSimpleStateWidget>(m_SimpleStateWidget->GetWidget());

	if (m_CharacterSimpleStateWidget)
		m_CharacterSimpleStateWidget->SetNameSetDelegate<AMonster>(this, &AMonster::SetPlayerNameWidget);

	// 머티리얼 정보들을 가져온다.
	int32 MtrlSlotCount = GetMesh()->GetNumMaterials();

	for (int32 i = 0; i < MtrlSlotCount; ++i)
	{
		UMaterialInstanceDynamic* Mtrl = GetMesh()->CreateDynamicMaterialInstance(i);
		m_DynamicMaterialArray.Add(Mtrl);
	}
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

	if (m_DissolveEnable)
	{
		m_DissolveAccTime += DeltaTime;

		m_Dissolve = m_DissolveMax - (m_DissolveAccTime / m_DissolveTime * m_DissolveRange);// 비율이 전체 구간에서 흐른 정도 구해

		GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Dissolve"), m_Dissolve);

		if (m_DissolveAccTime >= m_DissolveTime)
		{
			Destroy();
		}

		PrintViewport(2.f, FColor::Green, FString::Printf(TEXT("%f"), m_Dissolve));
	}
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

		// 죽었을 때 인공지능을 끄도록 한다.
		AAIController* AI = Cast<AAIController>(GetController());

		if (AI)
			AI->BrainComponent->StopLogic(TEXT("Dead"));

	}
	else if (Dmg > 0.f)				// 죽을땐 Hit 못하도록
		m_MonsterAnim->Hit();

	m_CharacterSimpleStateWidget->SetHPPercent((float)m_Info.HP / m_Info.HPMax);

	return Dmg;
}


void  AMonster::NormalAttack()
{

}


void AMonster::MonsterDeath()
{
	// 죽는 모션이 종료되엇으므로 여기에서 Dissolve를 활성화 시킨다.
	// 가지고 있는 모든 머티리얼들에 대해 변수의 이름을 바꾼다. 
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("DissolveEnable"), 1.f);

	m_DissolveEnable = true;
}