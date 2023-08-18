// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIUnderBarSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UUIUnderBarSlot : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility mSlotBackVisibility = ESlateVisibility::Visible;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility mIconVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	ESlateVisibility mSlotTextVisibility = ESlateVisibility::Hidden;

	//UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
	//ItemType ItemTypeValue = ItemType::NONE;

	/*UPROPERTY(Category = "Icon", EditAnywhere, BlueprintReadWrite)
	UImage* mIconImage = nullptr;

	UPROPERTY(Category = "Icon", EditAnywhere, BlueprintReadWrite)
	UImage* mIconBack = nullptr;

	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
	UTextBlock* mTextBlock = nullptr;

	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
	int ItemCountValue = 0;*/



};
