// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Skill1.generated.h"

UCLASS()
class FPS_API ASkill1 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASkill1();

protected:

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)) // 에디터에서 볼 수 있도록 
	UBoxComponent* m_Body;															// 박스 충돌체

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)) // 충돌체를 메쉬의 가운데에 오게하기 위해
	USceneComponent* m_MeshRoot;													// 비어있는 신컴포넌트를 만든다. 메쉬간 상하관계를 만들고 블루프린트에서 이동시켰다.


	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* m_Mesh;


	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)) // 이동시켜주기 위한
	UProjectileMovementComponent* m_Movement;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)) // 파티클시스템 컴포넌트
	UParticleSystemComponent* m_Particle;

	float m_Distance;			// 스킬사거리 방법1
	FVector m_StartLocation;	// 스킬사거리 방법2

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Delegate에 등록할 함수들은 반드시 UFUNCTION 함수로 만들어줘야 한다.
	UFUNCTION()
	void PrjectileStop(const FHitResult& result);

};
