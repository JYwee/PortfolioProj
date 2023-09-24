// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainTextWidget.h"
#include "Components/ProgressBar.h"
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

	void SetGameOverWindowOnOffSwitch()
	{
		mGameOverWindowOnOff = mGameOverWindowOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
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

	UMainTextWidget* GetUIMainTextBox()
	{
		return mUIMainTextBox;
	}

	void SetMainTextWindowOnOff(ESlateVisibility _Visibility)
	{
		MainTextWindowOnOff = _Visibility;
	}

	void SetTalkTextWindowOnOff(ESlateVisibility _Visibility)
	{
		TalkTextWindowOnOff = _Visibility;
	}

	void SetStaminaUIOnOff(ESlateVisibility _Visibility)
	{
		mStaminaUIOnOff = _Visibility;
	}

	void SetStaminaPercent(float staminaPercent)
	{
		mStaminaUIPercent = staminaPercent;
	}
	void SetHpPercent(float hpPercent)
	{
		mHpUIPercent = hpPercent;
	}
	
	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility mInvenStatusWindowOnOff = ESlateVisibility::Hidden;

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);


private:
	
	class UInvenAndStatus* mInvenAndStatus;

	UMainTextWidget* mUIMainTextBox;
	
	UProgressBar* mUIStamina;
	
	UProgressBar* mUIHpBar;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mStaminaUIPercent;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float mHpUIPercent;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UUserWidget*> mAllWidget;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility StatusWindowOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility TalkTextWindowOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility mCrossHairOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility MainTextWindowOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility mStaminaUIOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "UIzed", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ESlateVisibility mGameOverWindowOnOff = ESlateVisibility::Hidden;

};
