// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Engine/StaticMeshActor.h"
#include "../InteractiveInterface.h"
#include "GameFramework/Actor.h"
#include "InteractiveObject.generated.h"

class CapsuleComponent;

UCLASS()
class PROJECTPORTFOL_API AInteractiveObject : public AActor, public UInteractiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveObject();

	//AInteractiveObject(const FObjectInitializer& ObjectInitializer);

	//UPROPERTY(Category = InteractiveCapsule, EditAnywhere, AdvancedDisplay)
	//static FName CapsuleComponentName;

	virtual void Tick(float DeltaTime) override;
	

protected:
	virtual void BeginPlay() override;

	//using interactive collision
	virtual FORCEINLINE class UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }

	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ANpcCharacter::BeginOverLap);
	virtual void BeginOverLap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);


private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCapsuleComponent> CapsuleComponent;

};


