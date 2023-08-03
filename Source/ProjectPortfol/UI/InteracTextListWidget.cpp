// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteracTextListWidget.h"
#include "../ZedGameInstance.h"
void UInteracTextListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//textList = Cast<UListView>(GetWidgetFromName(TEXT("")))

	UZedGameInstance* gameInstance = GetWorld()->GetGameInstance<UZedGameInstance>();




}
void UInteracTextListWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick( MyGeometry, InDeltaTime);
}
void UInteracTextListWidget::AddInteracTextSlot(UObject* objData, UUserWidget* widgetData)
{

}

void UInteracTextListWidget::NewSlotWidget(UUserWidget* widgetData)
{

}



