// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "Engine/GameInstance.h"
#include "ZedGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UZedGameInstance : public UGameInstance
{
	GENERATED_BODY()

		UZedGameInstance();
	~UZedGameInstance();

public:
	UStaticMesh* GetMesh(FName name);
	

private:
	UDataTable* WeaponMeshData;
	TArray<UStaticMesh*> ArrWeaponMesh;
};
