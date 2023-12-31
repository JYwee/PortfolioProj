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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* mHP_WidgetComp;

//	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite)
//		NPCAniState AniState = NPCAniState::Idle;

	UFUNCTION(BlueprintCallable, Category = Npc)
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() {
		return mBehaviorTree;
	}

	UFUNCTION(BlueprintCallable, Category = Npc)
	class UBlackboardComponent* GetBlackboardComponent();

	
	virtual void TakeDamageNpcBase(uint8 damageValue);

	UFUNCTION(BlueprintCallable, Category = Npc)
		FORCEINLINE void PushComponent(UActorComponent* component) {
		mCompArr.Add(component);
	}



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

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite)
		TArray<UActorComponent*> mCompArr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Destroyed() override;

	virtual void PostInitializeComponents() override;

	//UFUNCTION(BlueprintCallable, Category = "NpcCharacter")
	template<typename EnumType>
	FORCEINLINE class UAnimMontage* GetAnimMontage(EnumType index) const{
		return GetAnimMontage(static_cast<int>(index));
	}

	class UAnimMontage* GetAnimMontage(int index) const;
		

	template<typename EnumType>
	void SetAllAnimation(const TMap<EnumType, class UAnimMontage*>& mapAnimation)
	{
		for (TPair<EnumType, UAnimMontage*> Pair : mapAnimation)
		{
			mAllAnimations.Add(static_cast<int>(Pair.Key), Pair.Value);
		}
	}

	FORCEINLINE TMap<int, class UAnimMontage*> GetAllAnimation() const{
		return mAllAnimations;
	}

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		FORCEINLINE void SetIsMeleeAttProcess(bool meleeAttProcess) {
		mIsMeleeAttProcess = meleeAttProcess;
	}
	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		FORCEINLINE bool IsMeleeAttProcessing() const {
		return mIsMeleeAttProcess;
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

	FORCEINLINE class UNpcAnimInstance* GetNpcAnimInstance() {
		return mNpcAnimInstance;
	}
	
	FORCEINLINE void SetNpcAnimInstance(UNpcAnimInstance* animInst) {
		if (animInst == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("%S(%u) animInst == nullptr"), __FUNCTION__, __LINE__);
			return;
		}

		mNpcAnimInstance = animInst;
	}

	FORCEINLINE float GetHpPercent() {
		if (mFullHealthPoint == 0) {
			UE_LOG(LogTemp, Error, TEXT("%S(%u) mFullHealthPoint == 0"), __FUNCTION__, __LINE__);
			return 1.0f;
		}
		return (static_cast<float>(mHealthPoint) / static_cast<float>(mFullHealthPoint));
	}


protected:

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int mAniState = 0;

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<int, class UAnimMontage*> mAllAnimations;

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int mHealthPoint;

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int mFullHealthPoint;


	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mShieldPoint;

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mFullShieldPoint;


	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int mStemina;

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int mFullStemina;


	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int mAttack;

	UPROPERTY(Category = "CharacterBase", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int mDefense;

private:

	UFUNCTION()
		void MontageEnd(UAnimMontage* animMontage, bool inter);


	UFUNCTION(BlueprintCallable, Category = NpcCollision)
		void BeginOverLap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);
	UFUNCTION(BlueprintCallable, Category = AMainCharacter)
		void EndOverLap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);

	bool mIsMeleeAttProcess = false;

	bool mIsOverlapWithPlayerAtt = false;

//	const struct FMonsterDataTable* mMonsterDT = nullptr;

	class UNpcAnimInstance* mNpcAnimInstance = nullptr;
	//UPROPERTY()
};
