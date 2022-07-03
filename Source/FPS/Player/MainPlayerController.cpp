// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "../Environment/EnvironmentActor.h"
#include "PlayerCharacter.h"
#include "../Monster/Monster.h"
#include "../FPSGameModeBase.h"

AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
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

	// 목록에 있는데 카메라와 충돌이 안됐으면 목록에서 제거를 해야한다.
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

	Picking();
}

void AMainPlayerController::Picking()
{
	FHitResult	result;

	bool Collision = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, result);

	AFPSGameModeBase* GameMode = Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode());

	if (Collision)
	{
		if (Cast<AMonster>(result.GetActor()))
		{
			GameMode->GetMouseWidget()->ChangeMouse(EMouseState::Aiming);

			//CurrentMouseCursor = EMouseCursor::Hand;
			APlayerCharacter* PlayerActor = Cast<APlayerCharacter>(GetPawn());

			if (PlayerActor)
			{
				PlayerActor->SetClickMove(true);
				PlayerActor->SetMoveTargetActor(result.GetActor());
				PlayerActor->GetCursorDecal()->SetHiddenInGame(true);
			}
		}
		else if (result.GetActor()->ActorHasTag(TEXT("LandScape")))
		{
			GameMode->GetMouseWidget()->ChangeMouse(EMouseState::Default);

			APlayerCharacter* PlayerActor = Cast<APlayerCharacter>(GetPawn());

			if (PlayerActor)
			{
				PlayerActor->SetClickMove(true);
				PlayerActor->SetMoveTarget(result.ImpactPoint);
				PlayerActor->GetCursorDecal()->SetHiddenInGame(false);
				PlayerActor->GetCursorDecal()->SetWorldLocation(result.ImpactPoint);
				PlayerActor->GetCursorDecal()->SetWorldRotation(result.ImpactNormal.ToOrientationRotator());
			}
		}
		else
		{
			GameMode->GetMouseWidget()->ChangeMouse(EMouseState::Default);
			APlayerCharacter* PlayerActor = Cast<APlayerCharacter>(GetPawn());

			if (PlayerActor)
			{
				PlayerActor->SetClickMove(false);
				PlayerActor->GetCursorDecal()->SetHiddenInGame(true);
			}
			//CurrentMouseCursor = EMouseCursor::Default;
		}
	}
	// 클릭이 안됐을 때
	else
	{
		GameMode->GetMouseWidget()->ChangeMouse(EMouseState::Default);
		APlayerCharacter* PlayerActor = Cast<APlayerCharacter>(GetPawn());

		if (PlayerActor)
		{
			//PlayerActor->SetClickMove(false);
			PlayerActor->GetCursorDecal()->SetHiddenInGame(true);
		}

		//CurrentMouseCursor = EMouseCursor::Default;
	}
}
