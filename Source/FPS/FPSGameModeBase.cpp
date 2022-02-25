// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSGameModeBase.h"
#include "Player/MainPlayerController.h"

AFPSGameModeBase::AFPSGameModeBase()
{
	static ConstructorHelpers::FClassFinder<ACharacter>PlayerAsset(TEXT("Blueprint'/Game/Player/BPTwinblast.BPTwinblast_C'"));

	if (PlayerAsset.Succeeded())
		DefaultPawnClass = PlayerAsset.Class;

	static ConstructorHelpers::FClassFinder<UMainWidget>	MainWidgetClassAsset(TEXT("WidgetBlueprint'/Game/UI/UI_MainWidget.UI_MainWidget_C'"));
	
	if (MainWidgetClassAsset.Succeeded())
		m_MainWidgetClass = MainWidgetClassAsset.Class;

	PlayerControllerClass = AMainPlayerController::StaticClass(); //UClass¡§∫∏
}

void AFPSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (m_MainWidgetClass)
	{
		m_MainWidget = CreateWidget<UMainWidget>(GetWorld(), m_MainWidgetClass);

		if (m_MainWidget)
			m_MainWidget->AddToViewport();
	}
}