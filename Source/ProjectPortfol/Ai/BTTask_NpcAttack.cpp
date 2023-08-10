// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_NpcAttack.h"

UBTTask_NpcAttack::UBTTask_NpcAttack()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_NpcAttack::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	GetNpcCharacter(ownerComp)->SetAniState(UBTTask_NpcAiBase::GetAiState(ownerComp));


	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NpcAttack::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, delataSeconds);

	/*if (true == IsDeathCheck(ownerComp))
	{
		SetStateChange(ownerComp, NPCEnemyAIControlState::Death);
		return;
	}*/
	//GetNpcCharacter(ownerComp)->GetAnimMontage<NPCAniState>(NPCAniState::Attack);
	UAnimMontage* Montage = GetNpcCharacter(ownerComp)->GetAnimMontage(UBTTask_NpcAiBase::GetAiState(ownerComp));
	float Time = Montage->CalculateSequenceLength();

	if (Time <= GetStateTime(ownerComp))
	{
		SetStateChange(ownerComp, NPCEnemyAIControlState::Move);
	}
}
