// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMode.h"
#include "MainCharacter.h"

bool AInGameMode::GetPlayerAttProcessing() const
{
	return mMainCharacter->IsMeleeAttProcessing();
}

void AInGameMode::SetPlayerAttProcess(bool meleeAttProcess)
{
	mMainCharacter->SetIsMeleeAttProcess(meleeAttProcess);
}
