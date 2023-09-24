// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteracTextListWidget.h"
#include "../ZedGameInstance.h"
#include "InteracTextSlot.h"
#include "InteracObjData.h"
//#include <UObject/Object.h>


void UInteracTextListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mListView = Cast<UListView>(GetWidgetFromName(TEXT("InteracTextListView")));

	UZedGameInstance* gameInstance = GetWorld()->GetGameInstance<UZedGameInstance>();
	
	//mListView->OnEntryWidgetReleased().AddUFunction(mListView, UListView::Han);

	/*for (int i = 0; i < 5; ++i)
	{
	UInteracObjData* Data = NewObject<UInteracObjData>();
	Data->mObjData = gameInstance->GetObjInteractData("TeleportGate");
	mListView->AddItem(Data);

	}*/
	
	//mFocusNowObjData = mListView->GetListItems()[0];

}
void UInteracTextListWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick( MyGeometry, InDeltaTime);

	if (mListView->GetListItems().Num() == 1) {
		if (mFocusNowObjData == nullptr) {
			mFocusNowObjData = mListView->GetListItems()[0];
		}
	}
}


UObject* UInteracTextListWidget::GetUpFocusSlotObj() 
{
	if (mListView->GetListItems().Num() == 0) {
		return nullptr;
	}
	/*else if (mListView->GetListItems().Num() == 1)
	{
		return mFocusNowObjData;
	}*/

	for (int i = 0; i < mListView->GetListItems().Num(); ++i)
	{
		UObject* SlotData = mListView->GetListItems()[i];

		if (SlotData == nullptr)
		{
			return nullptr;
		}

		if (mFocusNowObjData == SlotData)
		{
			if (i == 0)
			{
				return mFocusNowObjData;
			}

			UInteracObjData* SlotInteracData = Cast<UInteracObjData>(mFocusNowObjData);

			SlotInteracData->mWidget->mArrowFocusVisibility = ESlateVisibility::Hidden;
			
			mFocusNowObjData = mListView->GetListItems()[i - 1];;

			UInteracObjData* nextSlotData = Cast<UInteracObjData>(mFocusNowObjData);
			
			if (nextSlotData->mWidget != nullptr) { // 여러개 한번에 튀어나오는 경우 위젯 생성 전에 위젯 호출하는 경우가 있음.
				nextSlotData->mWidget->mArrowFocusVisibility = ESlateVisibility::Visible;
			}
			

			return mFocusNowObjData;
		}
	}
	return mFocusNowObjData;

}

UObject* UInteracTextListWidget::GetDownFocusSlotObj()
{
	if (mListView->GetListItems().Num() == 0) {
		return nullptr;
	}
	/*else if (mListView->GetListItems().Num() == 1)
	{
		return mFocusNowObjData;
	}*/

	for (int i = 0; i < mListView->GetListItems().Num(); ++i)
	{
		UObject* SlotData = mListView->GetListItems()[i];

		if (SlotData == nullptr)
		{
			return nullptr;
		}

		if (mFocusNowObjData == SlotData)
		{
			if (i == mListView->GetListItems().Num() - 1)
			{
				return mFocusNowObjData;
			}

			UInteracObjData* SlotInteracData = Cast<UInteracObjData>(mFocusNowObjData);

			SlotInteracData->mWidget->mArrowFocusVisibility = ESlateVisibility::Hidden;

			mFocusNowObjData = mListView->GetListItems()[i + 1];;

			UInteracObjData* nextSlotData = Cast<UInteracObjData>(mFocusNowObjData);

			if (nextSlotData->mWidget != nullptr) { // 여러개 한번에 튀어나오는 경우 위젯 생성 전에 위젯 호출하는 경우가 있음.
				nextSlotData->mWidget->mArrowFocusVisibility = ESlateVisibility::Visible;
			}
			
			return mFocusNowObjData;
		}
	}
	return mFocusNowObjData;
}

void UInteracTextListWidget::Function(UUserWidget* _Data)
{
}


void UInteracTextListWidget::AddInteracTextSlot(UObject* objData, UUserWidget* widgetData)
{
	UZedGameInstance* gameInstance = GetWorld()->GetGameInstance<UZedGameInstance>();

	UInteracTextSlot* ItemSlotWidget = Cast<UInteracTextSlot>(widgetData);
	UInteracObjData* InvenSlotData = Cast<UInteracObjData>(objData);

	if (nullptr == ItemSlotWidget)
	{
		return;
	}

	
	//ItemSlotWidget->mArrowFocusVisibility = ESlateVisibility::Hidden;
	InvenSlotData->mWidget = ItemSlotWidget;


	if (mListView->GetListItems().Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) mListView->GetListItems something worng "), __FUNCTION__, __LINE__);
		return;
	}
	else if(mListView->GetListItems().Num() == 1)
	{
		InvenSlotData->mIndex = mListView->GetListItems().Num() - 1;
		mFocusNowObjData = objData;
		//ItemSlotWidget->mArrowFocusVisibility = ESlateVisibility::Visible;
	}
	else
	{
		InvenSlotData->mIndex = mListView->GetListItems().Num() - 1;
		ItemSlotWidget->mArrowFocusVisibility = ESlateVisibility::Hidden;
	}

	if (mFocusNowObjData == objData)     // 여러개 한번에 튀어나오는 경우 위젯 생성 전에 위젯 호출하는 경우가 있어, 생성 될때 다시 호출하여 비지블로 세팅함.
	{
		ItemSlotWidget->mArrowFocusVisibility = ESlateVisibility::Visible;
	}

	//mListView->AddItem(objData);
	ItemSlotWidget->SetItemData(InvenSlotData->mObjData);

	//해야하는게 캡슐 충돌시 여기에서 슬롯이 추가되면서 main위젯에서 비지블을 해야함.
	//mListView->AddItem(objData);

}

void UInteracTextListWidget::NewSlotWidget(UUserWidget* widgetData)
{
	
}



