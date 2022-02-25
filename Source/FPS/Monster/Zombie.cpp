// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"

AZombie::AZombie()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZombie::BeginPlay()
{
	Super::BeginPlay();

}

void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void  AZombie::NormalAttack()
{

}
