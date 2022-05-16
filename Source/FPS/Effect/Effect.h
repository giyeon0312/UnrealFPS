// 생성해서 한 번 빵 터트리고 없어질 이펙트
// 이펙트들의 부모가 될것이기 때문에 생성자에서 오브젝트를 로드해놓을 수 없다.
// 실시간으로 오브젝트를 로드하는 기능이 필요하다.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Effect.generated.h"

UCLASS()
class FPS_API AEffect : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEffect();


protected:
	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)) // 파티클시스템 컴포넌트
	UParticleSystemComponent* m_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FSoftObjectPath		m_ParticleAssetPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FSoftObjectPath		m_SoundAssetPath;

	TSharedPtr<FStreamableHandle>	m_AsyncParticleLoadHandle;
	TSharedPtr<FStreamableHandle>	m_AsyncSoundLoadHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 경로를 받아서 실시간 파티클 오브젝트 로드한다.
	void SetParticle(const FString& Path);
	void SetParticle(UParticleSystem *Particle);
	// 사운드 재생 시스템
	void SetSound(const FString& Path);

	void SetParticleAsync(const FString& Name);
	void LoadParticleAsyncComplete();
	void SetSoundAsync(const FString& Name);
	void LoadSoundAsyncComplete();

	UFUNCTION()
		void ParticleFinish(UParticleSystemComponent* Particle);
};


