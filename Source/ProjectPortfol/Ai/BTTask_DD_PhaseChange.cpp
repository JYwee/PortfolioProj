// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask_DD_PhaseChange.h"
#include "BossCharacter.h"
#include "NpcAnimInstance.h"

EBTNodeResult::Type UBTTask_DD_PhaseChange::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	//GetNpcCharacter(ownerComp)->SetAniState(NPCAniState::Idle);
	Super::ExecuteTask(ownerComp, nodeMemory);

	GetNpcCharacter(ownerComp)->SetAniState(BossDragonAIControlState::PhaseChange);

	if (GetNpcCharacter(ownerComp)->GetHpPercent() > 0.5f)
	{
		GetBossCharacter(ownerComp)->SetPhase(BossPhase::FIRST);
	}
	else {
		GetBossCharacter(ownerComp)->SetPhase(BossPhase::SECOND);
	}
	//BossPhase myPhase = GetBossCharacter(ownerComp)->GetPhase();
	//GetBlackboardComponent(ownerComp)->SetValueAsEnum(TEXT("Phase"), static_cast<uint8>(myPhase));

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_DD_PhaseChange::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float delataSeconds)
{
    Super::TickTask(ownerComp, nodeMemory, delataSeconds);

	/*if (GetNpcCharacter(ownerComp)->GetNpcAnimInstance() != nullptr) {
		GetNpcCharacter(ownerComp)->GetAniState()
	}*/

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

		else if (GetNpcCharacter(ownerComp)->GetAniState() == static_cast<int>(BossDragonAIControlState::TakeOff))
		{
			SetStateChange(ownerComp, BossDragonAIControlState::TakeOff);
			
			return;
		}
		
	}

}
