// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../ZedEnums.h"
#include "UObject/NoExportTypes.h"
#include "NpcDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTPORTFOL_API FNpcDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
		FNpcDataTable() {}
	~FNpcDataTable() {}

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
		USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
		int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
		int SP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
		bool invincibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
		int Att;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
		int Def;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
		FText Dialog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
	TArray<FVector> PositionPatrol;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
		FVector PostionOri;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
		TMap<NPCEnemyAIControlState, class UAnimMontage*> MapAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrowdNpcData")
	int MaterialIndex;

	
};
