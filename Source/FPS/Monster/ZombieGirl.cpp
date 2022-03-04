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
	FVector Loc = GetActorLocation();			// 현재위치
	FVector Forward = GetActorForwardVector();  // 전방방향

	FCollisionQueryParams param(NAME_None, false, this);

		FHitResult result;
		bool Hit = GetWorld()->SweepSingleByChannel(result, Loc + (Forward * 30.f), Loc + Forward * (m_Info.AttackDistance + 30.f), //타겟만 때리므로 single이다! 
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel8,
			FCollisionShape::MakeSphere(50.f), param);
	
	#if ENABLE_DRAW_DEBUG 	//에디터모드에서만 사용가능한 디버깅용으로 도형출력..(exe파일 뽑아서 할 땐..?불가능) hit가능한 부분들을 도형으로 보자.
	
		FColor DrawColor = Hit ? FColor::Red : FColor::Green;
		FQuat qut = FRotationMatrix::MakeFromZ(Forward).ToQuat(); // 인수로 넣은 벡터 방향을 바라보도록 Z회전을 하게 회전 행렬을 만들어낸다.
																  // 부딪힌게 있으면 빨강색이겠지
		DrawDebugCapsule(GetWorld(), Loc + Forward * (m_Info.AttackDistance / 2.f + 30.f), m_Info.AttackDistance / 2.f + 50.f, 50.f, qut, DrawColor, false, 1.f);
	
	#endif
		if (Hit)
		{
			//사운드와 이펙트
	
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