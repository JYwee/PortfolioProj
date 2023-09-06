// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NpcAiBase.h"
#include "Kismet/GameplayStatics.h"


UBTTask_NpcAiBase::UBTTask_NpcAiBase()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_NpcAiBase::OnGameplayTaskActivated(class UGameplayTask&)
{
	
	//Super::OnGameplayTaskActivated(UGameplayTask);
}

void UBTTask_NpcAiBase::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, delataSeconds);

	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == blackBoard)"), __FUNCTION__, __LINE__);
		return;
	}

	float StateTime = blackBoard->GetValueAsFloat(TEXT("StateTime"));
	StateTime += delataSeconds;
	blackBoard->SetValueAsFloat(TEXT("StateTime"), StateTime);
}

bool UBTTask_NpcAiBase::IsDeath(UBehaviorTreeComponent& ownerComp)
{
	return false;
}

float UBTTask_NpcAiBase::GetStateTime(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == blackBoard)"), __FUNCTION__, __LINE__);
		return 0.0f;
	}

	float StateTime = blackBoard->GetValueAsFloat(TEXT("StateTime"));

	return StateTime;
}

NPCEnemyAIControlState UBTTask_NpcAiBase::GetAiState(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == blackBoard)"), __FUNCTION__, __LINE__);
		return NPCEnemyAIControlState::None;
	}

	uint8 Enum = blackBoard->GetValueAsEnum(mAIControlStateName);


	return static_cast<NPCEnemyAIControlState>(Enum);
}
//
//NPCEnemyAIControlState UBTTask_NpcAiBase::GetAiState(UBehaviorTreeComponent& ownerComp)
//{
//	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();
//
//	if (nullptr == blackBoard)
//	{
//		UE_LOG(LogTemp, Error, TEXT("if (nullptr == blackBoard)"), __FUNCTION__, __LINE__);
//		return NPCEnemyAIControlState::None;
//	}
//
//	uint8 Enum = blackBoard->GetValueAsEnum(mAIControlStateName);
//
//	return static_cast<NPCEnemyAIControlState>(Enum);
//}

void UBTTask_NpcAiBase::ResetStateTime(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == blackBoard)"), __FUNCTION__, __LINE__);
		return;
	}

	blackBoard->SetValueAsFloat(TEXT("StateTime"), 0.0f);
}

void UBTTask_NpcAiBase::SetStateChange(UBehaviorTreeComponent& ownerComp, uint8 state)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == blackBoard)"), __FUNCTION__, __LINE__);
		return;
	}


	if (GetNpcCharacter(ownerComp)->ActorHasTag("Monster") == true)
	{
		mAIControlStateName = TEXT("NPCEnemyAIControlState");
	}
	else if (GetNpcCharacter(ownerComp)->ActorHasTag("InteracNPC") == true)
	{
		mAIControlStateName = TEXT("NPCEnemyAIControlState");
	}
	blackBoard->SetValueAsEnum(mAIControlStateName, state);
	uint8 Enum = blackBoard->GetValueAsEnum(mAIControlStateName);
	//blackBoard->SetValueAsEnum(TEXT("NPCEnemyAIControlState"), state);
	//uint8 Enum2 = blackBoard->GetValueAsEnum(TEXT("NPCEnemyAIControlState"));
	ResetStateTime(ownerComp);

	FinishLatentTask(ownerComp, EBTNodeResult::Type::Failed);
}

ANpcCharacter* UBTTask_NpcAiBase::GetNpcCharacter(UBehaviorTreeComponent& ownerComp)
{
	AMyAIController* AIController = ownerComp.GetOwner<AMyAIController>();
	if (nullptr == AIController || false == AIController->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> AIController->IsValidLowLevel() "), __FUNCTION__, __LINE__);
		return nullptr;
	}

	ANpcCharacter* Character = AIController->GetPawn<ANpcCharacter>();

	if (nullptr == Character || false == Character->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> ANpcCharacter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return Character;
}

AActor* UBTTask_NpcAiBase::GetTargetSearch(UBehaviorTreeComponent& ownerComp)
{
	FString TargetTag = GetBlackboardComponent(ownerComp)->GetValueAsString(TEXT("TargetTag"));
	
	TArray<AActor*> TargetActors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *TargetTag, TargetActors);

	ANpcCharacter* Pawn = GetNpcCharacter(ownerComp);

	float SearchRange = GetBlackboardComponent(ownerComp)->GetValueAsFloat(TEXT("SearchRange"));


	AActor* ResultActor = nullptr;

	if (0 != TargetActors.Num())
	{
		float Range = TNumericLimits<float>::Max();

		for (size_t i = 0; i < TargetActors.Num(); i++)
		{
			float Dis = (Pawn->GetActorLocation() - TargetActors[i]->GetActorLocation()).Size();

			if (SearchRange <= Dis)
			{
				continue;
			}

			if (Range > Dis)
			{
				Range = Dis;
				ResultActor = TargetActors[i];
			}
		}
	}

	return ResultActor;
	
}

UBlackboardComponent* UBTTask_NpcAiBase::GetBlackboardComponent(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if blackBoard nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return blackBoard;
}

EBTNodeResult::Type UBTTask_NpcAiBase::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	if (GetNpcCharacter(ownerComp)->ActorHasTag("Monster") == true)
	{
		mAIControlStateName = TEXT("NPCEnemyAIControlState");
		int a = 0;
	}
	else if (GetNpcCharacter(ownerComp)->ActorHasTag("InteracNPC") == true)
	{
		mAIControlStateName = TEXT("NPCEnemyAIControlState");
		int a = 0;
	}
	UE_LOG(LogTemp, Warning, TEXT("called"));

	return EBTNodeResult::Type();

	
}
