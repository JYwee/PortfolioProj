// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InvenAndStatus.h"
#include "InventoryItemSlot.h"
#include "InventoryItemData.h"

//#include ""

void UInvenAndStatus::AddInvenItem(UObject* data, UUserWidget* widget)
{
	
	//UZedGameInstance* gameInstance = GetWorld()->GetGameInstance<UZedGameInstance>();

	UInventoryItemSlot* ItemSlotWidget = Cast<UInventoryItemSlot>(widget);
	UInventoryItemData* InvenSlotData = Cast<UInventoryItemData>(data);

	if (nullptr == ItemSlotWidget)
	{
		return;
	}


	//ItemSlotWidget->mArrowFocusVisibility = ESlateVisibility::Hidden;
	InvenSlotData->mWidget = ItemSlotWidget;
	
	//ItemSlotWidget->InvenSlotData = InvenSlotData;
	ItemSlotWidget->SetSlotData(InvenSlotData);
	//UInventoryItemSlot::SetSlotData(UInventoryItemData * invenSlotData)
	
	//InvenSlotData->mCount


	//mListView->AddItem(objData);
	//ItemSlotWidget->SetItemData(InvenSlotData->mObjData);

}
void UInvenAndStatus::NativeConstruct()
{
	Super::NativeConstruct();

	mInvenList = Cast<UTileView>(GetWidgetFromName(TEXT("TileView_Item")));
}

void UInvenAndStatus::AddGameItem(const struct FItemDataTable* data)
{

}
void UInvenAndStatus::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	const TArray<UObject*>& Items = mInvenList->GetListItems();
	for (size_t i = 0; i < Items.Num(); i++)
	{
		UInventoryItemData* tmpItemData = Cast<UInventoryItemData>(Items[i]);


		if (nullptr == tmpItemData->mWidget)
		{			
			continue;
		}

		UInventoryItemSlot* InvenSlotData = tmpItemData->mWidget;
		InvenSlotData->CheckSlotData();
	}

}