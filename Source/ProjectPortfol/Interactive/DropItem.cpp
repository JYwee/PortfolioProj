// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/DropItem.h"

ADropItem::ADropItem()
{
	PrimaryActorTick.bCanEverTick = true;

	
	mNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	mNiagaraComp->SetupAttachment(RootComponent, TEXT("attachNigara"));
}

ADropItem::~ADropItem()
{
}

void ADropItem::BeginPlay()
{
	Super::BeginPlay();

	FVector3f InColorVec;
	
	

	//Particle_SetColorFromVector(FVector3f(0.f, 0.f, 0.f), );
		//const FVector3f& InColorVec, const float InAlpha, FLinearColor& OutColor
		/*OutColor.R = InColorVec.X;
		OutColor.G = InColorVec.Y;
	OutColor.B = InColorVec.Z;
	OutColor.A = InAlpha;*/

	mNiagaraComp->GetAsset();
}
