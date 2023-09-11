// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/DropItem.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"

ADropItem::ADropItem()
{
	PrimaryActorTick.bCanEverTick = true;

	
	mNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	mNiagaraComp->SetupAttachment(RootComponent, TEXT("attachNigara"));

	mCapsuleComponent->ComponentTags.Add("DropItem");
	//mCapsuleComponent->SetCapsuleSize(150.f, 150.f, true);
	Tags.Add("DropItem");
}

ADropItem::~ADropItem()
{
}

void ADropItem::BeginPlay()
{
	Super::BeginPlay();
	//mNiagaraComp->GetAsset()
	//UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayColor(mNiagaraComp, TEXT("ArrColor"), ArrayData);
	
}

bool ADropItem::Init(FItemDataTable* itemData)
{
	if (itemData == nullptr)
	{
		return false;
	}
	mItemData = itemData;

	mNameItem = itemData->NameItem;

	mExplain = itemData->Explain;


	mItemMesh = itemData->ItemMesh;
	GetStaticMeshComponent()->SetStaticMesh(mItemMesh);

	mObject = itemData->Object;

	mItemType = itemData->ItemType;

	mRank = itemData->Rank;

	mStackSize = itemData->StackSize;

	if (mStackSize > 1)
	{
		mCount = 10;		//임시로 10개 생성  나중에 랜덤 생성 해야함.
	}

	switch (mRank)
	{
	case RankItem::SS:
		mNiagaraComp->SetColorParameter(TEXT("ArrColor_2"), FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case RankItem::S:
		mNiagaraComp->SetColorParameter(TEXT("ArrColor_2"), FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
		break;
	case RankItem::A:
		mNiagaraComp->SetColorParameter(TEXT("ArrColor_2"), FLinearColor(1.0f, 1.0f, 1.0f, 0.8f));
		break;
	case RankItem::Normal:
		mNiagaraComp->SetColorParameter(TEXT("ArrColor_2"), FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
		break;
	default:
		mNiagaraComp->SetColorParameter(TEXT("ArrColor_2"), FLinearColor(0.2f, 0.2f, 0.2f, 0.4f));
		break;
	}

	mCapsuleComponent->SetCapsuleSize(150.f, 150.f, true);

	return true;
}
