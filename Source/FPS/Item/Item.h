// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class FPS_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* m_Mesh;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetMesh(const FString& Path);
	void SetMesh(UStaticMesh* Mesh);
	void SimulatePhysics(bool Simulate);

};
