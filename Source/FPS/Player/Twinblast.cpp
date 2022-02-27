// Fill out your copyright notice in the Description page of Project Settings.


#include "Twinblast.h"
#include "PlayerAnimInstance.h"
#include "../Item/Weapon.h"
#include "../Monster/Monster.h"
#include "../Effect/Effect.h"


// Sets default values
ATwinblast::ATwinblast()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//에셋 로드
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Skins/Tier2/ActionMovie/Meshes/TwinBlast_ActionHero.TwinBlast_ActionHero'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Skins/Tier2/ActionMovie/Meshes/TwinBlast_ActionHero.TwinBlast_ActionHero'"));


	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	// 캡슐 가운데로 매시를 옮긴다.
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	
	// 기본 애니메이션
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Player/BPTwinblastAnim.BPTwinblastAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	// 공격 애님 몽타쥬들 1~3 가져오기
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack1Asset(TEXT("AnimMontage'/Game/Player/Twinblast/AMTwinblastAttack1.AMTwinblastAttack1'"));
	if (Attack1Asset.Succeeded())
		m_AttackMontageArr.Add(Attack1Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack2Asset(TEXT("AnimMontage'/Game/Player/Twinblast/AMTwinblastAttack2.AMTwinblastAttack2'"));
	if (Attack2Asset.Succeeded())
		m_AttackMontageArr.Add(Attack2Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack3Asset(TEXT("AnimMontage'/Game/Player/Twinblast/AMTwinblastAttack3.AMTwinblastAttack3'"));
	if (Attack3Asset.Succeeded())
		m_AttackMontageArr.Add(Attack3Asset.Object);

	//  Fall Recovery 몽타쥬
	static ConstructorHelpers::FObjectFinder<UAnimMontage> FallRecoveryAsset(TEXT("AnimMontage'/Game/Player/Twinblast/AMTwinblastFallRecovery.AMTwinblastFallRecovery'"));
	if (FallRecoveryAsset.Succeeded())
		m_FallRecoveryMontage = FallRecoveryAsset.Object;

	// 스킬 몽타쥬
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill1Asset(TEXT("AnimMontage'/Game/Player/Twinblast/AMTwinblastSkill1.AMTwinblastSkill1'"));
	if (Skill1Asset.Succeeded())
		m_SkillMontageArr.Add(Skill1Asset.Object);

	//기사로 지정
	m_Info.Name = TEXT("Knight");
}

// Called when the game starts or when spawned
void ATwinblast::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATwinblast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATwinblast::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATwinblast::NormalAttack()
{
	// Montage_IsPlaying 함수는 해당 몽타주가 재생이 되고 있다면 true, 아니면 false를 반환한다.
	if (!m_AnimInstance->Montage_IsPlaying(m_AttackMontageArr[m_AttackIndex])) 
	{
		// 이 몽타주의 플레이 위치를 처음으로 되돌려준다.
		m_AnimInstance->Montage_SetPosition(m_AttackMontageArr[m_AttackIndex], 0.f);

		m_AttackMontageArr[m_AttackIndex]->BlendIn.SetBlendTime(0.1f);
		m_AttackMontageArr[m_AttackIndex]->BlendOut.SetBlendTime(0.1f);

		m_AnimInstance->Montage_Play(m_AttackMontageArr[m_AttackIndex]);
		m_AnimInstance->SetAttackEnable(true);

		m_AttackIndex = (m_AttackIndex + 1) % m_AttackMontageArr.Num();
	}
}


void ATwinblast::AttackEnd()
{
	Super::AttackEnd();
	m_AttackIndex = 0;
}

void ATwinblast::Skill1()
{

	//PrintViewport(1.f, FColor::Red, TEXT("Skill1"));

	FVector Loc = GetMesh()->GetSocketLocation(TEXT("Skill1Location"));

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ASkill1* Skill = GetWorld()->SpawnActor<ASkill1>(ASkill1::StaticClass(), Loc,
		GetActorRotation(), params); // 원하는 액터를 스폰한다. 인자로 생성하는 위치
}

void ATwinblast::AttackEnable()
{
	FVector Loc = GetActorLocation();			// 현재위치
	FVector Forward = GetActorForwardVector();  // 전방방향

	FCollisionQueryParams param(NAME_None, false, this);

	TArray<FHitResult> HitArray;
	bool Hit = GetWorld()->SweepMultiByChannel(HitArray, Loc + (Forward * 30.f), Loc + Forward * 330.f,//여러마리를 때리므로 multi이다! 
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(50.f), param);

#if ENABLE_DRAW_DEBUG 	//에디터모드에서만 사용가능한 디버깅용으로 도형출력..(exe파일 뽑아서 할 땐 불가능) hit가능한 부분들을 도형으로 보자.

	FColor DrawColor = Hit ? FColor::Red : FColor::Green;
	FQuat qut = FRotationMatrix::MakeFromZ(Forward).ToQuat(); // 인수로 넣은 벡터 방향을 바라보도록 Z회전을 하게 회전 행렬을 만들어낸다.
															  // 부딪힌게 있으면 빨강색이겠지
	DrawDebugCapsule(GetWorld(), Loc + Forward * 130.f, 150.f, 50.f, qut, DrawColor, false, 1.f);

#endif
	if (Hit)
	{
		for (auto& result : HitArray)
		{
			FActorSpawnParameters param1;
			param1.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AEffect* Effect = GetWorld()->SpawnActor<AEffect>(AEffect::StaticClass(), result.ImpactPoint, result.ImpactNormal.Rotation(), param1);

			Effect->SetParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_hit_dark.P_ky_hit_dark'"));
			Effect->SetSound(TEXT("SoundWave'/Game/Sound/cardboard-step-1.cardboard-step-1'"));


			//데미지를 전달한다.
			FDamageEvent DmgEvent; //Actor클래스에 가상함수에 TakeDamage가 있다.
			result.GetActor()->TakeDamage((float)m_Info.Attack, DmgEvent, GetController(), this); //플레이어의 공격력.데미지이벤트(데미지 종류),주체가되는 컨트롤러(플레이어의),누가 데미지를 가하는지 

			//AMonster* Monster = Cast<AMonster>(result.GetActor());
			////충돌한 actor를 꺼내와서 monster에 넣었는데 제대로 들어가 있으면
			//if (Monster)
			//{

			//}

		}

	}
}
