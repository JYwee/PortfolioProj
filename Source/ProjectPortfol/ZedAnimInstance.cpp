// Fill out your copyright notice in the Description page of Project Settings.


#include "ZedAnimInstance.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include <UI/InGameHud.h>
#include "Kismet/KismetSystemLibrary.h"

void UZedAnimInstance::MontageEnd(UAnimMontage* aniMontage, bool inter)
{
	//수정해야할것 0729
	TSubclassOf<UAnimInstance> animInstance = UZedAnimInstance::StaticClass();
	
	AMainCharacter* character = Cast<AMainCharacter>(GetOwningActor());

	if (character == nullptr && character->IsValidLowLevel() == false)
	{
		return;
	}

	if (AllAnimations[ZEDAniState::Attack] == aniMontage)
	{
		AniState = ZEDAniState::Idle;
		character->SetAniState(ZEDAniState::Idle);
		Montage_Play(AllAnimations[ZEDAniState::Idle], 1.0f);
	}

	else if (AllAnimations[ZEDAniState::Jump] == aniMontage)
	{
		AniState = ZEDAniState::Idle;
		character->SetAniState(ZEDAniState::Idle);
		Montage_Play(AllAnimations[ZEDAniState::Idle], 1.0f);
	}

	else if (AllAnimations[ZEDAniState::SimpleMagicCasting] == aniMontage)
	{
		AniState = ZEDAniState::Idle;
		character->SetAniState(ZEDAniState::Idle);
		Montage_Play(AllAnimations[ZEDAniState::Idle], 1.0f);
	}

	else if(AllAnimations[ZEDAniState::GetHIT] == aniMontage)
	{
		AniState = ZEDAniState::Idle;
		character->SetAniState(ZEDAniState::Idle);
		Montage_Play(AllAnimations[ZEDAniState::Idle], 1.0f);
	}
	
}

void UZedAnimInstance::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	AMainCharacter* character = Cast<AMainCharacter>(GetOwningActor());
	if (NotifyName == TEXT("RightSpell")) {
		character->SpellRightMagic();
	}
	else if (NotifyName == TEXT("startattack")) {
		character->SetIsMeleeAttProcess(true);
	}
	else if (NotifyName == TEXT("endattack")) {
		character->SetIsMeleeAttProcess(false);
	}
	else if (NotifyName == TEXT("Death")) {
		
		APlayerController* HUDController = Cast<APlayerController>(character->GetController());
		AInGameHud* myHud = HUDController->GetHUD<AInGameHud>();
		myHud->GetMainWidget()->SetGameOverWindowOnOffSwitch();
		HUDController->SetInputMode(FInputModeUIOnly());
		HUDController->SetShowMouseCursor(true);

		AniState = character->GetAniState();
		class UAnimMontage* montage = AllAnimations[AniState];
		//GetOwningActor()->Destroy(true);
		mIsDeath = true;
		Montage_Pause();
		
		//UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}
}

void UZedAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageBlendingOut.AddDynamic(this, &UZedAnimInstance::MontageEnd);
	OnPlayMontageNotifyBegin.AddDynamic(this, &UZedAnimInstance::AnimNotifyBegin);

	AMainCharacter* character = Cast<AMainCharacter>(GetOwningActor());

	if (character == nullptr && character->IsValidLowLevel() == false)
	{
		return;
	}

	for (TPair<int, UAnimMontage*> Pair : character->GetAllAnimations())
	{
		AllAnimations.Add(static_cast<ZEDAniState>(Pair.Key), Pair.Value);
	}
	//AllAnimations = character->GetAllAnimations();
}

void UZedAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	if (AllAnimations.Num() == 0)
	{
		return;
	}
	if (mIsDeath == true) {
		return;
	}
	
	AMainCharacter* character = Cast<AMainCharacter>(GetOwningActor());

	if (character == nullptr && character->IsValidLowLevel() == false)
	{
		return;
	}

	AniState = character->GetAniState();

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
