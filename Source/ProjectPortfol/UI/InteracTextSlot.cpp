// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteracTextSlot.h"
#include <Interactive/DropItem.h>
#include <Ai/CrowdNpc.h>

void UInteracTextSlot::NativeConstruct()
{
	Super::NativeConstruct();

	mTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_InteractSlot")));

	mArrowImg = Cast<UImage>(GetWidgetFromName(TEXT("Img_Arrow")));
	mArrowBGImg = Cast<UImage>(GetWidgetFromName(TEXT("Img_back_Arrow")));
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

	if (mObjData->mObjData->Tag_Obj.IsEqual(FName("DropItem")))
	{
		ADropItem* item = Cast<ADropItem>(mObjData->mOnwerActor);
		if (item == nullptr || item->IsValidLowLevel() == false)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u) item == nullptr "), __FUNCTION__, __LINE__);
		}
		
		mTextBlock->SetText(FText::FromString(item->mNameItem.ToString() + " " + mObjData->mObjData->InteractiveText.ToString()));
	}
	else if (mObjData->mObjData->Tag_Obj.IsEqual(FName("InteracNPC"))) {
		ACrowdNpc* npc = Cast<ACrowdNpc>(mObjData->mOnwerActor);
		if (npc == nullptr || npc->IsValidLowLevel() == false)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u) item == nullptr "), __FUNCTION__, __LINE__);
		}
		mTextBlock->SetText(FText::FromString(npc->GetNpcName().ToString() + "와 " + mObjData->mObjData->InteractiveText.ToString()));
	}
	else {
		mTextBlock->SetText(mObjData->mObjData->InteractiveText);
	}
}


