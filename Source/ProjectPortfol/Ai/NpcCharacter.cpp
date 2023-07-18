// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcCharacter.h"
#include "Components/CapsuleComponent.h"
#include "ZedGameInstance.h"

// Sets default values
ANpcCharacter::ANpcCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mLockOnSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	mLockOnSphere->SetupAttachment(RootComponent);
	mLockOnSphere->SetVisibility(false);

}

// Called when the game starts or when spawned
void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ANpcCharacter::BeginOverLap);

	UZedGameInstance* Inst = GetGameInstance<UZedGameInstance>();
	
	if (Inst == nullptr || Inst->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr Inst->IsValidLowLevel() == false" ), __FUNCTION__, __LINE__);
		return;
	}

	Inst->AllNpcCharac.Add(this);
}

// Called every frame
void ANpcCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANpcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANpcCharacter::Destroyed()
{
	Super::Destroy();

	/*UZedGameInstance* Inst = GetGameInstance<UZedGameInstance>();

	if (Inst == nullptr || Inst->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  nst->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}

	Inst->AllNpcCharac.;*/
}


void ANpcCharacter::BeginOverLap(
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


