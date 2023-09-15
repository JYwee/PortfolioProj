// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DesertDragonBase.h"
#include "BossCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTTask_DesertDragonBase::UBTTask_DesertDragonBase()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_DesertDragonBase::OnGameplayTaskActivated(UGameplayTask& activated)
{
}

void UBTTask_DesertDragonBase::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
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

float UBTTask_DesertDragonBase::GetStateTime(UBehaviorTreeComponent& ownerComp)
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

BossDragonAIControlState UBTTask_DesertDragonBase::GetAiState(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == blackBoard)"), __FUNCTION__, __LINE__);
		return BossDragonAIControlState::None;
	}

	uint8 Enum = blackBoard->GetValueAsEnum(mBossAiControlStateName);


	return static_cast<BossDragonAIControlState>(Enum);
}

void UBTTask_DesertDragonBase::ResetStateTime(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == blackBoard)"), __FUNCTION__, __LINE__);
		return;
	}

	blackBoard->SetValueAsFloat(TEXT("StateTime"), 0.0f);
}

void UBTTask_DesertDragonBase::SetStateChange(UBehaviorTreeComponent& ownerComp, uint8 state)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == blackBoard)"), __FUNCTION__, __LINE__);
		return;
	}


	if (GetNpcCharacter(ownerComp)->ActorHasTag("DesertDragon") == true)
	{
		mBossAiControlStateName = TEXT("BossDragonAIControlState");
	}
	blackBoard->SetValueAsEnum(mBossAiControlStateName, state);
	uint8 Enum = blackBoard->GetValueAsEnum(mBossAiControlStateName);
	//blackBoard->SetValueAsEnum(TEXT("NPCEnemyAIControlState"), state);
	//uint8 Enum2 = blackBoard->GetValueAsEnum(TEXT("NPCEnemyAIControlState"));
	ResetStateTime(ownerComp);

	FinishLatentTask(ownerComp, EBTNodeResult::Type::Failed);

}

ANpcCharacter* UBTTask_DesertDragonBase::GetNpcCharacter(UBehaviorTreeComponent& ownerComp)
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

ABossCharacter* UBTTask_DesertDragonBase::GetBossCharacter(UBehaviorTreeComponent& ownerComp)
{
	AMyAIController* AIController = ownerComp.GetOwner<AMyAIController>();
	if (nullptr == AIController || false == AIController->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> AIController->IsValidLowLevel() "), __FUNCTION__, __LINE__);
		return nullptr;
	}

	ABossCharacter* Character = AIController->GetPawn<ABossCharacter>();

	if (nullptr == Character || false == Character->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> ANpcCharacter->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return Character;
}



AActor* UBTTask_DesertDragonBase::GetTargetSearch(UBehaviorTreeComponent& ownerComp)
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

UBlackboardComponent* UBTTask_DesertDragonBase::GetBlackboardComponent(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if blackBoard nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return blackBoard;
}

EBTNodeResult::Type UBTTask_DesertDragonBase::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	if (GetNpcCharacter(ownerComp)->ActorHasTag("DesertDragon") == true)
	{
		mBossAiControlStateName = TEXT("BossDragonAIControlState");
		int a = 0;
	}
	
	return EBTNodeResult::Type();
}

bool UBTTask_DesertDragonBase::IsDeath(UBehaviorTreeComponent& ownerComp)
{
	return false;
}
