// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryItemSlot.h"
#include "InventoryItemData.h"

void UInventoryItemSlot::SetSlotData(UInventoryItemData* invenSlotData)
{
	InvenSlotData = invenSlotData;

	if (InvenSlotData != nullptr) {
		if (InvenSlotData->mData != nullptr) {
	ItemIconImage->SetBrushFromTexture(Cast<UTexture2D>(invenSlotData->mData->ItemIconImage));
	ItemIconImgVisibility = ESlateVisibility::Visible;
		if (InvenSlotData->mData->StackSize > 1)
		{
			ItemCountValue = InvenSlotData->mCount;
			ItemCountVisibility = ESlateVisibility::Visible;
		}
	}
		else
		{
			ItemIconImgVisibility = ESlateVisibility::Hidden;
			ItemCountVisibility = ESlateVisibility::Hidden;
		}
	}
}

void UInventoryItemSlot::CheckSlotData()
{
	
	if (InvenSlotData == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == ItemData)"), __FUNCTION__, __LINE__);
	}
	else {
	
		if (InvenSlotData->mData != nullptr) {
			ItemIconImage->SetBrushFromTexture(Cast<UTexture2D>(InvenSlotData->mData->ItemIconImage));
			ItemIconImgVisibility = ESlateVisibility::Visible;
			if (InvenSlotData->mData->StackSize > 1)
			{
				if (InvenSlotData->mCount > 1) {
					ItemCountValue = InvenSlotData->mCount;
					ItemCountVisibility = ESlateVisibility::Visible;
				}
				else {
					ItemCountVisibility = ESlateVisibility::Hidden;
				}
			}
			else {
				ItemCountVisibility = ESlateVisibility::Hidden;
			}
		}
		else
		{
			
			ItemIconImgVisibility = ESlateVisibility::Hidden;
			ItemCountVisibility = ESlateVisibility::Hidden;
		}
	}



}

void UInventoryItemSlot::NativeConstruct()
{
	/*ItemIconImage = nullptr;

	ItemIconBack = nullptr;

	ItemCountBlock = nullptr;

	ItemCountValue = 0;*/

	if (ItemIconImage == nullptr)
	{
		//ItemIconImage->SetColorAndOpacity(FLinearColor::Black);
	}
	if (ItemCountBlock == nullptr)
	{
		//ItemCountBlock->Text = FText::FromString(FString::FromInt(ItemCountValue));
	}

	ItemIconBack = Cast<UImage>(GetWidgetFromName(TEXT("SideBack")));
	ItemIconImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	ItemCountBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));

	// 인벤토리 아이템에 있는 UInvenItemData는 인벤토리라면 무조건 가지고 있어야 합니다.
	//ItemData = NewObject<UInvenItemData>();
}
