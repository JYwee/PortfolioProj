// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "FItemDataTable.generated.h"

/**
 *
 */

UENUM(BlueprintType)
enum class ItemType : uint8
{

}

USTRUCT(BlueprintType)
struct PROJECTPORTFOL_API FItemDataTable : public FTableRowBase
{
	GENERATED_BODY()

		FItemDataTable() {}
	~FItemDataTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSubclassOf<UObject> Object;
};
