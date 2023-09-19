// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcAnimInstance.h"
#include "NpcCharacter.h"

//template<typename EnumType>
//bool UNpcAnimInstance::SetAllAnimations(TMap<EnumType, class UAnimMontage*> allAnim)
//{
//
//}

void UNpcAnimInstance::MontageEnd(UAnimMontage* aniMontage, bool inter)
{
	TSubclassOf<UAnimInstance> Inst = ANpcCharacter::StaticClass();

	ANpcCharacter* character = Cast<ANpcCharacter>(GetOwningActor());

	if (character->Tags.Contains(TEXT("Boss")))
	{
		int a = 0;
		if (mAllAnimations[static_cast<int>(BossDragonAIControlState::PhaseChange)] == aniMontage)
		{
			character->SetAniState<BossDragonAIControlState>(BossDragonAIControlState::Idle);
			Montage_Play(mAllAnimations[static_cast<int>(BossAniState::Idle)], 1.0f);
		}
	}

	// Anim 종료된 몽타주

	if (character->Tags.Contains(TEXT("Monster")))
	{
		int a = 0;
		//if (mAllAnimations[static_cast<int>(NPCAniState::Attack)] == aniMontage)
		//{
		//	character->SetAniState<NPCAniState>(NPCAniState::Idle);
		//	//Montage_Play(AllAnimations[ZEDAniState::Idle], 1.0f);
		//}

		//if (mAllAnimations[static_cast<int>(NPCAniState::Jump)] == aniMontage)
		//{
		//	character->SetAniState<NPCAniState>(NPCAniState::Idle);
		//	//Montage_Play(AllAnimations[ZEDAniState::Idle], 1.0f)
		//}
	}

}

void UNpcAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageBlendingOut.AddDynamic(this, &UNpcAnimInstance::MontageEnd);

	ANpcCharacter* character = Cast<ANpcCharacter>(GetOwningActor());

	if (character == nullptr && character->IsValidLowLevel() == false)
	{
		return;
	}

	mAllAnimations = character->GetAllAnimation();
}

void UNpcAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	if (mAllAnimations.Num() == 0)
	{
		return;
	}

	ANpcCharacter* character = Cast<ANpcCharacter>(GetOwningActor());

	if (character == nullptr && character->IsValidLowLevel() == false)
	{
		return;
	}

	mAniState = character->GetAniState();

	// emeny 점프 애니매이션 없어서 임시로 아이들로 때워놓은거 있음.
	class UAnimMontage* montage = mAllAnimations[mAniState];

	if (montage == nullptr)
	{
		return;
	}

	if (false == Montage_IsPlaying(montage))
	{
		Montage_Play(montage, 1.0f);
	}
}

