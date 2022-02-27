// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectGameMode.h"
#include "Player/Select/SelectPlayerController.h"
#include "Player/Select/SelectPawn.h"

ACharacterSelectGameMode::ACharacterSelectGameMode()
{
	static ConstructorHelpers::FClassFinder<UCharacterSelectWidget>	SelectWidgetClassAsset(TEXT("WidgetBlueprint'/Game/UI/UI_CharacterSelect.UI_CharacterSelect_C'"));

	if (SelectWidgetClassAsset.Succeeded())
		m_CharacterSelectWidgetClass = SelectWidgetClassAsset.Class;

	DefaultPawnClass = ASelectPawn::StaticClass();

	PlayerControllerClass = ASelectPlayerController::StaticClass();
}

void ACharacterSelectGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (m_CharacterSelectWidgetClass)
	{
		m_CharacterSelectWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), m_CharacterSelectWidgetClass);

		if (m_CharacterSelectWidget)
			m_CharacterSelectWidget->AddToViewport();
	}
}