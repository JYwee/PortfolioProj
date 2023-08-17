// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/Battle/MagicProjectile.h"

// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	mSphereComp->SetupAttachment(RootComponent);
	mSphereComp->SetCollisionProfileName(TEXT("NoCollision"), true);
	mSphereComp->ComponentTags.Add(FName("SphereMagicProj"));

	mNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	mNiagaraComp->SetupAttachment(mSphereComp, TEXT("attachNigara"));

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

	if (mProjectileDestroyTime < 0.f)
	{
		Destroy();
		return;
	}

	AddActorWorldOffset(GetActorLocation() * DeltaTime * mSpeed);
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

