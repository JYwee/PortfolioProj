// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_NpcIDLE.h"
#include <ZedEnums.h>

EBTNodeResult::Type UBTTask_NpcIDLE::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	GetNpcCharacter(ownerComp)->SetAniState(NPCAniState::Idle);

	GetBlackboardComponent(ownerComp)->SetValueAsObject(TEXT("TargetActor"), nullptr);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NpcIDLE::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	/*if (true == IsDeathCheck(ownerComp))
	{
		SetStateChange(ownerComp, NPCEnemyAIControlState::Death);
		return;
	}*/

	Super::TickTask(ownerComp, nodeMemory, delataSeconds);

	/*if (2.0f <= GetStateTime(ownerComp))
	{
		FRandomStream Stream;
		Stream.GenerateNewSeed();

		int Value = Stream.RandRange(0, 1);


		ResetStateTime(ownerComp);

		SetStateChange(ownerComp, NPCEnemyAIControlState::Patrol);
		return;
	}*/

	AActor* ResultActor = GetTargetSearch(ownerComp);

	if (nullptr != ResultActor)
	{
		GetBlackboardComponent(ownerComp)->SetValueAsObject(TEXT("TargetActor"), ResultActor);
		SetStateChange(ownerComp, NPCEnemyAIControlState::Move);
		return;
	}
	return;
}
