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

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemBackGroundVisibility = ESlateVisibility::Visible;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemIconImgVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility ItemCountVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ItemType ItemTypeValue = ItemType::Etc;

	UPROPERTY(Category = "Icon", EditAnywhere, BlueprintReadWrite)
	UImage* ItemIconImage = nullptr;

	UPROPERTY(Category = "Icon", EditAnywhere, BlueprintReadWrite)
	UImage* ItemIconBack = nullptr;

	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
	UTextBlock* ItemCountBlock = nullptr;

	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
	int ItemCountValue = 0;
	
protected:


	void NativeConstruct() override;

};
