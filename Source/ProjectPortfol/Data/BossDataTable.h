// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../ZedEnums.h"
#include "UObject/NoExportTypes.h"
#include "BossDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTPORTFOL_API FBossDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
		FBossDataTable() {}
	~FBossDataTable() {}

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		FName Subtitle;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		int HealthPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		int ShieldPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		int Stemina;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		int Att;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		int Def;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
	BossPhase Phase;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		FVector PostionOri;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		TMap<BossDragonAIControlState, class UAnimMontage*> MapAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossMonsterData")
		class UBehaviorTree* AI;

	
};
