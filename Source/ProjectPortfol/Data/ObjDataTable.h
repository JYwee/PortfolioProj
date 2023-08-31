// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "ObjDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTPORTFOL_API FObjDataTable : public FTableRowBase
{
	GENERATED_BODY()

	FObjDataTable() {}
	~FObjDataTable() {}

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjData")
		FText NameObj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjData")
		UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjData")
		FText InteractiveText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjData")
		FName Tag_Obj;

};
