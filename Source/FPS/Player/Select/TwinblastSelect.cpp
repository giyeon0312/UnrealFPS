// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinblastSelect.h"

ATwinblastSelect::ATwinblastSelect()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Job = EPlayerJob::Archer;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Skins/Tier2/ActionMovie/Meshes/TwinBlast_ActionHero.TwinBlast_ActionHero'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetCapsuleComponent()->SetCapsuleHalfHeight(95.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	//GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Player/Select/BPSelectTwinblast.BPSelectTwinblast_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
}

void ATwinblastSelect::BeginPlay()
{
	Super::BeginPlay();
}


void ATwinblastSelect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATwinblastSelect::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
