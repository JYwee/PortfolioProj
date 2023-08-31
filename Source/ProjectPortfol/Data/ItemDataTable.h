// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <ZedEnums.h>
//#include <Components/>
#include "UObject/NoExportTypes.h"
#include "ItemDataTable.generated.h"

/**
 *
 */





USTRUCT(BlueprintType)
struct PROJECTPORTFOL_API FItemDataTable : public FTableRowBase
{
	GENERATED_BODY()

		FItemDataTable() {}
	~FItemDataTable() {}

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FText NameItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	FText Explain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	UStaticMesh* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	TSubclassOf<UObject> Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	ItemType ItemType;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	RankItem Rank;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	uint8 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	UTexture* ItemIconImage;

};
