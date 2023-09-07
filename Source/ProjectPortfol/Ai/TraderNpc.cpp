// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/TraderNpc.h"
#include <Interactive/DropItem.h>

ATraderNpc::ATraderNpc()
{
	PrimaryActorTick.bCanEverTick = true;

	//GetCapsuleComponent()->ComponentTags.Add("InteracNPC");
	//Tags.Add("InteracNPC");
}

void ATraderNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATraderNpc::BeginPlay()
{
	Super::BeginPlay();
}
