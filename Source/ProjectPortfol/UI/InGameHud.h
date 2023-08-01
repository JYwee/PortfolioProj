// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameMainWidget.h"
#include "InGameHud.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API AInGameHud : public AHUD
{
	GENERATED_BODY()
	
public:
	AInGameHud();
	~AInGameHud();

	UInGameMainWidget* GetMainWidget()
	{
		return mInGameMainWdgt;
	}

protected:
	void BeginPlay() override;
	void Tick(float _Delta) override;

private:
	//TSubclassOf<UUserWidget> MainWidgetClass = nullptr;

	UInGameMainWidget* mInGameMainWdgt = nullptr;

};
