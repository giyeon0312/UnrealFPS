#include "EnvironmentActor.h"

// Sets default values
AEnvironmentActor::AEnvironmentActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	SetRootComponent(m_Body);
	m_Mesh->SetupAttachment(m_Body);

	m_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_Mesh->SetCollisionProfileName(TEXT("Building"));

	m_CameraCollision = false;
	m_DepthEnable = false;
}

// Called when the game starts or when spawned
void AEnvironmentActor::BeginPlay()
{
	Super::BeginPlay();

	int32 MtrlSlotCount = m_Mesh->GetNumMaterials();

	for (int32 i = 0; i < MtrlSlotCount; ++i)
	{
		UMaterialInstanceDynamic* Mtrl = m_Mesh->CreateDynamicMaterialInstance(i);
		m_DynamicMaterialArray.Add(Mtrl);
	}
}

// Called every frame
void AEnvironmentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

