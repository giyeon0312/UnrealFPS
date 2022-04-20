// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "../Environment/EnvironmentActor.h"
#include "PlayerCharacter.h"

AMainPlayerController::AMainPlayerController()
{
	bShowMouseCursor = true;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI mode;
	SetInputMode(mode);

	for (auto& CollisionActor : m_CameraCollisionEnvironmentActor)
	{
		CollisionActor->SetCameraCollision(false);
	}

	APlayerCharacter* PlayerActor = Cast<APlayerCharacter>(GetPawn());

	FVector	CameraLoc = PlayerActor->GetCameraPosition();
	FVector	PlayerLoc = PlayerActor->GetActorLocation();

	FCollisionQueryParams	params(NAME_None, false, this);

	TArray<FHitResult>	HitResultArray;

	bool Hit = GetWorld()->LineTraceMultiByChannel(HitResultArray, CameraLoc, PlayerLoc,
		ECollisionChannel::ECC_GameTraceChannel9, params);

	if (Hit)
	{
		for (auto& result : HitResultArray)
		{
			AEnvironmentActor* EnvironmentActor = Cast<AEnvironmentActor>(result.GetActor());
			if (EnvironmentActor)
			{
				if (EnvironmentActor->GetDepthEnable())
				{
					EnvironmentActor->SetCameraCollision(true);
					PrintViewport(1.f, FColor::Red, TEXT("Camera Hit"));
				}

				bool	Overlap = false;

				for (auto& CollisionActor : m_CameraCollisionEnvironmentActor)
				{
					if (CollisionActor == EnvironmentActor)
					{
						Overlap = true;
						break;
					}
				}

				if (!Overlap)
					m_CameraCollisionEnvironmentActor.Add(EnvironmentActor);
			}
		}
	}

	// ��Ͽ� �ִµ� ī�޶�� �浹�� �ȵ����� ��Ͽ��� ���Ÿ� �ؾ��Ѵ�.
	for (int32 i = 0; i < m_CameraCollisionEnvironmentActor.Num();)
	{
		if (!m_CameraCollisionEnvironmentActor[i]->GetCameraCollision())
		{
			m_CameraCollisionEnvironmentActor.RemoveAt(i);
		}
		else
			++i;
	}
}

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}