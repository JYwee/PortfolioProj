// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NpcAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UNpcAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(Category = "Anime", BlueprintCallable)
		void MontageEnd(UAnimMontage* aniMontage, bool inter);

	
	template<typename EnumType>
	UFUNCTION(Category = "Anime", BlueprintCallable)
	void SetAniState(EnumType state) {
		mAniState = static_cast<int> state;
	}

	template<typename EnumType>
	UFUNCTION(Category = "Anime", BlueprintCallable)
	EnumType GetAniState() {
		return static_cast<int>(mAniState);
	}

	template<typename EnumType>
	void SetAllAnimation(const TMap<EnumType, class UAnimMontage*>& mapAnimation)
	{
		for (TPair<EnumType, UAnimMontage*> Pair : mapAnimation)
		{
			mAllAnimations.Add(static_cast<int>(Pair.Key), Pair.Value);
		}
	}

	UFUNCTION(Category = "Anime")
		void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	UFUNCTION(Category = "Anime")
	bool IsPlaying(int index) {
		if (Montage_IsPlaying(mAllAnimations[index]) == false) {
			return false;
		}
		else {
			return true;
		}	
	}

protected:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float deltaTime) override;


private:
	UPROPERTY(Category = "Anime", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int mAniState;

	UPROPERTY(Category = "Anime", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, class UAnimMontage*> mAllAnimations;

};
