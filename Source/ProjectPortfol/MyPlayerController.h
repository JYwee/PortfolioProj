// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();
	
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* InPawn) override;


	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	void OpenInvenStatusAction();


protected:
	




	
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;
	
	void AttackAction();
	void JumpOrNextAction();
	//void JumpAxis(float Rate);

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		virtual void MoveForward(float Val);

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		virtual void MoveRight(float Val);

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		virtual void MoveUp_World(float Val);

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		virtual void TurnAtRate(float Rate);

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		virtual void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		void FocusTurn(float Rate);

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		void ShiftAction();

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		void LockOnTarget();

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		void InteractAction();
	
	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		void UpUiInteractAction();

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		void DownUiInteractAction();

	
	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		void Aiming(float Rate);



	//UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	//	void AMainCharacter::Look(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AMainCharacter")
		float BaseTurnRate;

	/** Base lookup rate, in deg/sec. Other scaling may affect final lookup rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AMainCharacter")
		float BaseLookUpRate;

public:

	FORCEINLINE bool GetIsShift() {
		return mIsShift;
	}


	FORCEINLINE void SetIsShift(bool isShift) {
		mIsShift = isShift;
	}

	/*FORCEINLINE class ANpcCharacter* GetLockOnTargetNpc() {
		return LockOnTargetNpcCharacter;
	}

	FORCEINLINE void SetLockOnTargetNpc(class ANpcCharacter* targetNpc) {
		LockOnTargetNpcCharacter = targetNpc;
	}*/
	//TArray<class ANpcCharacter*>
	class ANpcCharacter* Visibility_GetRenderedActors(class ANpcCharacter*, float MinRecentTime);

	UPROPERTY(Category = "AMainCharacter", VisibleAnywhere , BlueprintReadWrite)
		UUserWidget* mWdgLockOn;


	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
		FORCEINLINE	class AMainCharacter* GetMyCharacter() const
	{
		return myCharacter;
	}


private:
	class AMainCharacter* myCharacter;

	bool mIsShift = false;

	bool mIsUiControlling = false;
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AMainCharacter")
	class ANpcCharacter* LockOnTargetNpcCharacter;*/
};
