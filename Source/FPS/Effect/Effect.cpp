#include "Effect.h"
#include "../FPSGameInstance.h"
#include "../AssetPathManagement.h"

AEffect::AEffect()
{
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


#pragma region LoadEffectAsync

void AEffect::SetParticleAsync(const FString& Name)
{
	UFPSGameInstance* GameInst = Cast<UFPSGameInstance>(GetWorld()->GetGameInstance());
	UAssetPathManagement* PathManager = GameInst->GetAssetPathManagement();

	const FSoftObjectPath* Path = PathManager->FindParticlePath(Name);

	if (!Path)	return;

	m_ParticleAssetPath = *Path;

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();

	m_AsyncParticleLoadHandle = streamMgr.RequestAsyncLoad(m_ParticleAssetPath,
		FStreamableDelegate::CreateUObject(this, &AEffect::LoadParticleAsyncComplete));
}

void AEffect::LoadParticleAsyncComplete()
{
	m_AsyncParticleLoadHandle->ReleaseHandle();
	TAssetPtr<UParticleSystem>	NewParticle(m_ParticleAssetPath);

	if (NewParticle)
	{
		m_Particle->SetTemplate(NewParticle.Get());
		m_Particle->OnSystemFinished.AddDynamic(this, &AEffect::ParticleFinish);
	}
}

void AEffect::SetSoundAsync(const FString& Name)
{
	UFPSGameInstance* GameInst = Cast<UFPSGameInstance>(GetWorld()->GetGameInstance());
	UAssetPathManagement* PathManager = GameInst->GetAssetPathManagement();

	const FSoftObjectPath* Path = PathManager->FindSoundPath(Name);

	if (!Path)	return;

	m_SoundAssetPath = *Path;	// 경로를 가져온다.

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();

	m_AsyncSoundLoadHandle = streamMgr.RequestAsyncLoad(m_SoundAssetPath,
		FStreamableDelegate::CreateUObject(this, &AEffect::LoadSoundAsyncComplete));
}

void AEffect::LoadSoundAsyncComplete()
{
	m_AsyncSoundLoadHandle->ReleaseHandle();

	TAssetPtr<USoundBase>	NewSound(m_SoundAssetPath);

	if (NewSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, NewSound.Get(), GetActorLocation());
	}
}

void AEffect::ParticleFinish(UParticleSystemComponent* Particle)
{
	Destroy();
}

#pragma endregion // LoadEffectAsync
