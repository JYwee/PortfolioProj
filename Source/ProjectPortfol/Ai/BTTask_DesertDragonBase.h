// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask_NpcAiBase.h"
#include <ZedEnums.h>
#include "BTTask_DesertDragonBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UBTTask_DesertDragonBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_DesertDragonBase();

	void OnGameplayTaskActivated(class UGameplayTask& activated) override;

	void TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds) override;

	float GetStateTime(UBehaviorTreeComponent& ownerComp);

	BossDragonAIControlState GetAiState(UBehaviorTreeComponent& ownerComp);
	//NpcAiState

	void ResetStateTime(UBehaviorTreeComponent& ownerComp);

	template<typename EnumType>
	void SetStateChange(UBehaviorTreeComponent& ownerComp, EnumType state)
	{
		SetStateChange(ownerComp, static_cast<uint8>(state));
	}

	void SetStateChange(UBehaviorTreeComponent& ownerComp, uint8 state);

	class ANpcCharacter* GetNpcCharacter(UBehaviorTreeComponent& ownerComp);

	class AActor* GetTargetSearch(UBehaviorTreeComponent& ownerComp);

	class UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& ownerComp);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory);

	bool IsDeath(UBehaviorTreeComponent& ownerComp);

protected:

	FName mAIControlStateName;
	
};
