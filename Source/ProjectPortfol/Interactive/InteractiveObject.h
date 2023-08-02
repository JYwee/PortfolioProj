// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Engine/StaticMeshActor.h"
#include "../InteractiveInterface.h"
#include "GameFramework/Actor.h"
#include "InteractiveObject.generated.h"

class UCapsuleComponent;

UCLASS()
class PROJECTPORTFOL_API AInteractiveObject : public AActor, public IInteractiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveObject();

	//AInteractiveObject(const FObjectInitializer& ObjectInitializer);

	//UPROPERTY(Category = InteractiveCapsule, EditAnywhere, AdvancedDisplay)
	//static FName CapsuleComponentName;

	virtual void Tick(float DeltaTime) override;
	
	FORCEINLINE virtual class UCapsuleComponent* GetInteractCapsuleComponent() const override { return CapsuleComponent; }
	
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

	//using interactive collision
	

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCapsuleComponent> CapsuleComponent;
		//UCapsuleComponent* CapsuleComponent;

};


