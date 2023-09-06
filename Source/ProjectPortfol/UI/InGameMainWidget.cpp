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


	//mAllWidget.Add(Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_Status"))));
}