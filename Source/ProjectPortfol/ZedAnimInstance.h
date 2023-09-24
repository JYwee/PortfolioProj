// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZedEnums.h"

#include "Animation/AnimInstance.h"
#include "ZedAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UZedAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(Category = "Anime", EditAnywhere, BlueprintReadWrite)
		ZEDAniState AniState = (ZEDAniState::Idle);


	TMap<ZEDAniState, class UAnimMontage*> AllAnimations;


	UFUNCTION(Category = "Anime", BlueprintCallable)
		void MontageEnd(UAnimMontage* aniMontage, bool inter);

	UFUNCTION(Category = "Anime")
	void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

protected:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float deltaTime) override;

	bool mIsDeath = false;
};
