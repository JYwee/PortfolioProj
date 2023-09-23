// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MiniMapComponent.h"
#include <Ai/NpcCharacter.h>

// Sets default values for this component's properties
UMiniMapComponent::UMiniMapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMiniMapComponent::Init(ANpcCharacter* owner)
{
	mSpringArmComponent = owner->CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	mSpringArmComponent->TargetArmLength = 5000.0f;
	mSpringArmComponent->SetupAttachment(this);
	mSpringArmComponent->bUsePawnControlRotation = false;
	mSpringArmComponent->bInheritPitch = false;
	mSpringArmComponent->bInheritRoll = false;
	mSpringArmComponent->bInheritYaw = false;

	owner->PushComponent(mSpringArmComponent);

	FVector dir = FVector(0.0f, 0.0f, -1.0f);
	mSpringArmComponent->SetRelativeRotation(dir.Rotation());
	//FString path = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'");
	ConstructorHelpers::FObjectFinder<UStaticMesh> dataTable(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	UStaticMesh* staticMesh;


	if (dataTable.Succeeded())
	{
		staticMesh = dataTable.Object;
		mStaticMeshComponent = owner->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
		mStaticMeshComponent->SetStaticMesh(staticMesh);
		mStaticMeshComponent->SetupAttachment(mSpringArmComponent);
		owner->PushComponent(mStaticMeshComponent);
		// StaticMeshComponent->roation
		// FVector Dir = FVector(0.0f, 0.0f, 1.0f);
		// StaticMeshComponent->AddLocalRotation();
	}
}


// Called when the game starts
void UMiniMapComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMiniMapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

