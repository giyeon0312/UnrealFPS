// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "EnvironmentActor.generated.h"

UCLASS()
class FPS_API AEnvironmentActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnvironmentActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBoxComponent* m_Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool			m_DepthEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool			m_CameraCollision;

	TArray<UMaterialInstanceDynamic*>	m_DynamicMaterialArray;

public:
	bool GetDepthEnable()	const
	{
		return m_DepthEnable;
	}

	void SetCameraCollision(bool Collision)
	{
		m_CameraCollision = Collision;

		if (m_CameraCollision)
			m_Mesh->SetScalarParameterValueOnMaterials(TEXT("SilhouetteEnable"), 1.f);
		else
			m_Mesh->SetScalarParameterValueOnMaterials(TEXT("SilhouetteEnable"), 0.f);
	}

	bool GetCameraCollision()	const
	{
		return m_CameraCollision;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
