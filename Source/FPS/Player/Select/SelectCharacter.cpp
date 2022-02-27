// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacter.h"
#include "SelectAnimInstance.h"

ASelectCharacter::ASelectCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetMesh()->bRenderCustomDepth = true;
	GetMesh()->CustomDepthStencilWriteMask = ERendererStencilMask::ERSM_Default;
	GetMesh()->SetCustomDepthStencilValue(255);

}

void ASelectCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	m_AnimInstance = Cast<USelectAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void ASelectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASelectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASelectCharacter::EnableOutLine(bool Enable)
{
	//if (Enable)
	//	GetMesh()->SetCustomDepthStencilValue(1);

	//else
	//	GetMesh()->SetCustomDepthStencilValue(255);
}
