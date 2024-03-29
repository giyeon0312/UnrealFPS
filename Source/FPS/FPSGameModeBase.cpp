// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSGameModeBase.h"
#include "Player/MainPlayerController.h"
#include "Player/Twinblast.h"
#include "FPSGameInstance.h"

AFPSGameModeBase::AFPSGameModeBase()
{
	//static ConstructorHelpers::FClassFinder<ACharacter>PlayerAsset(TEXT("Blueprint'/Game/Player/BPTwinblast.BPTwinblast_C'"));

	//if (PlayerAsset.Succeeded())
	//	DefaultPawnClass = PlayerAsset.Class;

	static ConstructorHelpers::FClassFinder<UMainWidget>	MainWidgetClassAsset(TEXT("WidgetBlueprint'/Game/UI/UI_MainWidget.UI_MainWidget_C'"));
	if (MainWidgetClassAsset.Succeeded())
		m_MainWidgetClass = MainWidgetClassAsset.Class;
	PlayerControllerClass = AMainPlayerController::StaticClass(); //UClass����

	static ConstructorHelpers::FClassFinder<UMouseWidget>	MouseWidgetClassAsset(TEXT("WidgetBlueprint'/Game/UI/UI_Mouse.UI_Mouse_C'"));
	if (MouseWidgetClassAsset.Succeeded())
		m_MouseWidgetClass = MouseWidgetClassAsset.Class;
}

void AFPSGameModeBase::InitGame(const FString& MapName,	const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UFPSGameInstance* GameInst = Cast<UFPSGameInstance>(GetWorld()->GetGameInstance());

	if (GameInst)
	{
		EPlayerJob	SelectJob = GameInst->GetSelectJob();

		switch (SelectJob)
		{
		case EPlayerJob::Knight:
			DefaultPawnClass = LoadClass<APlayerCharacter>(GetWorld(), TEXT("Blueprint'/Game/Player/BPTwinblast.BPTwinblast_C'"));
			break;
		case EPlayerJob::Archer:
			DefaultPawnClass = LoadClass<APlayerCharacter>(GetWorld(), TEXT("Blueprint'/Game/Player/BPBelica.BPBelica_C'"));
			break;
		case EPlayerJob::Magicion:
			DefaultPawnClass = LoadClass<APlayerCharacter>(GetWorld(), TEXT("Blueprint'/Game/Player/BPTwinblast.BPTwinblast_C'"));
			break;
		}
	}
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

	if (m_MouseWidgetClass)
	{
		m_MouseWidget = CreateWidget<UMouseWidget>(GetWorld(), m_MouseWidgetClass);

		if (m_MouseWidget)
			GetWorld()->GetFirstPlayerController()->SetMouseCursorWidget(EMouseCursor::Default, m_MouseWidget);
	}
}