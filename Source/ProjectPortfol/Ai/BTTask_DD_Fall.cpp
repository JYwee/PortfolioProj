// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DD_Fall.h"

EBTNodeResult::Type UBTTask_DD_Fall::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	GetNpcCharacter(ownerComp)->SetAniState(BossDragonAIControlState::Falling);

	return EBTNodeResult::Type();
}

void UBTTask_DD_Fall::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, delataSeconds);
}
