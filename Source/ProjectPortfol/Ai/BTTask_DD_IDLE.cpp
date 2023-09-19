// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DD_IDLE.h"
#include "BossCharacter.h"

EBTNodeResult::Type UBTTask_DD_IDLE::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	GetNpcCharacter(ownerComp)->SetAniState(BossAniState::Idle);

	GetBlackboardComponent(ownerComp)->SetValueAsObject(TEXT("TargetActor"), nullptr);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_DD_IDLE::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{

	Super::TickTask(ownerComp, nodeMemory, delataSeconds);

	AActor* ResultActor = GetTargetSearch(ownerComp);

	if (nullptr != ResultActor)
	{
		if (static_cast<int>(BossPhase::None) == GetBlackboardComponent(ownerComp)->GetValueAsEnum(TEXT("Phase")))
		{
			ABossCharacter* bossChar = Cast<ABossCharacter>(GetNpcCharacter(ownerComp));

			if (bossChar == nullptr || bossChar->IsValidLowLevel() == false)
			{
				UE_LOG(LogTemp, Error, TEXT("%S(%u) bossChar == nullptr"), __FUNCTION__, __LINE__);
				return;
			}

			GetBlackboardComponent(ownerComp)->SetValueAsEnum(TEXT("Phase"), static_cast<int>(BossPhase::FIRST));
			
			GetBlackboardComponent(ownerComp)->SetValueAsObject(TEXT("TargetActor"), ResultActor);
		//GetBlackboardComponent(ownerComp)->GetValueAsEnum(TEXT("Phase"));
			SetStateChange(ownerComp, BossDragonAIControlState::PhaseChange);
			//bossChar->SetPhase()
		}
		return;
	}
	return;
}
