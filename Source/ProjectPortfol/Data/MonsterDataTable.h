// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../ZedEnums.h"
#include "UObject/NoExportTypes.h"
#include "MonsterDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTPORTFOL_API FMonsterDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
		FMonsterDataTable() {}
	~FMonsterDataTable() {}

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
		USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
		int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
		int SP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
		int Att;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
		int Def;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
		FVector PostionOri;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
		TMap<NPCAniState, class UAnimMontage*> MapAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MonsterData")
		class UBehaviorTree* AI;

	
};
