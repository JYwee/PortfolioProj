// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NpcCharacter.h"

AMyAIController::AMyAIController()
{
	mBehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	mBlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));;
}

void AMyAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	if (nullptr != mBehaviorTreeComponent && true == mBehaviorTreeComponent->IsValidLowLevel())
	{
		ANpcCharacter* aiNpcChar = Cast<ANpcCharacter>(inPawn);

		UBehaviorTree* behaviorTree = aiNpcChar->GetBehaviorTree();

		if (nullptr == behaviorTree || false == behaviorTree->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BehaviorTree || false == BehaviorTree->IsValidLowLevel())"), __FUNCTION__, __LINE__);
			return;
		}

		mBlackboardComponent->InitializeBlackboard(*behaviorTree->BlackboardAsset);

		mBlackboardComponent->SetValueAsObject(TEXT("SelfActor"), inPawn);

		mBehaviorTreeComponent->StartTree(*behaviorTree);
	}

}