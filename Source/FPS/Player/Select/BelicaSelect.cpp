
#include "BelicaSelect.h"

ABelicaSelect::ABelicaSelect()
{
	PrimaryActorTick.bCanEverTick = true;


	PrimaryActorTick.bCanEverTick = true;

	m_Job = EPlayerJob::Archer;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("SkeletalMesh'/Game/ParagonLtBelica/Characters/Heroes/Belica/Meshes/Belica.Belica'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetCapsuleComponent()->SetCapsuleHalfHeight(103.f);
	GetCapsuleComponent()->SetCapsuleRadius(34.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	//GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>	SelectAnimAsset(TEXT("AnimBlueprint'/Game/Player/Select/BPSelectBelica.BPSelectBelica_C'"));

	if (SelectAnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(SelectAnimAsset.Class);
}

void ABelicaSelect::BeginPlay()
{
	Super::BeginPlay();
}


void ABelicaSelect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABelicaSelect::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
