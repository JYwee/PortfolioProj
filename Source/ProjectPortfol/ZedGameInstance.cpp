// Fill out your copyright notice in the Description page of Project Settings.


#include "ZedGameInstance.h"
#include "Data/ObjDataTable.h"
#include "Ai/NpcCharacter.h"
#include "WeaponDataTable.h"
#include "Data/ObjDataTable.h"
#include "Data/MonsterDataTable.h"
#include "Data/BossDataTable.h"
#include "Data/SubClassData.h"
#include "Data/ItemDataTable.h"
#include "Data/NpcDataTable.h"
#include "Data/SoundDataTable.h"
#include "Interactive/DropItem.h"

FRandomStream UZedGameInstance::MainRandom;

UZedGameInstance::UZedGameInstance() {

	{
		MainRandom.GenerateNewSeed();

		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_Weapon.DT_Weapon'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			WeaponMeshData = DataTable.Object;

			TArray<FName> ArrayName = WeaponMeshData->GetRowNames();

			for (size_t i = 0; i < ArrayName.Num(); i++)
			{
				FWeaponDataTable* FindTable = WeaponMeshData->FindRow<FWeaponDataTable>(ArrayName[i], ArrayName[i].ToString());
			}
		}
	}
	{
		

		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_ObjectInteract.DT_ObjectInteract'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			mObjInteractData = DataTable.Object;

			TArray<FName> ArrayName = mObjInteractData->GetRowNames();

			for (size_t i = 0; i < ArrayName.Num(); i++)
			{
				FObjDataTable* FindTable = mObjInteractData->FindRow<FObjDataTable>(ArrayName[i], ArrayName[i].ToString());
			}
		}
	}

	///Script/Engine.DataTable'/Game/Data/DT_Monster.DT_Monster'
	
	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_Monster.DT_Monster'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			mMonsterData = DataTable.Object;
		}

	}

	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_BossDesertDragon.DT_BossDesertDragon'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			mBossData = DataTable.Object;

			TArray<FName> ArrayName = mBossData->GetRowNames();

			for (size_t i = 0; i < ArrayName.Num(); i++)
			{
				FBossDataTable* FindTable = mBossData->FindRow<FBossDataTable>(ArrayName[i], ArrayName[i].ToString());
			}
		}

	}

	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_SubClass.DT_SubClass'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			mSubClassData = DataTable.Object;
		}
	}

	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_Item.DT_Item'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			mDropItemData = DataTable.Object;
		}
	}
	
	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_Npc.DT_Npc'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			mCrowNpcData = DataTable.Object;
		}
	}


	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_Sound.DT_Sound'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			mSoundData = DataTable.Object;
		}
	}

	//mBossData
	/// Script / Engine.DataTable'/Game/Data/DT_BossDesertDragon.DT_BossDesertDragon'


	//// /Script/Engine.DataTable'/Game/Data/DT_Weapon.DT_Weapon'
	////DataPath = TEXT("");
	//ConstructorHelpers::FObjectFinder<UDataTable> DataTable2(*DataPath);

	//if (DataTable2.Succeeded())
	//{

	//}
	//mSubClassData;


}

UZedGameInstance::~UZedGameInstance() {

}

UStaticMesh* UZedGameInstance::GetMesh(FName name)
{
	if (nullptr == WeaponMeshData)
	{
		return nullptr;
	}

	FWeaponDataTable* FindTable = WeaponMeshData->FindRow<FWeaponDataTable>(name, name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable->weaponMesh;
}

TSubclassOf<UObject> UZedGameInstance::GetSubClassData(FName name)
{
	if (nullptr == mSubClassData)
	{
		return nullptr;
	}

	FSubClassData* FindTable = mSubClassData->FindRow<FSubClassData>(name, name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable->Object;
}

FMonsterDataTable* UZedGameInstance::GetMonsterDataTable(FName _Name)
{
	if (nullptr == mMonsterData)
	{
		return nullptr;
	}

	FMonsterDataTable* FindTable = mMonsterData->FindRow<FMonsterDataTable>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}

FObjDataTable* UZedGameInstance::GetObjInteractData(FName _Name)
{
	if (mObjInteractData == nullptr)
	{
		return nullptr;
	}
	FObjDataTable* FindTable = mObjInteractData->FindRow<FObjDataTable>(_Name, _Name.ToString());

	if (FindTable == nullptr)
	{
		return nullptr;
	}
	return FindTable;
}

FBossDataTable* UZedGameInstance::GetBossDataTable(FName _Name)
{
	if (nullptr == mBossData)
	{
		return nullptr;
	}

	FBossDataTable* FindTable = mBossData->FindRow<FBossDataTable>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}

FItemDataTable* UZedGameInstance::GetItemDataTable(FName name)
{
	if (nullptr == mDropItemData)
	{
		return nullptr;
	}

	FItemDataTable* FindTable = mDropItemData->FindRow<FItemDataTable>(name, name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}
	return FindTable;
}

FNpcDataTable* UZedGameInstance::GetNpcDataTable(FName name)
{
	if (nullptr == mCrowNpcData)
	{
		return nullptr;
	}

	FNpcDataTable* FindTable = mCrowNpcData->FindRow<FNpcDataTable>(name, name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}

FSoundDataTable* UZedGameInstance::GetSoundDataTable(FName name)
{
	
	if (nullptr == mSoundData)
		{
			return nullptr;
		}

	FSoundDataTable* FindTable = mSoundData->FindRow<FSoundDataTable>(name, name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}

void UZedGameInstance::DropItem(FName tagActorType, FVector dropLocation)
{
	TSubclassOf<UObject> dropItemObj = GetSubClassData(TEXT("DropItem"));
	for (int i = 0; i < 3; ++i)
	{
		AActor* Actor = GetWorld()->SpawnActor<AActor>(dropItemObj);
		Actor->SetActorLocation(dropLocation + FVector(0, 0, 20.f));
		ADropItem* dropItem = Cast<ADropItem>(Actor);

		if (dropItem == nullptr || dropItem->IsValidLowLevel() == false)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> dropItem == nullptr"), __FUNCTION__, __LINE__);
			return;
		}
		//inst->GetItemDataTable()
		//dropItemObj.


		if (i == 0)
		{
			dropItem->Init(GetItemDataTable("bracer01"));
			//mDropItemArray.Add(dropItem);
		}
		else if (i == 1) {
			dropItem->Init(GetItemDataTable("Crystal_01"));
			//mDropItemArray.Add(dropItem);
		}
		else if (i == 2) {
			dropItem->Init(GetItemDataTable("Gold"));
			//mDropItemArray.Add(dropItem);
		}
	}
}

