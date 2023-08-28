// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/LootObject.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include <ZedGameInstance.h>

ALootObject::ALootObject()
{
	PrimaryActorTick.bCanEverTick = true;

	//static À¸·Î


	mNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	mNiagaraComp->SetupAttachment(RootComponent, TEXT("attachNigara"));
	
	mCapsuleComponent->ComponentTags.Add("LootObj");
	Tags.Add("LootObj");
	
	/*ConstructorHelpers::FObjectFinder<UBlueprint> dropItem(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/InteractiveObj/bp_TestDropItem.bp_TestDropItem'"));
	if (dropItem.Object)
	{
		AmmoBlueprint = (UClass*)AmmoItem.Object->GeneratedClass;
	}*/

}

void ALootObject::BeginPlay()
{
	Super::BeginPlay();

	
	

	//if()
}

void ALootObject::TestDropItem()
{
//	ADropItem* dropItem;

	UZedGameInstance* inst = Cast<UZedGameInstance>(GetWorld()->GetGameInstance());

	TSubclassOf<UObject> dropItemObj = inst->GetSubClassData(TEXT("DropItem"));
	for (int i = 0; i < 3; ++i)
	{
		AActor* Actor = GetWorld()->SpawnActor<AActor>(dropItemObj);
		Actor->SetActorLocation(GetActorLocation() + FVector(0, 0, 20.f));
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
			dropItem->Init(inst->GetItemDataTable("apple"));
			mDropItemArray.Add(dropItem);
		}
		else if (i == 1){
			dropItem->Init(inst->GetItemDataTable("gold"));
			mDropItemArray.Add(dropItem);
		}
	}

	Destroy();
	//for (int i = 0; i < mDropItemArray.Num(); ++i)
	//{
	//	
	//	
	//	//mDropItemArray[i]
	//	//SpawnActo
	//}
}
