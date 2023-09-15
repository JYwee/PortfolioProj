// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DD_PhaseChange.h"
#include "BossCharacter.h"

EBTNodeResult::Type UBTTask_DD_PhaseChange::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	//GetNpcCharacter(ownerComp)->SetAniState(NPCAniState::Idle);
	GetNpcCharacter(ownerComp)->SetAniState(BossAniState::PhaseChange);
	BossPhase myPhase = GetBossCharacter(ownerComp)->GetPhase();
	GetBlackboardComponent(ownerComp)->SetValueAsEnum(TEXT("Phase"), static_cast<uint8>(myPhase));

	return EBTNodeResult0::Type::InProgress;
}

void UBTTask_DD_PhaseChange::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
    Super::TickTask(ownerComp, nodeMemory, delataSeconds);
}
