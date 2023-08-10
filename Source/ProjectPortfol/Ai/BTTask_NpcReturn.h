// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask_NpcAiBase.h"
#include "BTTask_NpcReturn.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UBTTask_NpcReturn : public UBTTask_NpcAiBase
{
	GENERATED_BODY()

		UBTTask_NpcReturn();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory);

	void TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds);

};
