// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractiveInterface.h"
#include "Engine/StaticMeshActor.h"
#include "InterObjStaticMeshAct.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API AInterObjStaticMeshAct : public AStaticMeshActor, public IInteractiveInterface
{
	GENERATED_BODY()
	
public:

	AInterObjStaticMeshAct();

	//virtual void Tick(float DeltaTime) override;

	FORCEINLINE virtual class UCapsuleComponent* GetInteractCapsuleComponent() const override { return mCapsuleComponent; }

	UFUNCTION(BlueprintCallable, Category = InteractiveCollision)
	virtual void BeginOverLap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;


protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(Category = InteractiveObjMeshActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> mCapsuleComponent;
	//class UCapsuleComponent* CapsuleComponent;

	
};
