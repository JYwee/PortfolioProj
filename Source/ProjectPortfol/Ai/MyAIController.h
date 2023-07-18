// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController();

	void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIController, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* mBehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIController, meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* mBlackboardComponent;

};
