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

	void NativeConstruct();

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


	void SetmCrossHairOnOffSwitch()
	{
		StatusWindowOnOff = StatusWindowOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	ESlateVisibility GetCrossHairOnOffOnOff()
	{
		return mCrossHairOnOff;
	}

	void SetCrossHairOnOffOnOff(ESlateVisibility _Visibility)
	{
		mCrossHairOnOff = _Visibility;
	}



private:
	
	class UInvenAndStatus* mInvenAndStatus;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility mInvenStatusWindowOnOff = ESlateVisibility::Hidden;




	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UUserWidget*> mAllWidget;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility StatusWindowOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility TalkTextWindowOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility mCrossHairOnOff = ESlateVisibility::Hidden;


};
