// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "UIHpBar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UUIHpBar : public UUserWidget
{
	GENERATED_BODY()



public:
	UPROPERTY(Category = "UiHpBar", EditAnywhere, BlueprintReadWrite)
	UImage* mBackGroundProgress = nullptr;

	UPROPERTY(Category = "UiHpBar", EditAnywhere, BlueprintReadWrite)
	UProgressBar* mHpProgressBar;
	
protected:

	void NativeConstruct() override;
};
