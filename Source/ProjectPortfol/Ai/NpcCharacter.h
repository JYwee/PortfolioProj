// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../ZedEnums.h"
#include "NpcCharacter.generated.h"

UCLASS()
class PROJECTPORTFOL_API ANpcCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpcCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* mLockOnSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* mLockOnWidgetComp;


//	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite)
//		NPCAniState AniState = NPCAniState::Idle;

	UFUNCTION(BlueprintCallable, Category = Npc)
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() {
		return mBehaviorTree;
	}

	UFUNCTION(BlueprintCallable, Category = Npc)
	class UBlackboardComponent* GetBlackboardComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*template<typename EnumType>
	void PushAnimMontage(EnumType index, UAnimMontage* aniMontage) {
		if (AllAnimations.Contains(static_cast<int>(index)))
		{
			return;
		}
		AllAnimations.Add(static_cast<int>(index), aniMontage);
	}*/


	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite)
		class UBehaviorTree* mBehaviorTree;

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite)
		class UBlackboardComponent* mBlackboardComponent;

	template<typename EnumType>
	void PushAnimation(const EnumType index, class UAnimMontage* animMontage)
	{
		if (mAllAnimations.Contains(index))
		{
			return;
		}
		mAllAnimations.Add(static_cast<int>(index), animMontage);
	}


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Destroyed() override;

	//UFUNCTION(BlueprintCallable, Category = "NpcCharacter")
	template<typename EnumType>
	FORCEINLINE class UAnimMontage* GetAnimMontage(EnumType index) const{
		return GetAnimMontage(static_cast<int>(index));
	}


	template<typename EnumType>
	void SetAllAnimation(const TMap<EnumType, class UAnimMontage*>& mapAnimation)
	{
		for (TPair<EnumType, UAnimMontage*> Pair : mapAnimation)
		{
			mAllAnimations.Add(static_cast<int>(Pair.Key), Pair.Value);
		}
	}


	

	FORCEINLINE class UAnimMontage* GetAnimMontage(int index) {
		if (mAllAnimations.Contains(index))
		{
			return mAllAnimations[index];
		}
		return nullptr;
	}


	template<typename EnumType>
	FORCEINLINE void SetAniState(EnumType aniState) {
		mAniState = static_cast<int>(aniState);
	}

	FORCEINLINE void SetAniState(int aniState) {
		mAniState = aniState;
	}

	template<typename EnumType>
	FORCEINLINE EnumType GetAniState() const{
		return static_cast<EnumType>(mAniState);
	}

	FORCEINLINE int GetAniState() const {
		return mAniState;
	}

	FORCEINLINE class UZedAnimInstance* GetZedAnimInstance() {
		return mZedAnimInstance;
	}
	

private:
	int mHealthPoint;

	float mShieldPoint;

	int mStemina;

	int mAttack;

	int mDefense;


	UFUNCTION(BlueprintCallable, Category = NpcCollision)
		void BeginOverLap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);


	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int mAniState = 0;

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int , class UAnimMontage*> mAllAnimations;


	class UZedAnimInstance* mZedAnimInstance = nullptr;
	//UPROPERTY()
};
