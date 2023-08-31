// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Data/ObjDataTable.h"
#include "InteracObjData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UInteracObjData : public UObject
{
	GENERATED_BODY()
	
public:
	class UInteracTextSlot* mWidget;
	uint8 mIndex;
	
	AActor* mOnwerActor;

	const FObjDataTable* mObjData;
};
