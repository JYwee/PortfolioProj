// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject.h"
#include "TestCapsuleComponent.h"
#include "Engine/StaticMeshActor.h"
#include "InterObjStaticMeshAct.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API AInterObjStaticMeshAct : public AStaticMeshActor/*, public AInteractiveObject*/
{
	GENERATED_BODY()
	
public:

	AInterObjStaticMeshAct();

	FORCEINLINE class UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }
	//virtual void Tick(float DeltaTime) override;

protected:
	//virtual void BeginPlay() override;

private:

	UPROPERTY(Category = InteractiveObjMeshActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	//TObjectPtr<UCapsuleComponent> CapsuleComponent;
};
