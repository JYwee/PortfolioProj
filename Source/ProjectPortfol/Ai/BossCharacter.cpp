// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include <ZedEnums.h>
#include <ZedGameInstance.h>
#include "BehaviorTree/BlackboardComponent.h"


ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetAniState(BossAniState::Idle);

	Tags.Add("Boss");

	//GetMesh()->SetSkeletalMeshAsset();

	//when died set true
	GetMesh()->SetSimulatePhysics(false);
	
	



}

void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABossCharacter::BeginPlay()
{
	


	UZedGameInstance* inst = Cast<UZedGameInstance>(GetWorld()->GetGameInstance());

	if (inst == nullptr || inst->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  inst->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}
	
	
	mCurBossData = inst->GetBossDataTable(mBossName);

	//GetMesh()->SetSkeletalMeshAsset(mCurBossData->Mesh);
		//SetAniState(AIState::DEATH);
	SetAllAnimation(mCurBossData->MapAnimation);
	SetAniState(BossDragonAIControlState::Idle);


	Super::BeginPlay();
	//WeaponArrays.Add(GetGameInstance<UZedGameInstance>()->GetMesh(TEXT("Staff01SM")));
	
	//mBossName = mCurBossData->Subtitle;
	mHealthPoint = mCurBossData->HealthPoint;
	mShieldPoint = mCurBossData->ShieldPoint;
	mStemina = mCurBossData->Stemina;
	mAtt = mCurBossData->Att;
	mDef = mCurBossData->Def;
	mPhase = mCurBossData->Phase;
	mPostionOri = mCurBossData->PostionOri;

	GetBlackboardComponent()->SetValueAsEnum(TEXT("BossDragonAIControlState"), static_cast<uint8>(BossDragonAIControlState::Idle));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 2000.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 250.0f);
	FVector Pos = GetActorLocation();
	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPosition"), Pos);
	/*mBaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;*/

}
