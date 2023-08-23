// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/DropItem.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"

ADropItem::ADropItem()
{
	PrimaryActorTick.bCanEverTick = true;

	
	mNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	mNiagaraComp->SetupAttachment(RootComponent, TEXT("attachNigara"));
}

ADropItem::~ADropItem()
{
}

void ADropItem::BeginPlay()
{
	Super::BeginPlay();
	//mNiagaraComp->GetAsset()
	//UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayColor(mNiagaraComp, TEXT("ArrColor"), ArrayData);

	switch (mRank)
	{
	default:
	{
		mNiagaraComp->SetColorParameter(TEXT("ArrColor_2"), FLinearColor(0.5f, 0.5f, 1.5f, 1.0f));
		break;
	}
	case 1:
	{
		mNiagaraComp->SetColorParameter(TEXT("ArrColor_2"), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}
	case 2:
	{
		break;
	}

		
	}
}
