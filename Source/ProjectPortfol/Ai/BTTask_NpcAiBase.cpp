// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NpcAiBase.h"
#include "Kismet/GameplayStatics.h"

void UBTTask_NpcAiBase::OnGameplayTaskActivated(class UGameplayTask&)
{
	//Super::OnGameplayTaskActivated(UGameplayTask);
}

void UBTTask_NpcAiBase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);
}