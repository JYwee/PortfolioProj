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

	
	mSplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
	mSplineComp->SetupAttachment(RootComponent);
	//mSplineComp->SetSplinePointType()
	//mSplineComp->SetWorldLocation(GetActorLocation());
	//FVector tmpVec = GetActorLocation();

	//mSplineComp->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::World, true);


}

void ACrowdNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("now %d ") , static_cast<uint8>(GetAniState()))
}


FVector ACrowdNpc::GetNextMovePos() 
{
	mCurSplinePointIndex;
	FVector tmp = mSplineComp->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World);
	GetBlackboardComponent()->SetValueAsVector(TEXT("TargetPosition"), mSplineComp->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World));

	return FVector();
}

void ACrowdNpc::BeginPlay()
{
	UZedGameInstance* inst = Cast<UZedGameInstance>(GetWorld()->GetGameInstance());

	if (inst == nullptr || inst->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  inst->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}

	FNpcDataTable* npcDT = nullptr;

	if (nullptr != inst)
	{
		if (mNpcID.IsNone() == true)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u) mNpcID.IsNone()"), __FUNCTION__, __LINE__);
			return;
		}
		npcDT = inst->GetNpcDataTable(mNpcID);

		//SetAllAnimation<NPCAniState>(mMonsterDT->MapAnimation);
		SetAllAnimation(npcDT->MapAnimation);
		SetAniState(NPCEnemyAIControlState::Idle);
		//if (npcDT->NameNpc != nullptr) {
			mNpcFTextName = npcDT->NameNpc;
		//}

	}

	Super::BeginPlay();


	//Super::BeginPlay();

	GetBlackboardComponent()->SetValueAsEnum(TEXT("NPCEnemyAIControlState"), static_cast<uint8>(NPCEnemyAIControlState::Idle));
	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPostion"), GetActorLocation());
	
	int32 tt = mSplineComp->GetNumberOfSplinePoints();
	if (mSplineComp->GetNumberOfSplinePoints() > 2)
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("TargetPosition"), mSplineComp->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World));
		FVector tmp = mSplineComp->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World);

		int a = 0;
	}
	else
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("TargetPosition"), GetActorLocation());
	}
	
	mPatrolPostion = inst->GetNpcDataTable(mNpcID)->PositionPatrol;
	mInteractDialogues = inst->GetNpcDataTable(mNpcID)->ArrDialog;
}

void ACrowdNpc::TakeDamageNpcBase(uint8 damageValue)
{
	//Super::TakeDamageNpcBase(damageValue);
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