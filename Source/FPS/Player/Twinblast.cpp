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

	//���� �ε�
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Skins/Tier2/ActionMovie/Meshes/TwinBlast_ActionHero.TwinBlast_ActionHero'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Skins/Tier2/ActionMovie/Meshes/TwinBlast_ActionHero.TwinBlast_ActionHero'"));


	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	// ĸ�� ����� �Žø� �ű��.
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	
	// �⺻ �ִϸ��̼�
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Player/BPTwinblastAnim.BPTwinblastAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	// ���� �ִ� ��Ÿ��� 1~3 ��������
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack1Asset(TEXT("AnimMontage'/Game/Player/Twinblast/AMTwinblastAttack1.AMTwinblastAttack1'"));
	if (Attack1Asset.Succeeded())
		m_AttackMontageArr.Add(Attack1Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack2Asset(TEXT("AnimMontage'/Game/Player/Twinblast/AMTwinblastAttack2.AMTwinblastAttack2'"));
	if (Attack2Asset.Succeeded())
		m_AttackMontageArr.Add(Attack2Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack3Asset(TEXT("AnimMontage'/Game/Player/Twinblast/AMTwinblastAttack3.AMTwinblastAttack3'"));
	if (Attack3Asset.Succeeded())
		m_AttackMontageArr.Add(Attack3Asset.Object);

	//  Fall Recovery ��Ÿ��
	static ConstructorHelpers::FObjectFinder<UAnimMontage> FallRecoveryAsset(TEXT("AnimMontage'/Game/Player/Twinblast/AMTwinblastFallRecovery.AMTwinblastFallRecovery'"));
	if (FallRecoveryAsset.Succeeded())
		m_FallRecoveryMontage = FallRecoveryAsset.Object;

	// ��ų ��Ÿ��
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill1Asset(TEXT("AnimMontage'/Game/Player/Twinblast/AMTwinblastSkill1.AMTwinblastSkill1'"));
	if (Skill1Asset.Succeeded())
		m_SkillMontageArr.Add(Skill1Asset.Object);

	//���� ����
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
	// Montage_IsPlaying �Լ��� �ش� ��Ÿ�ְ� ����� �ǰ� �ִٸ� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	if (!m_AnimInstance->Montage_IsPlaying(m_AttackMontageArr[m_AttackIndex])) 
	{
		// �� ��Ÿ���� �÷��� ��ġ�� ó������ �ǵ����ش�.
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
		GetActorRotation(), params); // ���ϴ� ���͸� �����Ѵ�. ���ڷ� �����ϴ� ��ġ
}

void ATwinblast::AttackEnable()
{
	FVector Loc = GetActorLocation();			// ������ġ
	FVector Forward = GetActorForwardVector();  // �������

	FCollisionQueryParams param(NAME_None, false, this);

	TArray<FHitResult> HitArray;
	bool Hit = GetWorld()->SweepMultiByChannel(HitArray, Loc + (Forward * 30.f), Loc + Forward * 330.f,//���������� �����Ƿ� multi�̴�! 
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(50.f), param);

#if ENABLE_DRAW_DEBUG 	//�����͸�忡���� ��밡���� ���������� �������..(exe���� �̾Ƽ� �� �� �Ұ���) hit������ �κе��� �������� ����.

	FColor DrawColor = Hit ? FColor::Red : FColor::Green;
	FQuat qut = FRotationMatrix::MakeFromZ(Forward).ToQuat(); // �μ��� ���� ���� ������ �ٶ󺸵��� Zȸ���� �ϰ� ȸ�� ����� ������.
															  // �ε����� ������ �������̰���
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


			//�������� �����Ѵ�.
			FDamageEvent DmgEvent; //ActorŬ������ �����Լ��� TakeDamage�� �ִ�.
			result.GetActor()->TakeDamage((float)m_Info.Attack, DmgEvent, GetController(), this); //�÷��̾��� ���ݷ�.�������̺�Ʈ(������ ����),��ü���Ǵ� ��Ʈ�ѷ�(�÷��̾���),���� �������� ���ϴ��� 

			//AMonster* Monster = Cast<AMonster>(result.GetActor());
			////�浹�� actor�� �����ͼ� monster�� �־��µ� ����� �� ������
			//if (Monster)
			//{

			//}

		}

	}
}
