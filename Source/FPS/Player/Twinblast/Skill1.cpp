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

	m_Body->SetBoxExtent(FVector(65.f, 38.f, 20.f)); // 층돌체의 크기 정보

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Weapon_ForgingHammers/SK_Forging_ForgeHammer02.SK_Forging_ForgeHammer02'"));
	if (MeshAsset.Succeeded())
		m_Mesh->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_cutter2.P_ky_cutter2'"));
	if (ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);

	m_Mesh->SetRelativeRotation(FRotator(0.f, 90.f, -90.f));  // 메쉬의 회전 정보
	m_Mesh->SetRelativeLocation(FVector(-50.f, 0.f, 0.f));      // 메쉬의 위치 정보

	m_Particle->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));  // 파티클의 회전 정보
	m_Particle->SetRelativeLocation(FVector(0.f, -120.f, 10.f));// 파티클의 위치 정보


	m_Movement->SetUpdatedComponent(m_Body); // 바디를 움직이면 밑에있는 메쉬들도 따라서 이동하겠지

	m_Movement->InitialSpeed = 1000.f;
	m_Movement->ProjectileGravityScale = 0.f; // 아래로 떨어지지 않도록 중력값을 없앴다.

	m_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 성능상의 이유로 메쉬충돌은 사용하지 않는다.

	m_Mesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;	// 캐릭터가 밟고 올라설 수 있는지 설정
	m_Body->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	//m_Body->SetCollisionProfileName(TEXT("BlockAll"));		     // 박스 충돌체의 충돌을 사용한다.
	m_Body->SetCollisionProfileName(TEXT("PlayerAttack"));

	// 무브먼트 컴포넌트에서 충돌일어났을때 이벤트에 등록하기 위해 델리게이트에 호출할 함수를 넣는다.
	m_Movement->OnProjectileStop.AddDynamic(this, &ASkill1::PrjectileStop); // 어떤 객체의 함수포인터인지, 함수의 주소를 넣어서 델리게이트에 함수를 추가한다.
																			// 델리게이트와 같은 타입의 함수를 추가해줘야한다.

	m_Distance = 2000.f; // 스킬사거리를 20m로 정한다.
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

	// 델타타임: 이전 프레임과 현재 프레임 사이에 시간이 얼마나 지났는지
	// 델타타임을 1초동안 누적되면 값이 1이된다.
	// 실제론 델타타임을 누적시키는게 아니라 AddRelativeRotation가 회전각을 누적시킨다.
	// 그럼 1초동안 3바퀴 도는게 된다. -  1/5초에 216, 1/3초에 360,..4/5초에 864도,...,1초에 1080도 
	m_MeshRoot->AddRelativeRotation(FRotator(0.f, 1080.f * DeltaTime, 0.f)); // 부모로부터 상대적인 회전을 누적시킨다.

	//// 스킬 사거리를 줄여나간다.
	//// 이동량*델타타임 = 현재 프레임에서 이동한만큼 감소시킨다. 
	//m_Distance -= m_Movement->Velocity.Size() * DeltaTime;
	//if (m_Distance <= 0.f) //사거리만큼 이동하면
	//	Destory();

	// 두 벡터간에 거리를 구해주는 함수 - 시작위치와 실시간으로 계속 이동하고 있는 액터의 거리를 추한다.
	// 가속도 등 물리시뮬레이션이 적용되어 더욱 정확하다.
	float Dist = FVector::Distance(m_StartLocation, GetActorLocation());
	if (m_Distance <= Dist)
		Destroy();
}

void ASkill1::PrjectileStop(const FHitResult& result)
{
	PrintViewport(1.f, FColor::Red, TEXT("Projectile Stop"));

	//부딪힌 위치에다가 터트리는 이펙트를 나오게 하겠다s
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEffect* Effect = GetWorld()->SpawnActor<AEffect>(AEffect::StaticClass(),
		result.ImpactPoint, FRotator::ZeroRotator, params); // ImpactPoint는 부딪힌 위치를 의미한다.

	Effect->SetParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_explosion2.P_ky_explosion2'"));
	Effect->SetSound(TEXT("SoundWave'/Game/Sound/Fire1.Fire1'"));

	// 아래 방향으로 직선을 이용하여 부딪히는 지형의 위치를 판단한다.
	FHitResult result1;
	FCollisionQueryParams	param1(NAME_None, false, this); //이름,복합충돌,여부,제외할 액터

	bool Collision = GetWorld()->LineTraceSingleByChannel(result1, result.ImpactPoint, result.ImpactPoint + FVector(0.f, 0.f, -300.f),
		ECollisionChannel::ECC_EngineTraceChannel5, param1); // 부딪힌 정보를 담을 result1,시작위치, 끝위치(방향), 대상 오브젝트(LandScape)채널의 번호

	if (Collision) // 충돌하면 true, 데칼을 spawn한다
	{
		FActorSpawnParameters param2;
		param2.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	/*	ADecalEffect* EffectDecal = GetWorld()->SpawnActor<ADecalEffect>(ADecalEffect::StaticClass(),
			result1.ImpactPoint, FRotator::ZeroRotator, param2);*/

		ADecalEffect* EffectDecal = GetWorld()->SpawnActor<ADecalEffect>(ADecalEffect::StaticClass(),
			result1.ImpactPoint, FRotator(-60.f, 0.f, 0.f), param2);

		// 데칼에서 사용하는 재질을 지정한다.
		EffectDecal->SetMaterial(TEXT("MaterialInstanceConstant'/Game/Effect/MTBurnDecal_Inst.MTBurnDecal_Inst'"));

		EffectDecal->SetLifeSpan(3.f);
	}

	Destroy();
	
}