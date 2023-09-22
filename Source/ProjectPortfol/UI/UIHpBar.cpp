// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIHpBar.h"



void UUIHpBar::NativeConstruct()
{
	Super::NativeConstruct();

	mBackGroundProgress = Cast<UImage>(GetWidgetFromName(TEXT("BackgroundHPBar")));
	mHpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgBarHP")));

}

void UUIHpBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (mHpProgressBar != nullptr)
	{
		if (mHpProgressBar->Percent >= 1.0f)
		{
			Visibility = ESlateVisibility::Hidden;
		}
		else
		{
			Visibility = ESlateVisibility::Visible;
		}
	}
	else {
		mHpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgBarHP")));
	}
}
