// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DD_IDLE.h"

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
		GetBlackboardComponent(ownerComp)->SetValueAsObject(TEXT("TargetActor"), ResultActor);
		SetStateChange(ownerComp, BossDragonAIControlState::PhaseChange);
		return;
	}
	return;
}
