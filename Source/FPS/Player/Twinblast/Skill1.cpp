// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill1.h"
#include "../../Effect/Effect.h"
#include "../../Effect/DecalEffect.h"

// Sets default values
ASkill1::ASkill1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	m_MeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MeshRoot"));
	m_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	m_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));


	SetRootComponent(m_Body);

	m_MeshRoot->SetupAttachment(m_Body);
	m_Mesh->SetupAttachment(m_MeshRoot);
	m_Particle->SetupAttachment(m_Body);

	m_Body->SetBoxExtent(FVector(65.f, 38.f, 20.f)); // ����ü�� ũ�� ����

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Weapon_ForgingHammers/SK_Forging_ForgeHammer02.SK_Forging_ForgeHammer02'"));
	if (MeshAsset.Succeeded())
		m_Mesh->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_cutter2.P_ky_cutter2'"));
	if (ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);

	m_Mesh->SetRelativeRotation(FRotator(0.f, 90.f, -90.f));  // �޽��� ȸ�� ����
	m_Mesh->SetRelativeLocation(FVector(-50.f, 0.f, 0.f));      // �޽��� ��ġ ����

	m_Particle->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));  // ��ƼŬ�� ȸ�� ����
	m_Particle->SetRelativeLocation(FVector(0.f, -120.f, 10.f));// ��ƼŬ�� ��ġ ����


	m_Movement->SetUpdatedComponent(m_Body); // �ٵ� �����̸� �ؿ��ִ� �޽��鵵 ���� �̵��ϰ���

	m_Movement->InitialSpeed = 1000.f;
	m_Movement->ProjectileGravityScale = 0.f; // �Ʒ��� �������� �ʵ��� �߷°��� ���ݴ�.

	m_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // ���ɻ��� ������ �޽��浹�� ������� �ʴ´�.

	m_Mesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;	// ĳ���Ͱ� ��� �ö� �� �ִ��� ����
	m_Body->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	//m_Body->SetCollisionProfileName(TEXT("BlockAll"));		     // �ڽ� �浹ü�� �浹�� ����Ѵ�.
	m_Body->SetCollisionProfileName(TEXT("PlayerAttack"));

	// �����Ʈ ������Ʈ���� �浹�Ͼ���� �̺�Ʈ�� ����ϱ� ���� ��������Ʈ�� ȣ���� �Լ��� �ִ´�.
	m_Movement->OnProjectileStop.AddDynamic(this, &ASkill1::PrjectileStop); // � ��ü�� �Լ�����������, �Լ��� �ּҸ� �־ ��������Ʈ�� �Լ��� �߰��Ѵ�.
																			// ��������Ʈ�� ���� Ÿ���� �Լ��� �߰�������Ѵ�.

	m_Distance = 2000.f; // ��ų��Ÿ��� 20m�� ���Ѵ�.
}

// Called when the game starts or when spawned
void ASkill1::BeginPlay()
{
	Super::BeginPlay();

	m_StartLocation = GetActorLocation();
}

// Called every frame
void ASkill1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ��ŸŸ��: ���� �����Ӱ� ���� ������ ���̿� �ð��� �󸶳� ��������
	// ��ŸŸ���� 1�ʵ��� �����Ǹ� ���� 1�̵ȴ�.
	// ������ ��ŸŸ���� ������Ű�°� �ƴ϶� AddRelativeRotation�� ȸ������ ������Ų��.
	// �׷� 1�ʵ��� 3���� ���°� �ȴ�. -  1/5�ʿ� 216, 1/3�ʿ� 360,..4/5�ʿ� 864��,...,1�ʿ� 1080�� 
	m_MeshRoot->AddRelativeRotation(FRotator(0.f, 1080.f * DeltaTime, 0.f)); // �θ�κ��� ������� ȸ���� ������Ų��.

	//// ��ų ��Ÿ��� �ٿ�������.
	//// �̵���*��ŸŸ�� = ���� �����ӿ��� �̵��Ѹ�ŭ ���ҽ�Ų��. 
	//m_Distance -= m_Movement->Velocity.Size() * DeltaTime;
	//if (m_Distance <= 0.f) //��Ÿ���ŭ �̵��ϸ�
	//	Destory();

	// �� ���Ͱ��� �Ÿ��� �����ִ� �Լ� - ������ġ�� �ǽð����� ��� �̵��ϰ� �ִ� ������ �Ÿ��� ���Ѵ�.
	// ���ӵ� �� �����ùķ��̼��� ����Ǿ� ���� ��Ȯ�ϴ�.
	float Dist = FVector::Distance(m_StartLocation, GetActorLocation());
	if (m_Distance <= Dist)
		Destroy();
}

void ASkill1::PrjectileStop(const FHitResult& result)
{
	PrintViewport(1.f, FColor::Red, TEXT("Projectile Stop"));

	//�ε��� ��ġ���ٰ� ��Ʈ���� ����Ʈ�� ������ �ϰڴ�s
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEffect* Effect = GetWorld()->SpawnActor<AEffect>(AEffect::StaticClass(),
		result.ImpactPoint, FRotator::ZeroRotator, params); // ImpactPoint�� �ε��� ��ġ�� �ǹ��Ѵ�.

	Effect->SetParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_explosion2.P_ky_explosion2'"));
	Effect->SetSound(TEXT("SoundWave'/Game/Sound/Fire1.Fire1'"));

	// �Ʒ� �������� ������ �̿��Ͽ� �ε����� ������ ��ġ�� �Ǵ��Ѵ�.
	FHitResult result1;
	FCollisionQueryParams	param1(NAME_None, false, this); //�̸�,�����浹,����,������ ����

	bool Collision = GetWorld()->LineTraceSingleByChannel(result1, result.ImpactPoint, result.ImpactPoint + FVector(0.f, 0.f, -300.f),
		ECollisionChannel::ECC_EngineTraceChannel5, param1); // �ε��� ������ ���� result1,������ġ, ����ġ(����), ��� ������Ʈ(LandScape)ä���� ��ȣ

	if (Collision) // �浹�ϸ� true, ��Į�� spawn�Ѵ�
	{
		FActorSpawnParameters param2;
		param2.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	/*	ADecalEffect* EffectDecal = GetWorld()->SpawnActor<ADecalEffect>(ADecalEffect::StaticClass(),
			result1.ImpactPoint, FRotator::ZeroRotator, param2);*/

		ADecalEffect* EffectDecal = GetWorld()->SpawnActor<ADecalEffect>(ADecalEffect::StaticClass(),
			result1.ImpactPoint, FRotator(-60.f, 0.f, 0.f), param2);

		// ��Į���� ����ϴ� ������ �����Ѵ�.
		EffectDecal->SetMaterial(TEXT("MaterialInstanceConstant'/Game/Effect/MTBurnDecal_Inst.MTBurnDecal_Inst'"));

		EffectDecal->SetLifeSpan(3.f);
	}

	Destroy();
	
}