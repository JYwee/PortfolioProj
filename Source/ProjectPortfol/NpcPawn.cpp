// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcPawn.h"
//#include "Components/CapsuleComponent.h"


FName ANpcPawn::CapsuleComponentName(TEXT("CollisionCylinder"));

// Sets default values
ANpcPawn::ANpcPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(ANpcPawn::CapsuleComponentName);
	CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;
}

// Called when the game starts or when spawned
void ANpcPawn::BeginPlay()
{
	Super::BeginPlay();
	
	
	
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ANpcPawn::BeginOverLap);
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
	if (OtherComp->ComponentHasTag(TEXT("Weapon")))
	{
		this->Destroy();
	}

	SweepResult.Distance;
	SweepResult.FaceIndex;
	SweepResult.GetActor();

}
