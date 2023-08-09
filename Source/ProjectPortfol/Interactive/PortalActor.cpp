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

	//myGameMode->GetMainCharacter()->SetActorLocation(mTargetPortal);
}
