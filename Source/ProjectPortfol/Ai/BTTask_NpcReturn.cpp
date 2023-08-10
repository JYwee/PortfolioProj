// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_NpcReturn.h"
#include <ZedEnums.h>


UBTTask_NpcReturn::UBTTask_NpcReturn()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_NpcReturn::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	GetNpcCharacter(ownerComp)->SetAniState(NPCEnemyAIControlState::Move);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_NpcReturn::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{

	FVector OriginPos = GetBlackboardComponent(ownerComp)->GetValueAsVector(TEXT("OriginPos"));

	{
		FVector TargetPos = OriginPos;
		FVector ThisPos = GetNpcCharacter(ownerComp)->GetActorLocation();
		TargetPos.Z = 0.0f;
		ThisPos.Z = 0.0f;

		FVector Dir = TargetPos - ThisPos;
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
		FVector TargetPos = OriginPos;
		PawnPos.Z = 0.0f;
		TargetPos.Z = 0.0f;

		FVector Dir = TargetPos - PawnPos;

		GetNpcCharacter(ownerComp)->AddMovementInput(Dir);

		if (10.0f >= Dir.Size())
		{
			SetStateChange(ownerComp, NPCEnemyAIControlState::Idle);
			return;
		}
	}
}
