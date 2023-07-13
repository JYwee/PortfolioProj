// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcPawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ANpcPawn::ANpcPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANpcPawn::BeginPlay()
{
	Super::BeginPlay();
	
	
	
	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ANpcPawn::BeginOverLap);
}

// Called every frame
void ANpcPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANpcPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANpcPawn::BeginOverLap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{

	if (OtherActor->ActorHasTag(TEXT("Weapon")))
	{
		this->Destroy();
	}

	SweepResult.Distance;
	SweepResult.FaceIndex;
	SweepResult.GetActor();

}
