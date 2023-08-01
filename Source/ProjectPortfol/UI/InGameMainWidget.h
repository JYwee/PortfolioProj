// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UInGameMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetStatusWindowOnOffSwitch()
	{
		StatusWindowOnOff = StatusWindowOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	ESlateVisibility GetStatusWindowOnOff()
	{
		return StatusWindowOnOff;
	}

	void SetStatusWindowOnOff(ESlateVisibility _Visibility)
	{
		StatusWindowOnOff = _Visibility;
	}

private:
	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility StatusWindowOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility TalkTextWindowOnOff = ESlateVisibility::Hidden;
};
