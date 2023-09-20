// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DD_MeleeAttack.h"
#include "BTTask_DesertDragonBase.h"


UBTTask_DD_MeleeAttack::UBTTask_DD_MeleeAttack()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_DD_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	GetNpcCharacter(ownerComp)->SetAniState(UBTTask_DesertDragonBase::GetAiState(ownerComp));

	return EBTNodeResult::Type();
}

void UBTTask_DD_MeleeAttack::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, delataSeconds);


	UAnimMontage* Montage = GetNpcCharacter(ownerComp)->GetAnimMontage(UBTTask_DesertDragonBase::GetAiState(ownerComp));
	float Time = Montage->CalculateSequenceLength();

	if (Time <= GetStateTime(ownerComp))
	{
		SetStateChange(ownerComp, BossDragonAIControlState::MoveWork);
	}
	//if()
}
