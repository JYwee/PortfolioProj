// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask_NpcAiBase.h"
#include "BTTask_NpcMove.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UBTTask_NpcMove : public UBTTask_NpcAiBase
{
	GENERATED_BODY()

		UBTTask_NpcMove();

protected:
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory);

	void TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds);

};
