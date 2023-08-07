// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/PortalActor.h"
#include "Kismet/GameplayStatics.h"
#include <InGameMode.h>

void APortalActor::PlayerTeleport()
{
	//GetWorld().getplayer
	AInGameMode* myGameMode =  Cast<AInGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (myGameMode == nullptr || myGameMode->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  myGameMode->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}

	myGameMode->GetMainCharacter();
}
