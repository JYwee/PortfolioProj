// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UMainTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* mMainTextBlock;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText mMainText;

	UPROPERTY(Category = "UI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FText> mArrMainText;

	int indexMainText = 0;
};
