// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_NpcAiBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UBTTask_NpcAiBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

public:

	void OnGameplayTaskActivated(class UGameplayTask&) override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds) override;

};
