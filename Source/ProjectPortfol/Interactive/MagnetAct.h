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

	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	TQueue<FTransform> mPastPos;

	
	UFUNCTION(BlueprintCallable, Category = "Portal")
	FORCEINLINE void SetIsGotoPast(bool isGo)
	{
		mIsGotoPast = isGo;
	}

	
	UFUNCTION(BlueprintCallable, Category = "Portal")
		void MovePast();

	void Tick(float DeltaSeconds) override;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class  UMaterialInterface* mOriginMaterial = nullptr;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class  UMaterialInterface* mActionMaterial = nullptr;


private:

	


	float mLimitTime = 0.f;
	float mCurrnetTime = 0.f;

	bool mIsGotoPast = false;
	
};
