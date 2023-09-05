// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/NpcCharacter.h"
#include "Components/SceneComponent.h"
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

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(Category = "NPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FVector> mPatrolPostion;
	//USceneComponent*

	UPROPERTY(Category = "NPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName mNpcName;

	UPROPERTY(Category = "NPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* mAI;

	UPROPERTY(Category = "NPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText mInteractDialogues;

};
