// Fill out your copyright notice in the Description page of Project Settings.


#include "ZedGameInstance.h"
#include "ObjDataTable.h"


UZedGameInstance::UZedGameInstance() {

	FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DataTable_Object.DataTable_Object'");
	ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

	if (DataTable.Succeeded())
	{
		int i = 0;
	}

}

UZedGameInstance::~UZedGameInstance() {

}