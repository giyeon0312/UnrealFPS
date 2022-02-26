// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameMode.h"


AStartGameMode::AStartGameMode()
{
	static ConstructorHelpers::FClassFinder<UStartWidget>	StartWidgetClassAsset(TEXT("WidgetBlueprint'/Game/UI/UI_Start.UI_Start_C'"));

	if (StartWidgetClassAsset.Succeeded())
		m_StartWidgetClass = StartWidgetClassAsset.Class;
}

void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (m_StartWidgetClass)
	{
		m_StartWidget = CreateWidget<UStartWidget>(GetWorld(), m_StartWidgetClass);

		if (m_StartWidget)
			m_StartWidget->AddToViewport();
	}

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	FInputModeUIOnly	Mode;

	Controller->SetInputMode(Mode);
	Controller->bShowMouseCursor = true;
}
