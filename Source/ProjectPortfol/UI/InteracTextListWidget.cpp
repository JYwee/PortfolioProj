// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteracTextListWidget.h"
#include "../ZedGameInstance.h"
#include "InteracTextSlot.h"
#include "InteracObjData.h"
void UInteracTextListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mListView = Cast<UListView>(GetWidgetFromName(TEXT("InteracTextListView")));

	UZedGameInstance* gameInstance = GetWorld()->GetGameInstance<UZedGameInstance>();
	
	/*for (int i = 0; i < 5; ++i)
	{
	UInteracObjData* Data = NewObject<UInteracObjData>();
	Data->mObjData = gameInstance->GetObjInteractData("TeleportGate");
	mListView->AddItem(Data);

	}*/
	


}
void UInteracTextListWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick( MyGeometry, InDeltaTime);
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
	mListView->AddItem(objData);
	ItemSlotWidget->SetItemData(InvenSlotData->mObjData);

	//해야하는게 캡슐 충돌시 여기에서 슬롯이 추가되면서 main위젯에서 비지블을 해야함.
	//mListView->AddItem(objData);

}

void UInteracTextListWidget::NewSlotWidget(UUserWidget* widgetData)
{
	
}



