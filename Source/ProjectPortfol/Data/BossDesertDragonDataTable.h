// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../ZedEnums.h"
#include "UObject/NoExportTypes.h"
#include "BossDesertDragonDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTPORTFOL_API FBossDesertDragonDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
		FBossDesertDragonDataTable() {}
	~FBossDesertDragonDataTable() {}

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		int SP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		int Att;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		int Def;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		FVector PostionOri;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		TMap<BossDragonAniState, class UAnimMontage*> MapAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		class UBehaviorTree* AI;

	
};
