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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// ��θ� �޾Ƽ� �ǽð� ��ƼŬ ������Ʈ �ε��Ѵ�.
	void SetParticle(const FString& Path);
	// ���� ��� �ý���
	void SetSound(const FString& Path);

	UFUNCTION()
		void ParticleFinish(UParticleSystemComponent* Particle);
};


