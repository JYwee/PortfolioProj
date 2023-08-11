// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "InGameMode.generated.h"



class AMainCharacter;
/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API AInGameMode : public AGameMode
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = InGameMode)
		AMainCharacter* GetMainCharacter() const { return mMainCharacter; }

	UFUNCTION(BlueprintCallable, Category = InGameMode)
	FORCEINLINE void SetMainCharacter(AMainCharacter* mainCharac) { mMainCharacter = mainCharac; }
protected:


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InGameMode, meta = (AllowPrivateAccess = "true"))
	AMainCharacter* mMainCharacter;
};
