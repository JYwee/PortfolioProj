// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <ZedEnums.h>
#include "UObject/NoExportTypes.h"
#include "SoundDataTable.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct PROJECTPORTFOL_API FSoundDataTable : public FTableRowBase
{
	GENERATED_BODY()

		FSoundDataTable() {}
	~FSoundDataTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<SoundName, class USoundBase*> mAllSoundsMap;
};
