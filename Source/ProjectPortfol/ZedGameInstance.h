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
	
	UPROPERTY(Category = "NpcCharacters", EditAnywhere, BlueprintReadWrite)
		TArray<class ANpcCharacter*> AllNpcCharac;

	UFUNCTION(Category = "Anime", BlueprintCallable)
		TSubclassOf<UObject> GetSubClassData(FName name);

	struct FMonsterDataTable* GetMonsterDataTable(FName _Name);

	struct FObjDataTable* GetObjInteractData(FName _Name);

	struct FBossDataTable* GetBossDataTable(FName _Name);

	struct FItemDataTable* GetItemDataTable(FName name);

	struct FNpcDataTable* GetNpcDataTable(FName name);

	struct FSoundDataTable* GetSoundDataTable(FName name);


	static FRandomStream MainRandom;

	UFUNCTION()
		void DropItem(FName tagActorType, FVector dropLocation);

	//UWorld* mMenuWorld;

private:

	UDataTable* mDropItemData;

	
	UDataTable* mSubClassData;

	UDataTable* WeaponMeshData;

	UDataTable* mMonsterData;

	UDataTable* mBossData;

	UDataTable* mObjInteractData;

	UDataTable* mCrowNpcData;

	UDataTable* mSoundData;

	TArray<UStaticMesh*> ArrWeaponMesh;
};
