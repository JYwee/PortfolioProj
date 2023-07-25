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


	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite)
		NPCAniState AniState = NPCAniState::Idle;

	UFUNCTION(BlueprintCallable, Category = Npc)
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() {
		return mBehaviorTree;
	}

	UFUNCTION(BlueprintCallable, Category = Npc)
	class UBlackboardComponent* GetBlackboardComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	template<typename EnumType>
	void PushAnimMontage(EnumType index, UAnimMontage* aniMontage) {
		if (AllAnimations.Contains(static_cast<int>(index)))
		{
			return;
		}
		AllAnimations.Add(static_cast<int>(index), aniMontage);
	}


	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite)
		class UBehaviorTree* mBehaviorTree;

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite)
		class UBlackboardComponent* mBlackboardComponent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Destroyed() override;

	//UFUNCTION(BlueprintCallable, Category = "NpcCharacter")
	template<typename EnumType>
	class UAnimMontage* GetAnimMontage(EnumType index) {
		return GetAnimMontage(static_cast<int>(index));
	}

	class UAnimMontage* GetAnimMontage(int index) {
		if (AllAnimations.Contains(index))
		{
			return AllAnimations[index];
		}
		return nullptr;
	}

	template<typename EnumType>
	void SetAniState(EnumType aniState) {
		mAniState = static_cast<int>(aniState);
	}

	class UZedAnimInstance* GetZedAnimInstance() {
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
	TMap<int , class UAnimMontage*> AllAnimations;


	class UZedAnimInstance* mZedAnimInstance = nullptr;
	//UPROPERTY()
};
