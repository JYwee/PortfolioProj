// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteracTextSlot.h"

void UInteracTextSlot::NativeConstruct()
{
	Super::NativeConstruct();

	mTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_InteractSlot")));
	//mStringData
}

void UInteracTextSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInteracTextSlot::SetItemData(const FObjDataTable* objData)
{
	/*mObjData = objData;

	if (mObjData->InteractiveText.IsEmpty() == true)
	{
		return;
	}
	else
	{
		mTextBlock->SetText(mObjData->InteractiveText);
	}*/
}

void UInteracTextSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	mObjData = Cast<UInteracObjData>(ListItemObject);
	if (mObjData == nullptr) {
		return;
	}
	mTextBlock->SetText(mObjData->mObjData->InteractiveText);
}
