// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/NpcCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "CrowdNpc.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API ACrowdNpc : public ANpcCharacter
{
	GENERATED_BODY()
	

public:
	ACrowdNpc();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Npc)
		FORCEINLINE  TArray<FText> GetInteractDialogues() const{
		return mInteractDialogues;
	}

	UFUNCTION(BlueprintCallable, Category = Npc)
	FORCEINLINE  FName GetNpcID() const {
		return mNpcID;
	}
	
	UFUNCTION(BlueprintCallable, Category = Npc)
		FORCEINLINE  FText GetNpcName() const {
		return mNpcFTextName;
	}

	UFUNCTION(BlueprintCallable, Category = Npc)
	FVector GetNextMovePos();

protected:
	virtual void BeginPlay() override;

	/*UFUNCTION(BlueprintCallable, Category = ACrowdNpc)
		void BeginOverLap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		) override;*/

private:

	UPROPERTY(Category = "NPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USplineComponent* mSplineComp;


	UPROPERTY(Category = "NPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FVector> mPatrolPostion;
	//USceneComponent*

	UPROPERTY(Category = "NPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName mNpcID;

	UPROPERTY(Category = "NPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText mNpcFTextName;

	UPROPERTY(Category = "NPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* mAI;

	UPROPERTY(Category = "NPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<FText> mInteractDialogues;

		int mCurSplinePointIndex = 0;

	
		void TakeDamageNpcBase(uint8 damageValue) override;

};
