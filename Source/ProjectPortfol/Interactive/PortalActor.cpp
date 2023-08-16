// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/PortalActor.h"
#include "Kismet/GameplayStatics.h"
#include <MainCharacter.h>
#include <InGameMode.h>


APortalActor::APortalActor()
{
	GetInteractCapsuleComponent();

	mCapsuleComponent->SetCapsuleHalfHeight(150.f);
	mCapsuleComponent->SetCapsuleRadius(150.f);
	mCapsuleComponent->ComponentTags.Add(TEXT("TeleportGate"));

	//mPaticleComp->Activate(true);
	//
	mPaticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PaticleComp"));
	
	mPaticleComp->SetWorldScale3D(FVector3d(0.7f, 0.7f, 0.7f));
	mPaticleComp->SetupAttachment(RootComponent);
	
	//mNavigationSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("NavigationSphereComp"));
	

	Tags.Add("TeleportGate");
}



void APortalActor::PlayerTeleport()
{
	//GetWorld().getplayer
	AInGameMode* myGameMode =  Cast<AInGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (myGameMode == nullptr || myGameMode->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  myGameMode->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}

	myGameMode->GetMainCharacter()->SetActorLocation(mTargetLocatrion, false);

	

	//const FVector& NewLocation, bool bSweep, FHitResult* OutSweepHitResult, ETeleportType Teleport
}

void APortalActor::BeginPlay()
{
	Super::BeginPlay();

	if (mTargetPortal != nullptr)
	{
		mTargetLocatrion = mTargetPortal->GetActorLocation();
	}
}
