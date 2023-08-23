// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/LootObject.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"

ALootObject::ALootObject()
{
	PrimaryActorTick.bCanEverTick = true;

	//static À¸·Î


	mNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	mNiagaraComp->SetupAttachment(RootComponent, TEXT("attachNigara"));


}

void ALootObject::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < mDropItemArray.Num(); ++i)
	{
		//mDropItemArray[i].
	}
	

	//if()
}