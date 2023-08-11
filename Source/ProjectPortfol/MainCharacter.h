// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZedEnums.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.generated.h"

UCLASS()
class PROJECTPORTFOL_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()


	
public:
	// Sets default values for this character's properties
	AMainCharacter();


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
		void EndOverlap(
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
	
	
	void SetAllAnimation(const TMap<int, class UAnimMontage*>& mapAnimation)
	{
		for (TPair<int, UAnimMontage*> Pair : mapAnimation)
		{
			mAllAnimations.Add(static_cast<ZEDAniState>(Pair.Key), Pair.Value);
		}
	}

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	void InteractAction();

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

//mNearInteractObj
	
	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	FORCEINLINE TArray<AActor*> GetNearInteractObj() {
		return mNearInteractObj;
	}

private:
		int mHealthPoint;

		float mStaminaPoint;

		int mAttack;

		int mDefense;

		bool mIsLockOn;

		UPROPERTY(Category = "AMainCharacter", BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
			ZEDAniState mAniState;
		//ZEDAniState AniState;
		
		
		UPROPERTY(Category = "AMainCharacter", BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
			TMap<ZEDAniState, class UAnimMontage*> mAllAnimations;
		//TMap<ZEDAniState, class UAnimMontage*> AllAnimations;

		UPROPERTY(Category = "AMainCharacter", BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
			TArray<AActor*> mNearInteractObj;


};
