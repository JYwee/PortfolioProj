// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryItemSlot.h"

void UInventoryItemSlot::NativeConstruct()
{
	ItemIconImage = nullptr;

	ItemIconBack = nullptr;

	ItemCountBlock = nullptr;

	ItemCountValue = 0;

	if (ItemIconImage == nullptr)
	{
		//ItemIconImage->SetColorAndOpacity(FLinearColor::Black);
	}
	if (ItemCountBlock == nullptr)
	{
		//ItemCountBlock->Text = FText::FromString(FString::FromInt(ItemCountValue));
	}
}
