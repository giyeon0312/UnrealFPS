// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/TreeView.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UTreeView* m_Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UButton* m_CloseButton;

	class UQuestCategoryData* m_PrevSelect;

	TArray<class UQuestCategoryData*>	m_ProgressQuest;
	TArray<class UQuestCategoryData*>	m_CompleteQuest;

public:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
	void InitList();

public:
	UFUNCTION()
	void CloseButtonClicked();

public:
	UFUNCTION() //델리게이트용 함수로 사용할 것이므로
	void ItemClick(UObject* Item);

	UFUNCTION()
	void ItemDoubleClick(UObject* Item);

	UFUNCTION()
	void ItemHovered(UObject* Item, bool IsHobered);

	UFUNCTION()
	void ItemSelectionChanged(UObject* Item, bool IsSelection);

	UFUNCTION()
	void ItemChildren(UObject* Item, TArray<UObject*>& ItemArray);

	
//public:
//	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
//	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
//	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
//	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
//	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
//	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
//	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
//	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
//	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
//	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};
