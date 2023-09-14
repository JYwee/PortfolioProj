// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DesertDragonBase.h"

UBTTask_DesertDragonBase::UBTTask_DesertDragonBase()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_DesertDragonBase::OnGameplayTaskActivated(UGameplayTask& activated)
{
}

void UBTTask_DesertDragonBase::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, delataSeconds);
}

float UBTTask_DesertDragonBase::GetStateTime(UBehaviorTreeComponent& ownerComp)
{
	return 0.0f;
}

BossDragonAIControlState UBTTask_DesertDragonBase::GetAiState(UBehaviorTreeComponent& ownerComp)
{
	return BossDragonAIControlState();
}

void UBTTask_DesertDragonBase::ResetStateTime(UBehaviorTreeComponent& ownerComp)
{
}

void UBTTask_DesertDragonBase::SetStateChange(UBehaviorTreeComponent& ownerComp, uint8 state)
{
}

ANpcCharacter* UBTTask_DesertDragonBase::GetNpcCharacter(UBehaviorTreeComponent& ownerComp)
{
	return nullptr;
}

AActor* UBTTask_DesertDragonBase::GetTargetSearch(UBehaviorTreeComponent& ownerComp)
{
	return nullptr;
}

UBlackboardComponent* UBTTask_DesertDragonBase::GetBlackboardComponent(UBehaviorTreeComponent& ownerComp)
{
	return nullptr;
}

EBTNodeResult::Type UBTTask_DesertDragonBase::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	return EBTNodeResult::Type();
}

bool UBTTask_DesertDragonBase::IsDeath(UBehaviorTreeComponent& ownerComp)
{
	return false;
}
