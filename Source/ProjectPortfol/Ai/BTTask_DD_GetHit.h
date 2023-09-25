// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask_DesertDragonBase.h"
#include "BTTask_DD_GetHit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UBTTask_DD_GetHit : public UBTTask_DesertDragonBase
{
	GENERATED_BODY()
	
public:

protected:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory);

	void TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds);

};
