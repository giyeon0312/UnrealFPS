// �����ؼ� �� �� �� ��Ʈ���� ������ ����Ʈ
// ����Ʈ���� �θ� �ɰ��̱� ������ �����ڿ��� ������Ʈ�� �ε��س��� �� ����.
// �ǽð����� ������Ʈ�� �ε��ϴ� ����� �ʿ��ϴ�.

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
	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)) // ��ƼŬ�ý��� ������Ʈ
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
	// ��θ� �޾Ƽ� �ǽð� ��ƼŬ ������Ʈ �ε��Ѵ�.
	void SetParticle(const FString& Path);
	void SetParticle(UParticleSystem *Particle);
	// ���� ��� �ý���
	void SetSound(const FString& Path);

	void SetParticleAsync(const FString& Name);
	void LoadParticleAsyncComplete();
	void SetSoundAsync(const FString& Name);
	void LoadSoundAsyncComplete();

	UFUNCTION()
		void ParticleFinish(UParticleSystemComponent* Particle);
};


