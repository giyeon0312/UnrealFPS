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

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)) // �����Ϳ��� �� �� �ֵ��� 
	UBoxComponent* m_Body;															// �ڽ� �浹ü

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)) // �浹ü�� �޽��� ����� �����ϱ� ����
	USceneComponent* m_MeshRoot;													// ����ִ� ��������Ʈ�� �����. �޽��� ���ϰ��踦 ����� �������Ʈ���� �̵����״�.


	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* m_Mesh;


	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)) // �̵������ֱ� ����
	UProjectileMovementComponent* m_Movement;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = true)) // ��ƼŬ�ý��� ������Ʈ
	UParticleSystemComponent* m_Particle;

	float m_Distance;			// ��ų��Ÿ� ���1
	FVector m_StartLocation;	// ��ų��Ÿ� ���2

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Delegate�� ����� �Լ����� �ݵ�� UFUNCTION �Լ��� �������� �Ѵ�.
	UFUNCTION()
	void PrjectileStop(const FHitResult& result);

};
