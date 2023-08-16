// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactive/InterObjStaticMeshAct.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "PortalActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API APortalActor : public AInterObjStaticMeshAct
{
	GENERATED_BODY()
	

public:

	APortalActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	UParticleSystemComponent* mPaticleComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	FVector mTargetLocatrion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	APortalActor* mTargetPortal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	FVector mStartPortal;



	UFUNCTION(BlueprintCallable, Category = "Portal")
		void PlayerTeleport();

protected:
	void BeginPlay() override;

private:

	/*UPROPERTY(Category = InteractiveObjMeshActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> mNavigationSphereComp;*/


};
