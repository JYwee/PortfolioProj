// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_NpcMove.h"
#include <ZedEnums.h>
#include "GameFramework/CharacterMovementComponent.h"


UBTTask_NpcMove::UBTTask_NpcMove()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_NpcMove::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	GetNpcCharacter(ownerComp)->SetAniState(NPCEnemyAIControlState::Move);

	UCharacterMovementComponent* moveComp = Cast<UCharacterMovementComponent>(GetNpcCharacter(ownerComp)->GetMovementComponent());

	if (nullptr != moveComp)
	{
		moveComp->MaxWalkSpeed = 300.0f;
	}

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NpcMove::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	UObject* targetObject = GetBlackboardComponent(ownerComp)->GetValueAsObject(TEXT("TargetActor"));
	AActor* targetActor = Cast<AActor>(targetObject);

	if (nullptr == targetActor)
	{
		SetStateChange(ownerComp, NPCEnemyAIControlState::Return);
		return;
	}

	/*if (true == IsDeathCheck(ownerComp))
	{
		SetStateChange(ownerComp, NPCEnemyAIControlState::Death);
		return;
	}*/


	{
		FVector targetPos = targetActor->GetActorLocation();
		FVector thisPos = GetNpcCharacter(ownerComp)->GetActorLocation();
		// 혹시라도 z축이 있을 가능성을 없애는게 보통입니다.
		targetPos.Z = 0.0f;
		thisPos.Z = 0.0f;

		FVector Dir = targetPos - thisPos;
		Dir.Normalize();

		FVector OtherForward = GetNpcCharacter(ownerComp)->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;

		if (FMath::Abs(Angle0 - Angle1) >= 10.0f)
		{
			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 500.0f * delataSeconds });
			GetNpcCharacter(ownerComp)->AddActorWorldRotation(Rot);
		}
		else {
			FRotator Rot = Dir.Rotation();
			GetNpcCharacter(ownerComp)->SetActorRotation(Rot);
		}
	}



	{
		FVector PawnPos = GetNpcCharacter(ownerComp)->GetActorLocation();
		FVector TargetPos = targetActor->GetActorLocation();
		PawnPos.Z = 0.0f;
		TargetPos.Z = 0.0f;

		FVector Dir = TargetPos - PawnPos;

		GetNpcCharacter(ownerComp)->AddMovementInput(Dir);
		//GetGlobalCharacter(OwnerComp)->SetActorRotation(Dir.Rotation());

		FVector OriginPos = GetBlackboardComponent(ownerComp)->GetValueAsVector(TEXT("OriginPosition"));
		float SearchRange = GetBlackboardComponent(ownerComp)->GetValueAsFloat(TEXT("SearchRange"));
		float AttackRange = GetBlackboardComponent(ownerComp)->GetValueAsFloat(TEXT("AttackRange"));

		OriginPos.Z = 0.0f;
		FVector OriginDir = OriginPos - PawnPos;

		if (OriginDir.Size() >= SearchRange * 1.5f)
		{
			GetBlackboardComponent(ownerComp)->SetValueAsObject(TEXT("TargetActor"), nullptr);
			SetStateChange(ownerComp, NPCEnemyAIControlState::Return);
			int a = 0;
			return;
		}

		if (SearchRange < Dir.Size())
		{
			SetStateChange(ownerComp, NPCEnemyAIControlState::Idle);
			return;
		}

		// 충분히 근접했다.
		if (AttackRange >= Dir.Size())
		{
			SetStateChange(ownerComp, NPCEnemyAIControlState::Attack);
			return;
		}
	}

}
