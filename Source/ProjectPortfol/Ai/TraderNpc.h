// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/CrowdNpc.h"
#include "TraderNpc.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API ATraderNpc : public ACrowdNpc
{
	GENERATED_BODY()
	

public:
	ATraderNpc();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


private:

	UPROPERTY(Category = "TradeNPC", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class ADropItem*> mTradeInventory;

};
