#include "Effect.h"

// Sets default values
AEffect::AEffect()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	SetRootComponent(m_Particle);

}

// Called when the game starts or when spawned
void AEffect::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AEffect::SetParticle(const FString& Path)
{
	UParticleSystem* Particle = LoadObject<UParticleSystem>(this, *Path);

	if (Particle)
	{
		m_Particle->SetTemplate(Particle);

		// 파티클시스템 컴포넌트에서 이벤트가 잇어서 델리게이트에 추가
		m_Particle->OnSystemFinished.AddDynamic(this, &AEffect::ParticleFinish); 
	}
}

void AEffect::SetParticle(UParticleSystem* Particle)
{
	if (Particle)
	{
		m_Particle->SetTemplate(Particle);
		// 파티클시스템 컴포넌트에서 이벤트가 잇어서 델리게이트에 추가
		m_Particle->OnSystemFinished.AddDynamic(this, &AEffect::ParticleFinish);
	}
}


void AEffect::SetSound(const FString& Path)
{
	USoundBase* Sound = LoadObject<USoundBase>(this, *Path);

	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
	}
}

void AEffect::ParticleFinish(UParticleSystemComponent* Particle)
{
	Destroy();
}