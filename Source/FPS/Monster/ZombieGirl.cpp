// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieGirl.h"
#include "../Effect/Effect.h"

AZombieGirl::AZombieGirl()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/Monster/ZombieGirl/ZombieGirl.ZombieGirl'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(90.f);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	//GetMesh()->SetRelativeScale3D(FVector(0.95f, 0.95f, 0.95f));

	m_SimpleStateWidget->SetRelativeLocation(FVector(0.f, 0.f, 230.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("AnimBlueprint'/Game/Monster/BPZombieGirlAnim.BPZombieGirlAnim_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	m_Info.Name = TEXT("ZombieGirl");
}

void AZombieGirl::BeginPlay()
{
	Super::BeginPlay();

}

void AZombieGirl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void  AZombieGirl::NormalAttack()
{
	FVector Loc = GetActorLocation();			// ������ġ
	FVector Forward = GetActorForwardVector();  // �������

	FCollisionQueryParams param(NAME_None, false, this);

		FHitResult result;
		bool Hit = GetWorld()->SweepSingleByChannel(result, Loc + (Forward * 30.f), Loc + Forward * (m_Info.AttackDistance + 30.f), //Ÿ�ٸ� �����Ƿ� single�̴�! 
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel8,
			FCollisionShape::MakeSphere(50.f), param);
	
	#if ENABLE_DRAW_DEBUG 	//�����͸�忡���� ��밡���� ���������� �������..(exe���� �̾Ƽ� �� ��..?�Ұ���) hit������ �κе��� �������� ����.
	
		FColor DrawColor = Hit ? FColor::Red : FColor::Green;
		FQuat qut = FRotationMatrix::MakeFromZ(Forward).ToQuat(); // �μ��� ���� ���� ������ �ٶ󺸵��� Zȸ���� �ϰ� ȸ�� ����� ������.
																  // �ε����� ������ �������̰���
		DrawDebugCapsule(GetWorld(), Loc + Forward * (m_Info.AttackDistance / 2.f + 30.f), m_Info.AttackDistance / 2.f + 50.f, 50.f, qut, DrawColor, false, 1.f);
	
	#endif
		if (Hit)
		{
			//����� ����Ʈ
	
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