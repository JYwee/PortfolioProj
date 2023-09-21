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
	
	
}

void AMonsterNpc::BeginPlay()
{
	UZedGameInstance* inst = Cast<UZedGameInstance>(GetWorld()->GetGameInstance());

	if (inst == nullptr || inst->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  inst->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}

	UUIHpBar* HealthBarWidget = Cast<UUIHpBar>(mHP_WidgetComp->GetWidget());

	if (HealthBarWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) HealthBarWidget == nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	else {
	HealthBarWidget->mHpProgressBar->PercentDelegate.BindUFunction(this, "GetHpPercent");
	HealthBarWidget->mHpProgressBar->SynchronizeProperties();
	////HealthBarWidget

	}


	//if (HealthBarWidget != nullptr)
	//{
	//	
	//}

	

	if (nullptr != inst)
	{
		mMonsterDT = inst->GetMonsterDataTable(TEXT("meeleEnemy"));

		//SetAllAnimation<NPCAniState>(mMonsterDT->MapAnimation);
		SetAllAnimation(mMonsterDT->MapAnimation);
		SetAniState(NPCEnemyAIControlState::Idle);
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
