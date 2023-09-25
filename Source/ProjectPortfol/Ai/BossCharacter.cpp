// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include <ZedEnums.h>
#include <ZedGameInstance.h>

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include <UI/UIHpBar.h>
#include <UI/MiniMapComponent.h>
#include "NpcAnimInstance.h"


ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetAniState(BossDragonAIControlState::Idle);

	Tags.Add("Boss");

	//GetMesh()->SetSkeletalMeshAsset();

	//when died set true
	GetMesh()->SetSimulatePhysics(false);
	
	
	mHP_WidgetComp->SetupAttachment(GetMesh(),TEXT("HEAD_UI_Socket"));
	//mLockOnWidgetComp->SetupAttachment(GetMesh(), TEXT("HEAD_UI_Socket"));

	mMiniMapComp = CreateDefaultSubobject<UMiniMapComponent>(TEXT("MiniMapComp"));
	mMiniMapComp->SetupAttachment(RootComponent);
	mMiniMapComp->Init(this);
	//mHP_WidgetComp->SetVisibility(true);


}

void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UUIHpBar* HealthBarWidget = Cast<UUIHpBar>(mHP_WidgetComp->GetWidget());

	if (HealthBarWidget->mHpProgressBar != nullptr) {
		HealthBarWidget->mHpProgressBar->SetPercent(GetHpPercent());

		if (HealthBarWidget->mHpProgressBar->Percent < 1.0f)
		{
			mHP_WidgetComp->SetVisibility(true);
			//HealthBarWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			mHP_WidgetComp->SetVisibility(false);
		}
	}
	
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
	mFullHealthPoint = mCurBossData->HealthPoint;
	mHealthPoint = mFullHealthPoint;
	mShieldPoint = mCurBossData->ShieldPoint;
	mStemina = mCurBossData->Stemina;
	mAttack = mCurBossData->Att;
	mDefense = mCurBossData->Def;
	mPhase = BossPhase::None;
	mFinalPhase = mCurBossData->FinalPhase;
	mPostionOri = mCurBossData->PostionOri;
	
	

	//UUIHpBar* HealthBarWidget = Cast<UUIHpBar>(mHP_WidgetComp->GetWidget());

	//if (HealthBarWidget->mHpProgressBar == nullptr)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("%S(%u) HealthBarWidget == nullptr"), __FUNCTION__, __LINE__);
	//	//return;
	//}

	//else {
	//	HealthBarWidget->mHpProgressBar->PercentDelegate.BindUFunction(this, "GetHpPercent");
	//	HealthBarWidget->mHpProgressBar->SynchronizeProperties();
	//	////HealthBarWidget

	//}


	GetBlackboardComponent()->SetValueAsEnum(TEXT("BossDragonAIControlState"), static_cast<uint8>(BossDragonAIControlState::Idle));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 2000.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 250.0f);
	GetBlackboardComponent()->SetValueAsEnum(TEXT("Phase"), static_cast<uint8>(mPhase));
	GetBlackboardComponent()->SetValueAsEnum(TEXT("FinalPhase"), static_cast<uint8>(mFinalPhase));
	FVector Pos = GetActorLocation();
	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPosition"), Pos);
	/*mBaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;*/

	//SetNpcAnimInstance(Cast<UNpcAnimInstance>(GetMesh()->GetAnimInstance()));
	GetNpcAnimInstance()->SetAllAnimation(mCurBossData->MapAnimation);

	UUIHpBar* HealthBarWidget = Cast<UUIHpBar>(mHP_WidgetComp->GetWidget());
	HealthBarWidget->mHpProgressBar = Cast<UProgressBar>(HealthBarWidget->GetWidgetFromName(TEXT("ProgBarHP")));;
	HealthBarWidget->mBackGroundProgress = Cast<UImage>(HealthBarWidget->GetWidgetFromName(TEXT("BackgroundHPBar")));

}

void ABossCharacter::TakeDamageNpcBase(uint8 damageValue)
{
	//Super::TakeDamageNpcBase(damageValue);

	mHealthPoint -= damageValue;

	if (mHealthPoint < 0)
	{
		//죽음 처리
		return;
	}

	SetAniState(BossDragonAIControlState::GetHit);
}

//float ABossCharacter::GetHpPercent()
//{
//	{
//		if (mFullHealthPoint == 0) {
//			UE_LOG(LogTemp, Error, TEXT("%S(%u) mFullHealthPoint == 0"), __FUNCTION__, __LINE__);
//			return 1.0f;
//		}
//		return (static_cast<float>(mHealthPoint) / static_cast<float>(mFullHealthPoint));
//	}
//}
