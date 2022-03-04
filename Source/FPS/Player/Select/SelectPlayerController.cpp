// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayerController.h"
#include "SelectCharacter.h"
#include "../../CharacterSelectGameMode.h"
#include "../../UI/CharacterSelectWidget.h"
#include "../../FPSGameInstance.h"


ASelectPlayerController::ASelectPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	m_SelectCharacter = nullptr;
}

void ASelectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI	mode;

	SetInputMode(mode);

	//TArray<AActor*>	FindActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMediaPlayerActor::StaticClass(), FindActors);

	//if (FindActors.Num() > 0)
	//	m_MediaActor = Cast<AMediaPlayerActor>(FindActors[0]);
}

void ASelectPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	Picking();
}

void ASelectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("MouseLButton"), EInputEvent::IE_Pressed, this,
		&ASelectPlayerController::MouseLClick);

	InputComponent->BindAction(TEXT("MouseLButton"), EInputEvent::IE_Released, this,
		&ASelectPlayerController::MouseLUp);
}

void ASelectPlayerController::Picking()
{
	FHitResult	result;

	bool Collision = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false, result);

	if (Collision)
	{
		ASelectCharacter* SelectPlayer = Cast<ASelectCharacter>(result.GetActor());

		if (SelectPlayer)
		{
			if (SelectPlayer != m_SelectCharacter)
			{
				m_SelectCharacter = SelectPlayer;
				m_SelectCharacter->EnableOutLine(true);
			}
		}
		else
		{
			if (m_SelectCharacter)
			{
				m_SelectCharacter->EnableOutLine(false);
				m_SelectCharacter = nullptr;
			}
		}
	}
	else
	{
		if (m_SelectCharacter)
		{
			m_SelectCharacter->EnableOutLine(false);
			m_SelectCharacter = nullptr;
		}
	}
}

void ASelectPlayerController::MouseLClick()
{
	ACharacterSelectGameMode* GameMode = Cast<ACharacterSelectGameMode>(GetWorld()->GetAuthGameMode());

	UCharacterSelectWidget* SelectWidget = nullptr;

	if (GameMode)
		SelectWidget = GameMode->GetCharacterSelectWidget();

	// 현재 선택된 캐릭터가 있으면 UI와 연동
	if (m_SelectCharacter)
	{
		UFPSGameInstance* GameInst = Cast<UFPSGameInstance>(GetWorld()->GetGameInstance());

		if (GameInst)
			GameInst->SetSelectJob(m_SelectCharacter->GetJob());

		if (SelectWidget)
		{
			SelectWidget->StartEnable(true);
			SelectWidget->SetInputNameVisible(true);
		}
	}

	else
	{
		if (SelectWidget)
		{
			SelectWidget->StartEnable(false);
			SelectWidget->SetInputNameVisible(false);
		}
	}
}

void ASelectPlayerController::MouseLUp()
{
}
