// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryTileWidget.h"
#include "InventoryListItemData.h"
#include "../FPSGameInstance.h"
#include "../Player/PlayerCharacter.h"

void UInventoryTileWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_InvenTile = Cast<UTileView>(GetWidgetFromName(TEXT("InvenTile")));
	m_ItemDesc = Cast<UInventoryItemDesc>(GetWidgetFromName(TEXT("UI_ItemDesc")));

	m_InvenTile->OnItemClicked().AddUObject(this, &UInventoryTileWidget::ItemClick);
	m_InvenTile->OnItemDoubleClicked().AddUObject(this, &UInventoryTileWidget::ItemDoubleClick);
	m_InvenTile->OnItemIsHoveredChanged().AddUObject(this, &UInventoryTileWidget::ItemHovered);
	//m_InvenTile->OnItemSelectionChanged().AddUObject(this, &UInventoryTileWidget::ItemSelectionChanged);

	InitList();
}

void UInventoryTileWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UInventoryTileWidget::InitList()
{
	UFPSGameInstance* GameInst = Cast<UFPSGameInstance>(GetWorld()->GetGameInstance());
	if (GameInst)
	{
		TArray<FString> ItemName;
		ItemName.Add(TEXT("Gun"));
		ItemName.Add(TEXT("Sword"));
		ItemName.Add(TEXT("HPPotion"));

		for (int32 i = 0; i < 100; ++i)
		{
			//UObject* obj= NewObject<UObject>(this,UObject::StaticClass());이렇게 UObject를 직접 생성하면 패키징할 때 크래쉬나므로 절대 안된다!!
			UInventoryListItemData* Item = NewObject<UInventoryListItemData>(this, UInventoryListItemData::StaticClass()); //이렇게 UObject를 상속받은 UInventoryListItemData클래스를 생성해야한다.

			int32 ItemIndex = FMath::RandRange(0, 2);//DTItemInfo데이터테블에 있는 아이템 개수
			const FItemTableInfo* Info = GameInst->FindItemInfo(ItemName[ItemIndex]);
			if (Info)
			{
				Item->SetItemName(Info->Name);
				Item->SetItemType(Info->Type);
				Item->SetIconTexture(Info->IconTexture);
				Item->SetMesh(Info->Mesh);
				Item->SetItemOption(Info->OptionArray);

				m_InvenTile->AddItem(Item);	//UI_InventoryListItem의 인터페이스가 호출된다.
			}
		//UInventoryListItemData를 블루프린트에서 사용할수 있도록 클래스 선언 위에 UCLASS(BluePrintType)을 추가한다.
		}
	}

}

void UInventoryTileWidget::ItemClick(UObject* Item)
{
	UInventoryListItemData* Data = Cast<UInventoryListItemData>(Item);

	APlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();
	//이 플레이어 컨틀롤러가 현재 빙의되어있는 폰이 플레이어이므로 가져오는데APlayerCharacter타입으로 가져오는 것이다.

	if (Player)
	{
		switch (Data->GetItemType())
		{
		case EItemType::Weapon:
			Player->SetWeapon(Data->GetItemMesh());
			break;
		case EItemType::Armor:
			break;
		case EItemType::HPPotion:
			break;
		case EItemType::MPPotion:
			break;
		}
	}
}

void UInventoryTileWidget::ItemDoubleClick(UObject* Item)
{
	UInventoryListItemData* Data = Cast<UInventoryListItemData>(Item);

	APlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();
	//이 플레이어 컨틀롤러가 현재 빙의되어있는 폰이 플레이어이므로 가져오는데APlayerCharacter타입으로 가져오는 것이다.

	if (Player)
	{
		switch (Data->GetItemType())
		{
		case EItemType::Weapon:
			break;
		case EItemType::Armor:
			break;
		case EItemType::HPPotion:
			Player->AddHP(Data->GetItemOption(EItemOption::HPRecovery)->Option);
			m_InvenTile->RemoveItem(Item);
			break;
		case EItemType::MPPotion:
			Player->AddMP(Data->GetItemOption(EItemOption::MPRecovery)->Option);
			break;
		}
	}
}

void UInventoryTileWidget::ItemHovered(UObject* Item, bool IsHovered)
{
	if (IsHovered)
	{
		UInventoryListItemData* Data = Cast<UInventoryListItemData>(Item);

		m_ItemDesc->SetVisibility(ESlateVisibility::Visible);

		m_ItemDesc->SetItemInfo(Data->GetItemName(), Data->GetItemType(),
			TEXT("Item Description"), Data->GetItemOption());
	}
	else
	{
		UInventoryListItemData* Data = Cast<UInventoryListItemData>(Item);

		m_ItemDesc->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInventoryTileWidget::ItemSelectionChanged(UObject* Item, bool IsSelection)
{/*
	UInventoryListItemData* Data = Cast< UInventoryListItemData>(Item);

	if(Data)*/
}


FReply UInventoryTileWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return result;
}

FReply UInventoryTileWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return result;
}

FReply UInventoryTileWidget::NativeOnMouseMove(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	// 아이템이 보일때만
	// 아이템 설명창의 위치를 마우스의 위치로 지정해준다.
	// 먼저 아이템 설명창의 CanvasPanelSlot을 얻어온다.
	if (m_ItemDesc->GetVisibility() == ESlateVisibility::Visible)
	{
		FVector2D	MousePos = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(m_ItemDesc->Slot); // Slot은 public변수이다.

		if (PanelSlot)
		{
			MousePos.X += 5.f;
			MousePos.Y += 5.f;

			PanelSlot->SetPosition(MousePos);
		}
	}

	//PrintViewport(2.f, FColor::Red, FString::Printf(TEXT("Mouse : %s"), *MousePos.ToString()));

	return result;
}


FReply UInventoryTileWidget::NativeOnMouseWheel(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseWheel(InGeometry, InMouseEvent);

	return result;
}

void UInventoryTileWidget::NativeOnDragDetected(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UInventoryTileWidget::NativeOnDragEnter(const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryTileWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}

bool UInventoryTileWidget::NativeOnDragOver(const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Result = Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	return Result;
}

bool UInventoryTileWidget::NativeOnDrop(const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	return Result;
}

void UInventoryTileWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}
