// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AMainCharacter")
		float BaseTurnRate;

	/** Base lookup rate, in deg/sec. Other scaling may affect final lookup rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AMainCharacter")
		float BaseLookUpRate;

};
