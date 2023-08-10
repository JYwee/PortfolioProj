// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_NpcPatrol.h"
#include <ZedEnums.h>


UBTTask_NpcPatrol::UBTTask_NpcPatrol()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_NpcPatrol::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NpcPatrol::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, delataSeconds);
	
}
