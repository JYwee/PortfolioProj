// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DD_Fly.h"

EBTNodeResult::Type UBTTask_DD_Fly::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	GetNpcCharacter(ownerComp)->SetAniState(BossAniState::TakeOff);

	

	return EBTNodeResult::Type();
}

void UBTTask_DD_Fly::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, delataSeconds);
}
