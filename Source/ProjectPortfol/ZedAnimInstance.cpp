// Fill out your copyright notice in the Description page of Project Settings.


#include "ZedAnimInstance.h"
#include "MainCharacter.h"

void UZedAnimInstance::MontageEnd(UAnimMontage* aniMontage, bool inter)
{
	/*TSubclassOf<UAnimInstance> animInstance = UZedAnimInstance::StaticClass();
	
	AMainCharacter* character = Cast<AMainCharacter>(GetOwningActor());

	if (character == nullptr && character->IsValidLowLevel() == false)
	{
		return;
	}

	if (AllAnimations[ZEDAniState::Attack] == aniMontage)
	{
		AniState = ZEDAniState::Idle;
		character->AniState = ZEDAniState::Idle;
		Montage_Play(AllAnimations[ZEDAniState::Idle], 1.0f);
	}

	if (AllAnimations[ZEDAniState::Jump] == aniMontage)
	{
		AniState = ZEDAniState::Idle;
		character->AniState = ZEDAniState::Idle;
		Montage_Play(AllAnimations[ZEDAniState::Idle], 1.0f);
	}*/

}

void UZedAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageBlendingOut.AddDynamic(this, &UZedAnimInstance::MontageEnd);
	
	AMainCharacter* character = Cast<AMainCharacter>(GetOwningActor());

	if (character == nullptr && character->IsValidLowLevel() == false)
	{
		return;
	}

	
	AllAnimations = character->GetAllAnimations();
}

void UZedAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	if (AllAnimations.Num() == 0)
	{
		return;
	}

	AMainCharacter* character = Cast<AMainCharacter>(GetOwningActor());

	if (character == nullptr && character->IsValidLowLevel() == false)
	{
		return;
	}

	AniState = static_cast<int>(character->GetAniState());

	class UAnimMontage* montage = AllAnimations[AniState];

	if (montage == nullptr)
	{
		return;
	}

	if (false == Montage_IsPlaying(montage))
	{
		Montage_Play(montage, 1.0f);
	}
}
