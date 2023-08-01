// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHud.h"

AInGameHud::AInGameHud() {

}

AInGameHud::~AInGameHud() {

}

void AInGameHud::BeginPlay()
{
	Super::BeginPlay();

	FSoftClassPath ClassPath(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/InGameUI/Wdg_InGameMain.Wdg_InGameMain'"));
	TSubclassOf<UUserWidget> MainWidgetClass = ClassPath.TryLoadClass<UUserWidget>();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
	mInGameMainWdgt = Cast<UInGameMainWidget>(Widget);
	mInGameMainWdgt->AddToViewport();

	{
		//UUserWidget* Window = Cast<UUserWidget>(mInGameMainWdgt->GetWidgetFromName(TEXT("TalkTextWindow")));

		// Window->SetVisibility(ESlateVisibility::Hidden);
		// Window->Visibility = ESlateVisibility::Visible;


	}

	{
		//UUserWidget* Window = Cast<UUserWidget>(mInGameMainWdgt->GetWidgetFromName(TEXT("StatusWindow")));
	}

}

void AInGameHud::Tick(float _Delta)
{
	Super::Tick(_Delta);
}