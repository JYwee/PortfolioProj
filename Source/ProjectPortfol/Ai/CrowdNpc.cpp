// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/CrowdNpc.h"
#include <Data/NpcDataTable.h>
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include <ZedGameInstance.h>

ACrowdNpc::ACrowdNpc()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->ComponentTags.Add("InteracNPC");
	Tags.Add("InteracNPC");
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

	FNpcDataTable* npcDT = nullptr;

	if (nullptr != inst)
	{
		npcDT = inst->GetNpcDataTable(mNpcName);

		//SetAllAnimation<NPCAniState>(mMonsterDT->MapAnimation);
		SetAllAnimation(npcDT->MapAnimation);
		SetAniState(NPCEnemyAIControlState::Idle);
	}

	//Super::BeginPlay();

	GetBlackboardComponent()->SetValueAsEnum(TEXT("NpcAiState"), static_cast<uint8>(NPCEnemyAIControlState::Idle));

	mPatrolPostion = inst->GetNpcDataTable(mNpcName)->PositionPatrol;
}


//void ACrowdNpc::BeginOverLap(
//	UPrimitiveComponent* OverlappedComponent,
//	AActor* OtherActor,
//	UPrimitiveComponent* OtherComp,
//	int32 OtherBodyIndex,
//	bool bFromSweep,
//	const FHitResult& SweepResult
//)
//{
//
//	//if (OtherActor->ActorHasTag(TEXT("Weapon")))
//	//{
//	//	this->Destroy();
//	//}
//	//if (OtherComp->ComponentHasTag(TEXT("Weapon")))
//	//{
//	//	this->Destroy();
//	//}
//
//	//SweepResult.Distance;
//	//SweepResult.FaceIndex;
//	//SweepResult.GetActor();
//
//}