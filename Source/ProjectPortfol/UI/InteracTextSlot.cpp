// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteracTextSlot.h"

void UInteracTextSlot::NativeConstruct()
{
	Super::NativeConstruct();

	//mTextBlock = Cast<>
	//mStringData
}

void UInteracTextSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInteracTextSlot::SetItemData(const FText* stringData)
{

}
