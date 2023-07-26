// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZedEnums.h"
#include "MainCharacter.generated.h"

UCLASS()
class PROJECTPORTFOL_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()


	
public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	FORCEINLINE	TMap<ZEDAniState, class UAnimMontage*> GetAllAnimations() {
		return mAllAnimations;
	}
	
	template<typename EnumType>
	void SetAllAnimation(const TMap<EnumType, class UAnimMontage*>& mapAnimation)
	{
		for (TPair<EnumType, UAnimMontage*> Pair : mapAnimation)
		{
			mAllAnimations.Add(static_cast<int>(Pair.Key), Pair.Value);
		}
	}

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

private:
		int mHealthPoint;

		float mStaminaPoint;

		int mAttack;

		int mDefense;

		bool mIsLockOn;

		UPROPERTY(Category = "AMainCharacter", BlueprintReadOnly)
			ZEDAniState mAniState;
		//ZEDAniState AniState;

		UPROPERTY(Category = "AMainCharacter", BlueprintReadOnly)
			TMap<ZEDAniState, class UAnimMontage*> mAllAnimations;
		//TMap<ZEDAniState, class UAnimMontage*> AllAnimations;

};
