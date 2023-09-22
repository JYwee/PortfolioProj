// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "MagicProjectile.generated.h"

UCLASS()
class PROJECTPORTFOL_API AMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		FORCEINLINE USphereComponent* GetSphereComponent()
	{
		return mSphereComp;
	}
	


private:
	UPROPERTY(Category = "MagicProj", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mSpeed = 1000.0f;

	UPROPERTY(Category = "MagicProj", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mProjectileDestroyTime = 3.0f;

	UPROPERTY(Category = "MagicProj", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> mDestroyEffectObject = nullptr;

	UFUNCTION()
		void DestroyProjectile(AActor* _Destroy);

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* mSphereComp = nullptr;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UNiagaraComponent* mNiagaraComp = nullptr;

	FVector mDirection = FVector::Zero();


	UFUNCTION(BlueprintCallable, Category = "MagicProj")
		void BeginOverLap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

	//UPROPERTY(VisibleAnywhere, Category = Movement)
	//	class UProjectileMovementComponent* mProjectileMovementComponent;
};
