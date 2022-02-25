// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "../Player/PlayerCharacter.h" 

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	m_CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::CloseButtonClicked);


}

void UInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryWidget::CloseButtonClicked()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
//
//void UInventoryWidget::ItemClick(UObject* Item)
//{
//	//UInventoryListItemData* Data = Cast<UInventoryListItemData>(Item);
//
//	//APlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();
//	////이 플레이어 컨틀롤러가 현재 빙의되어있는 폰이 플레이어이므로 가져오는데APlayerCharacter타입으로 가져오는 것이다.
//
//	//if (Player)
//	//{
//	//	switch (Data->GetItemType())
//	//	{
//	//	case EItemType::Weapon:
//	//		Player->SetWeapon(Data->GetItemMesh());
//	//		break;
//	//	case EItemType::Armor:
//	//		break;
//	//	case EItemType::HPPotion,
//	//		break;
//	//	case EItemType::MPPotion,   
//	//		break;
//	//	}
//	//}
//}
//
//void UInventoryWidget::ItemDoubleClick(UObject* Item)
//{
////	UInventoryListItemData* Data = Cast<UInventoryListItemData>(Item);
////
////	APlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();
////	//이 플레이어 컨틀롤러가 현재 빙의되어있는 폰이 플레이어이므로 가져오는데APlayerCharacter타입으로 가져오는 것이다.
////
////	if (Player)
////	{
////		switch (Data->GetItemType())
////		{
////		case EItemType::Weapon:
////			break;
////		case EItemType::Armor:
////			break;
////		case EItemType::HPPotion:
////	 	    Player->AddHP(Data->GetItempOption(EItemOption::HPRecovery));
////			m_InvenList->RemoveItem(Item);
////			break;
////		case EItemType::MPPotion:   
////	 	    Player->AddMP(Data->GetItempOption(EItemOption::MPRecovery));
////			break;
////		}
////	}
//}
//
//void UInventoryWidget::ItemHovered(UObject* Item, bool IsHobered)
//{
//}
//
//void UInventoryWidget::ItemSelectionChange(UObject* Item, bool IsSelection)
//{/*
//	UInventoryListItemData* Data = Cast< UInventoryListItemData>(Item);
//
//	if(Data)*/
//}


