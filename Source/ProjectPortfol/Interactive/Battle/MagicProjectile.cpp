// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/Battle/MagicProjectile.h"
#include <MyPlayerController.h>
#include <MainCharacter.h>
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = mSphereComp;
	mSphereComp->SetCollisionProfileName(TEXT("NoCollision"), true);
	mSphereComp->ComponentTags.Add(FName("SphereMagicProj"));
	

	mNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	mNiagaraComp->SetupAttachment(RootComponent, TEXT("attachNigara"));

	/*if (mProjectileMovementComponent != nullptr)
	{
		mProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		mProjectileMovementComponent->SetUpdatedComponent(mSphereComp);
		mProjectileMovementComponent->InitialSpeed = 1000.0f;
		mProjectileMovementComponent->MaxSpeed = 1000.0f;
		mProjectileMovementComponent->bRotationFollowsVelocity = true;
		mProjectileMovementComponent->bShouldBounce = false;
		mProjectileMovementComponent->Bounciness = 0.3f;
		mProjectileMovementComponent->ProjectileGravityScale = 9.0f;
	}*/
}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	OnDestroyed.AddDynamic(this, &AMagicProjectile::DestroyProjectile);
}

// Called every frame
void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mProjectileDestroyTime -= DeltaTime;
	
	UE_LOG(LogTemp, Error, TEXT("%S(%u) %f, %f, %f"), __FUNCTION__, __LINE__, GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

	if (mProjectileDestroyTime < 0.0f)
	{
		Destroy();
		return;
	}
	
	if (mDirection == FVector::Zero())
	{
		AMyPlayerController* playerController = GetWorld()->GetFirstPlayerController<AMyPlayerController>();
		SetActorRotation(playerController->GetMyCharacter()->GetFollowCameraRotator());
		mDirection = playerController->GetMyCharacter()->GetFollowCameraRotator().Vector();
	}
	else {
		AddActorWorldOffset(mDirection * DeltaTime * mSpeed);
	}
	
	
	
	//FVector tmp = GetActorForwardVector() + playerController->GetMyCharacter()->GetFollowCameraRotator().Vector();
	
	
}

void AMagicProjectile::DestroyProjectile(AActor* _Destroy)
{
	if(nullptr == mDestroyEffectObject)
	{
		return;
	}

	AActor* Actor = GetWorld()->SpawnActor<AActor>(mDestroyEffectObject);

	Actor->SetActorLocation(GetActorLocation());
	Actor->SetActorRotation(GetActorRotation());
}

