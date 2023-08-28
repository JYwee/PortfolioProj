// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Data/ItemDataTable.h"
#include "InventoryItemData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UInventoryItemData : public UObject
{
	GENERATED_BODY()
	
public:
	
	class UInventoryItemSlot* mWidget;
	int mCount = 1;
	const FItemDataTable* mData;
};
