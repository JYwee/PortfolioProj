// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "MyAIController.h"
#include "NpcCharacter.h"
#include <ZedEnums.h>
#include <NavigationSystem.h>
#include <NavigationPath.h>
#include "BTTask_NpcAiBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UBTTask_NpcAiBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

public:

	UBTTask_NpcAiBase();

	void OnGameplayTaskActivated(class UGameplayTask& activated) override;

	void TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds) override;

	

	float GetStateTime(UBehaviorTreeComponent& ownerComp);

	NPCEnemyAIControlState GetAiState(UBehaviorTreeComponent& ownerComp);
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

	TArray<FVector> PathFind(UBehaviorTreeComponent& ownerComp, AActor* actor);
		
	TArray<FVector> PathFind(UBehaviorTreeComponent& ownerComp, FVector targetPos);

	UNavigationPath* PathFindNavPath(UBehaviorTreeComponent& ownerComp, AActor* actor);

	UNavigationPath* PathFindNavPath(UBehaviorTreeComponent& ownerComp, FVector targetPos);

protected:

	FName mAIControlStateName;
};
