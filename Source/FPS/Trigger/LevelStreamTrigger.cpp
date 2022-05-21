// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamTrigger.h"

// Sets default values
ALevelStreamTrigger::ALevelStreamTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelStreamTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelStreamTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelStreamTrigger::BeginOverlapOverride(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PrintViewport(1.f, FColor::Red, TEXT("LevelStreamTrigger On"));

	FLatentActionInfo	Info;
	UGameplayStatics::LoadStreamLevel(GetWorld(), *m_LevelName, true, false, Info);
}

void ALevelStreamTrigger::EndOverlapOverride(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	PrintViewport(1.f, FColor::Red, TEXT("LevelStreamTrigger Off"));

	FLatentActionInfo	Info;
	UGameplayStatics::UnloadStreamLevel(GetWorld(), *m_LevelName, Info, true);
}
