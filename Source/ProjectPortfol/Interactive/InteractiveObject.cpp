// Fill out your copyright notice in the Description page of Project Settings.



#include "InteractiveObject.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AInteractiveObject::AInteractiveObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractiveCapsule"));
	CapsuleComponent->InitCapsuleSize(30.0f, 30.0f);
	CapsuleComponent->ComponentTags.Add(TEXT("Interactive"));
	//CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
}

//AInteractiveObject::AInteractiveObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
//{
//}

void AInteractiveObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();

	FVector Origin, Extent;
	GetActorBounds(false, Origin, Extent);
	//mCapsuleComponent->SetCapsuleSize(Extent.X * 0.5f, Extent.Y * 0.5f, true);
	CapsuleComponent->SetCapsuleSize(Extent.X + 50.f, Extent.Y + 50.f, true);

}

//UCapsuleComponent* AInteractiveObject::GetCapsuleComponent() const
//{
//	return  CapsuleComponent;
//}

void AInteractiveObject::BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


