// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive/InterObjStaticMeshAct.h"
#include "PortalActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API APortalActor : public AInterObjStaticMeshAct
{
	GENERATED_BODY()
	

public:

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	FVector mTargetPortal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	FVector mStartPortal;

	UFUNCTION(BlueprintCallable, Category = "Portal")
		void PlayerTeleport();

private:


};
