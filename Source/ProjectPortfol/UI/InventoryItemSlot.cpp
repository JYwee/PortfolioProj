// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryItemSlot.h"
#include "InventoryItemData.h"

void UInventoryItemSlot::SetSlotData(UInventoryItemData* invenSlotData)
{
	InvenSlotData = invenSlotData;

	if (InvenSlotData != nullptr) {
		if (InvenSlotData->mData != nullptr) {
	ItemIconImage->SetBrushFromTexture(Cast<UTexture2D>(invenSlotData->mData->ItemIconImage));

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

	// �κ��丮 �����ۿ� �ִ� UInvenItemData�� �κ��丮��� ������ ������ �־�� �մϴ�.
	//ItemData = NewObject<UInvenItemData>();
}
