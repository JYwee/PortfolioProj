// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive/InterObjStaticMeshAct.h"
#include "../Data/ItemDataTable.h"
#include "NiagaraComponent.h"
#include "../ZedEnums.h"
#include "DropItem.h"
#include "LootObject.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API ALootObject : public AInterObjStaticMeshAct
{
	GENERATED_BODY()
	
public:
	ALootObject();
	~ALootObject() {}

	virtual void BeginPlay() override;

	//virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	TArray<ADropItem*> GetDropItemArray()
	{
		return mDropItemArray;
	};

	UFUNCTION(BlueprintCallable, Category = "AMainCharacter")
	void TestDropItem();

private:

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* mNiagaraComp = nullptr;

	UPROPERTY(Category = "LootDropArr", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<ADropItem*> mDropItemArray;
};
