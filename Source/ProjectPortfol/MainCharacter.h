// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZedEnums.h"
#include "Components/SphereComponent.h"
#include "UI/InventoryItemData.h"
#include "MainCharacter.generated.h"

UCLASS()
class PROJECTPORTFOL_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()


	
public:
	// Sets default values for this character's properties
	AMainCharacter();
	~AMainCharacter();

	UFUNCTION(BlueprintCallable, Category = AMainCharacter)
		void BeginOverLap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);
	
	
	UFUNCTION(BlueprintCallable, Category = AMainCharacter)
		void BeginOverLapWithCap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);


	UFUNCTION(BlueprintCallable, Category = AMainCharacter)
		void EndOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);

	UFUNCTION(BlueprintCallable, Category = AMainCharacter)
		void EndOverlapWithCap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);
	

//	(FComponentEndOverlapSignature, UPrimitiveComponent, OnComponentEndOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USphereComponent> mSphereComponent;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* mSpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* mMiniMapSpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* mUSceneCaptureComponent2D;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* mFollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* mParticleSystemComp;


	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	FORCEINLINE	ZEDAniState GetAniState() const{
		return mAniState;
	}
	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	FORCEINLINE	void SetAniState(ZEDAniState aniState) {
		mAniState = aniState;
	}
	
	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	FORCEINLINE	TMap<int, class UAnimMontage*> GetAllAnimations() const{
		TMap<int, class UAnimMontage*> tmpAllAnim;
		for (TPair<ZEDAniState, UAnimMontage*> Pair : mAllAnimations)
		{
			tmpAllAnim.Add(static_cast<int>(Pair.Key), Pair.Value);
		}
		return tmpAllAnim;
	}
	
	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	void AimingAction() ;
	
	void SetAllAnimation(const TMap<int, class UAnimMontage*>& mapAnimation)
	{
		for (TPair<int, UAnimMontage*> Pair : mapAnimation)
		{
			mAllAnimations.Add(static_cast<ZEDAniState>(Pair.Key), Pair.Value);
		}
	}

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	void InteractAction();

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		void TakeDamage(uint8 damage);
	/*UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	FORCEINLINE	void SetAllAnimations(ZEDAniState aniState) {
		mA
	}*/
	//void AttackAction();
	//void JumpAction();
	////void JumpAxis(float Rate);

	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	//	virtual void MoveForward(float Val);

	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	//	virtual void MoveRight(float Val);

	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	//	virtual void MoveUp_World(float Val);

	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	//	virtual void TurnAtRate(float Rate);

	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	//	virtual void LookUpAtRate(float Rate);

	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	//	void FocusTurn(float Rate);

	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	//	void LockOnTarget();


	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	//	void AMainCharacter::Look(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AMainCharacter")
		float BaseTurnRate;

	/** Base lookup rate, in deg/sec. Other scaling may affect final lookup rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AMainCharacter")
		float BaseLookUpRate;


	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		FRotator GetFollowCameraRotator() const;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* WeaponMesh;

	// 블루프린트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UStaticMesh*> WeaponArrays;

	FORCEINLINE bool IsLockOnTarget(){
		return mIsLockOn;
	}

	FORCEINLINE void SetIsLockOn(bool isLockOn) {
		mIsLockOn = isLockOn;
	}

	FORCEINLINE class ANpcCharacter* GetTargetNpcChar() {
		return mTargetNpcCharacter;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMyPlayerController* myController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ANpcCharacter* mTargetNpcCharacter;

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		void SpellRightMagic();
//mNearInteractObj
	
	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	FORCEINLINE TArray<AActor*> GetNearInteractObj() {
		return mNearInteractObj;
	}

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	FORCEINLINE void SetIsAimingNow(bool bIsAnimed) {
		mIsAimingNow = bIsAnimed;
	}
	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	FORCEINLINE bool IsAimingNow() {
		return mIsAimingNow;
	}

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		FORCEINLINE bool IsMeleeAttProcessing() const{
		return mIsMeleeAttProcess;
	}

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		FORCEINLINE void SetIsMeleeAttProcess(bool meleeAttProcess) {
		mIsMeleeAttProcess = meleeAttProcess;
	}
	bool IsChangeAimingState(bool curAimState)
	{
		//if()
		return mIsChangeAimingState;
	}

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	TArray<UInventoryItemData*> GetInventoryData()
	{
		return mInventoryData;
	}

	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	bool AddInventoryItem(const struct FItemDataTable* itemData, uint8 count);
	
	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	int FindIndexItemInInv(const struct FItemDataTable* itemData , int index);

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	class USoundBase* GetSound(SoundName index)
	{
		if (false == mAllSoundsMap.Contains(index))
		{
			return nullptr;
		}
		return mAllSoundsMap[index];
	}

private:
		int mHealthPoint;
		UPROPERTY(Category = "AMainCharacter", BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		int mMaxHealthPoint = 1000;


		float mStaminaPoint = 1.f;

		int mAttack;

		int mDefense;

		bool mIsLockOn;

		bool mIsAimingNow = false;

		bool mIsChangeAimingState = false;

		bool mIsOverlapWihtEnemyAttack = false;

		bool mIsMeleeAttProcess = false;

		UPROPERTY(Category = "AMainCharacter", BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
			ZEDAniState mAniState;
		//ZEDAniState AniState;
		
		class UZedAnimInstance* mAnimInstance = nullptr;

		UPROPERTY(Category = "AMainCharacter", BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
			TMap<ZEDAniState, class UAnimMontage*> mAllAnimations;
		//TMap<ZEDAniState, class UAnimMontage*> AllAnimations;

		UPROPERTY(Category = "AMainCharacter", BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
			TArray<AActor*> mNearInteractObj;

		UPROPERTY(Category = "AMainCharacter", BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
			TArray<UInventoryItemData*> mInventoryData;

		UPROPERTY(Category = "AMainCharacter", BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
			TMap<SoundName, class USoundBase*> mAllSoundsMap;

//		UInventoryItemData* Data
		//UPROPERTY(Category = "AMainCharacter", BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		//class UInteracTextSlot* mFocusNowInteractText;
		
};
