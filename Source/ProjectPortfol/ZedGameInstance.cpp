// Fill out your copyright notice in the Description page of Project Settings.


#include "ZedGameInstance.h"
#include "Data/ObjDataTable.h"
#include "Ai/NpcCharacter.h"
#include "WeaponDataTable.h"


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


	return nullptr;
}
