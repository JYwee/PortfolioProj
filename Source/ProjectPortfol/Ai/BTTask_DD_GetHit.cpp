// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DD_GetHit.h"
#include "BossCharacter.h"
#include "NpcAnimInstance.h"

EBTNodeResult::Type UBTTask_DD_GetHit::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	GetNpcCharacter(ownerComp)->SetAniState(BossDragonAIControlState::GetHit);
	
	return EBTNodeResult::Type::InProgress;
}

void UBTTask_DD_GetHit::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, delataSeconds);

	
}