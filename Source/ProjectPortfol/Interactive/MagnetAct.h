// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive/InterObjStaticMeshAct.h"
#include "MagnetAct.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API AMagnetAct : public AInterObjStaticMeshAct
{
	GENERATED_BODY()

	AMagnetAct();

public:


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	TQueue<FTransform> mPastPos;

	

	
	UFUNCTION(BlueprintCallable, Category = "Portal")
		void MovePast();

	void Tick(float DeltaSeconds) override;

private:

	float mCurrnetTime;

	bool mIsGotoPast = false;
	
};
