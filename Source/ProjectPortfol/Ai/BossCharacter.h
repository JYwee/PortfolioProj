// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/NpcCharacter.h"
#include <Data/BossDataTable.h>
#include "BossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API ABossCharacter : public ANpcCharacter
{
	GENERATED_BODY()

public:
	ABossCharacter();

	const struct FBossDataTable* mCurBossData;

	virtual void Tick(float DeltaTime) override;

	void BeginPlay() override;

	BossPhase GetPhase()
	{
		return mPhase;
	}
	
	void SetPhase(BossPhase newPhase)
	{
		mPhase = newPhase;
		return;
	}

private:

	UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FName mBossName;

	//UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//	USkeletalMesh* Mesh;

	UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int mHealthPoint;

	UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int mShieldPoint;

	UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int mStemina;


	UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int mAtt;

	UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int mDef;

	UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	BossPhase mPhase;

	UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ZEDElementalState mElementalType;

	UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FVector mPostionOri;

	//UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//	TMap<BossAniState, class UAnimMontage*> MapAnimation;

	UPROPERTY(Category = "BossChara", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* mAI;
	
};
