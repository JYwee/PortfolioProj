// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DD_Fly.h"
#include "BossAnimInstance.h"

EBTNodeResult::Type UBTTask_DD_Fly::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	//GetNpcCharacter(ownerComp)->SetAniState(BossDragonAIControlState::TakeOff);

	

	return EBTNodeResult::Type();
}

void UBTTask_DD_Fly::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, delataSeconds);

	UObject* targetObject = GetBlackboardComponent(ownerComp)->GetValueAsObject(TEXT("TargetActor"));
	AActor* targetActor = Cast<AActor>(targetObject);

	if (nullptr == targetActor)
	{
		SetStateChange(ownerComp, BossDragonAIControlState::Idle);
		return;
	}

	if (GetNpcCharacter(ownerComp)->GetNpcAnimInstance() != nullptr) {
		if (GetNpcCharacter(ownerComp)->GetNpcAnimInstance()->Montage_IsPlaying(GetNpcCharacter(ownerComp)->GetCurrentMontage())
			&& GetNpcCharacter(ownerComp)->GetAniState() == static_cast<int>(BossDragonAIControlState::PhaseChange))
		{
			FVector targetPos = targetActor->GetActorLocation();
			FVector thisPos = GetNpcCharacter(ownerComp)->GetActorLocation();

			targetPos.Z = 0.0f;
			//thisPos.Z = 0.0f;

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

		else if (GetNpcCharacter(ownerComp)->GetAniState() == static_cast<int>(BossDragonAIControlState::Idle))
		{
			SetStateChange(ownerComp, BossDragonAIControlState::Idle);

			return;
		}

	}

}
