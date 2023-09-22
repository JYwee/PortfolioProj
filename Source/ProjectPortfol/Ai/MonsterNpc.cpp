// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterNpc.h"
#include <ZedGameInstance.h>
#include <Data/MonsterDataTable.h>
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <UI/UIHpBar.h>

AMonsterNpc::AMonsterNpc()
{
	Tags.Add("Monster");
	
	mHP_WidgetComp->SetupAttachment(GetMesh(), TEXT("HEAD_UI_Socket"));

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	WeaponMesh->SetupAttachment(GetMesh(), TEXT("weaponSocket"));
}

void AMonsterNpc::BeginPlay()
{
	UZedGameInstance* inst = Cast<UZedGameInstance>(GetWorld()->GetGameInstance());

	if (inst == nullptr || inst->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  inst->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}

	//UUIHpBar* HealthBarWidget = Cast<UUIHpBar>(mHP_WidgetComp->GetWidget());

	//if (HealthBarWidget == nullptr)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("%S(%u) HealthBarWidget == nullptr"), __FUNCTION__, __LINE__);
	//	//return;
	//}

	//else {
	//HealthBarWidget->mHpProgressBar->PercentDelegate.BindUFunction(this, "GetHpPercent");
	//HealthBarWidget->mHpProgressBar->SynchronizeProperties();
	//////HealthBarWidget

	//}


	//if (HealthBarWidget != nullptr)
	//{
	//	
	//}

	

	if (nullptr != inst)
	{
		mMonsterDT = inst->GetMonsterDataTable(TEXT("meeleEnemy"));

		//SetAllAnimation<NPCAniState>(mMonsterDT->MapAnimation);
		mFullHealthPoint = mMonsterDT->HP;
		mHealthPoint = mFullHealthPoint;
		SetAllAnimation(mMonsterDT->MapAnimation);
		SetAniState(NPCEnemyAIControlState::Idle);

		WeaponMesh->SetStaticMesh(inst->GetMesh(TEXT("SM_Water3")));
	}

	Super::BeginPlay();
	//GetBlackboardComponent().
	GetBlackboardComponent()->SetValueAsEnum(TEXT("NPCEnemyAIControlState"), static_cast<uint8>(NPCEnemyAIControlState::Idle));
	//GetBlackboardComponent()->SetValueAsEnum(mAIControlStateName, static_cast<uint8>(NPCEnemyAIControlState::Idle));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 1500.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 200.0f);
	FVector Pos = GetActorLocation();
	GetBlackboardComponent()->SetValueAsVector(TEXT("OriginPosition"), Pos);
}

void AMonsterNpc::TakeDamageNpcBase(uint8 damageValue)
{
	//Super::TakeDamageNpcBase(damageValue);

	mHealthPoint -= damageValue;

	if (mHealthPoint < 0)
	{
		//죽음 처리
		return;
	}

	SetAniState(NPCEnemyAIControlState::GetHit);

}

void AMonsterNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UUIHpBar* HealthBarWidget = Cast<UUIHpBar>(mHP_WidgetComp->GetWidget());

	/*if (HealthBarWidget->mHpProgressBar != nullptr) {
		HealthBarWidget->mHpProgressBar->SetPercent(GetHpPercent());

		if (HealthBarWidget->mHpProgressBar->Percent < 1.0f)
		{
			HealthBarWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			HealthBarWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}*/
}
