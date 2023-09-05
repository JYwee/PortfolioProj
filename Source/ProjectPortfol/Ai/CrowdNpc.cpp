// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/CrowdNpc.h"
#include <Data/NpcDataTable.h>
#include "Components/CapsuleComponent.h"
#include <ZedGameInstance.h>

ACrowdNpc::ACrowdNpc()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->ComponentTags.Add("InteracNPC");

}

void ACrowdNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ACrowdNpc::BeginPlay()
{
	Super::BeginPlay();

	UZedGameInstance* inst = Cast<UZedGameInstance>(GetWorld()->GetGameInstance());

	if (inst == nullptr || inst->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  inst->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}

	mPatrolPostion = inst->GetNpcDataTable(mNpcName)->PositionPatrol;
}
