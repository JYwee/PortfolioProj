// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIHpBar.h"

void UUIHpBar::NativeConstruct()

{
	mBackGroundProgress = Cast<UImage>(GetWidgetFromName(TEXT("BackgroundHPBar")));
	mHpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgBarHP")));

}
