// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcAnimInstance.h"
#include "NpcCharacter.h"

//template<typename EnumType>
//bool UNpcAnimInstance::SetAllAnimations(TMap<EnumType, class UAnimMontage*> allAnim)
//{
//
//}

void UNpcAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	//OnMontageBlendingOut.AddDynamic(this, &UZedAnimInstance::MontageEnd);

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