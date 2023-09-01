// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive/InterObjStaticMeshAct.h"
//#include "InteractiveObject.h"
#include "NiagaraComponent.h"
#include <Data/ItemDataTable.h>
#include <ZedEnums.h>
#include "DropItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API ADropItem : public AInterObjStaticMeshAct //AInteractiveObject   
{
	GENERATED_BODY()
	
public:

	ADropItem();
	~ADropItem();

	virtual void BeginPlay() override;
	
	bool Init(FItemDataTable* itemData);
	//virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//FItemDataTable* GetItemData()// const
	//{
	//	return mItemData;
	//}

	
	const FItemDataTable* mItemData;

private:

	UPROPERTY(Category = "DropItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* mNiagaraComp = nullptr;

	UPROPERTY(Category = "DropItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText mNameItem;
	UPROPERTY(Category = "DropItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText mExplain;
	UPROPERTY(Category = "DropItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMesh* mItemMesh;
	UPROPERTY(Category = "DropItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UObject> mObject;
	UPROPERTY(Category = "DropItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ItemType mItemType;
	UPROPERTY(Category = "DropItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	RankItem mRank;
	UPROPERTY(Category = "DropItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	uint8 mStackSize;
	//UPROPERTY(Category = "DropItem", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	
};
