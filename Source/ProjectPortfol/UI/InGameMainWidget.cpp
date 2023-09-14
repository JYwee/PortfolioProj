// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameMainWidget.h"

#include "InvenAndStatus.h"

void UInGameMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Inven = Cast<UInventoryUserWidget>(GetWidgetFromName(TEXT("WBP_Inventory")));
	// Inven = Cast<UInventoryUserWidget>(GetWidgetFromName(TEXT("WBP_Status")));

	mInvenAndStatus = Cast<UInvenAndStatus>(GetWidgetFromName(TEXT("UI_InventoryStatus")));
	mAllWidget.Add(Cast<UUserWidget>(GetWidgetFromName(TEXT("UI_InventoryStatus"))));

	mUIMainTextBox = Cast<UMainTextWidget>(GetWidgetFromName(TEXT("UI_MainTextBox")));
	mUIStamina = Cast<UProgressBar>(GetWidgetFromName(TEXT("UI_playerStamina")));

	//TalkTextWindowOnOff = Cast<UInteracTextListWidget>(GetWidgetFromName(TEXT("UI_IntractiveText")));
	//mAllWidget.Add(Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_Status"))));
}

void UInGameMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (mStaminaUIPercent >= 1.f) {
		mStaminaUIOnOff = ESlateVisibility::Hidden;
	}
	else {
		mStaminaUIOnOff = ESlateVisibility::Visible;
	}

}
