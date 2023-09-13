// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include <Data/ItemDataTable.h>
#include "InventoryItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UInventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = "InventoryItemSlot", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemBackGroundVisibility = ESlateVisibility::Visible;

	UPROPERTY(Category = "InventoryItemSlot", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemIconImgVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "InventoryItemSlot", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemCountVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "InventoryItemSlot", EditAnywhere, BlueprintReadWrite)
	ItemType ItemTypeValue = ItemType::Etc;

	UPROPERTY(Category = "InventoryItemSlot", EditAnywhere, BlueprintReadWrite)
	UImage* ItemIconImage = nullptr;

	UPROPERTY(Category = "InventoryItemSlot", EditAnywhere, BlueprintReadWrite)
	UImage* ItemIconBack = nullptr;

	UPROPERTY(Category = "InventoryItemSlot", EditAnywhere, BlueprintReadWrite)
	UTextBlock* ItemCountBlock = nullptr;

	UPROPERTY(Category = "InventoryItemSlot", EditAnywhere, BlueprintReadWrite)
	int ItemCountValue = 0;
	
	UPROPERTY(Category = "InventoryItemSlot", EditAnywhere, BlueprintReadWrite)
	class UInventoryItemData* InvenSlotData;

	void SetSlotData(class UInventoryItemData* invenSlotData);

	void CheckSlotData();

protected:


	void NativeConstruct() override;

};
