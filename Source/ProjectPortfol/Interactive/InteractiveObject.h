// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Engine/StaticMeshActor.h"

#include "GameFramework/Actor.h"
#include "InteractiveObject.generated.h"

class CapsuleComponent;

UCLASS()
class PROJECTPORTFOL_API AInteractiveObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveObject();

	//AInteractiveObject(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE class UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }

	//UPROPERTY(Category = InteractiveCapsule, EditAnywhere, AdvancedDisplay)
	//static FName CapsuleComponentName;

	virtual void Tick(float DeltaTime) override;
	

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCapsuleComponent> CapsuleComponent;

};


