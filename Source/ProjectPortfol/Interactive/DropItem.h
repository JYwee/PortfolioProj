// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive/InterObjStaticMeshAct.h"
//#include "InteractiveObject.h"
#include "NiagaraComponent.h"
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
	
	//virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* mNiagaraComp = nullptr;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int mRank;


};
