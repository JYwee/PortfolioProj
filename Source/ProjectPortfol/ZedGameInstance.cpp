// Fill out your copyright notice in the Description page of Project Settings.


#include "ZedGameInstance.h"
#include "Data/ObjDataTable.h"
#include "Ai/NpcCharacter.h"
#include "WeaponDataTable.h"
#include "Data/ObjDataTable.h"
#include "Data/MonsterDataTable.h"
#include "Data/BossDataTable.h"
#include "Data/SubClassData.h"


UZedGameInstance::UZedGameInstance() {

	{
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

