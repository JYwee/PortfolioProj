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



protected:
	




	
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;
	
	void AttackAction();
	void JumpAction();
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

	UPROPERTY(Category = "AMainCharacter", VisibleAnywhere , BlueprintReadWrite)
		UUserWidget* mWdgLockOn;

private:
	class AMainCharacter* myCharacter;

	bool mIsShift = false;

	
};
