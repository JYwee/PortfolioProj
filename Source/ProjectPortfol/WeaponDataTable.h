// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "WeaponDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTPORTFOL_API FWeaponDataTable : public FTableRowBase
{
	GENERATED_BODY()

		FWeaponDataTable() {}
	~FWeaponDataTable() {}

public:
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataObj")
	//	FName ActorName;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataObj")
	//	TSubclassOf<AActor> mActor;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_WeaponDATA")
		UStaticMesh* weaponMesh;
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_WeaponDATA")
		int attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DT_WeaponDATA")
		int intelli;

};
