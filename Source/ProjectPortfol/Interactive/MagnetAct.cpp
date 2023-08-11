// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/MagnetAct.h"


AMagnetAct::AMagnetAct()
{
	PrimaryActorTick.bCanEverTick = true;


	mCapsuleComponent->SetCapsuleSize(150.f, 150.f, true);
	mCapsuleComponent->ComponentTags.Add("MagnetOBJ");
	Tags.Add("MagnetOBJ");

	//FVector Origin, Extent;
	//GetActorBounds(false, Origin, Extent);
	////mCapsuleComponent->SetCapsuleSize(Extent.X * 0.5f, Extent.Y * 0.5f, true);
	//mCapsuleComponent->SetCapsuleSize(Extent.X + 50.f, Extent.Y + 50.f, true);

}

void AMagnetAct::BeginPlay()
{
	/*FVector Origin, Extent;
	GetActorBounds(false, Origin, Extent);
	mCapsuleComponent->SetCapsuleSize(Extent.X + 50.f, Extent.Y + 50.f, true);*/
	Super::BeginPlay();
}
	

void AMagnetAct::MovePast()
{
	FTransform pastTrans;
	if (!mPastPos.IsEmpty()) {
		mPastPos.Dequeue(pastTrans);
	}
	

	SetActorTransform(pastTrans);
}

void AMagnetAct::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	mCurrnetTime += DeltaSeconds;
	mLimitTime += DeltaSeconds;
	if (mIsGotoPast == true)
	{
		if (mCurrnetTime > 1)
		{
			//FTransform&

			MovePast();
			mCurrnetTime = 0;
		}
		else {

		}
	}
	else {
		if (mCurrnetTime > 1)
		{
		//FTransform&
		
			mPastPos.Enqueue(GetActorTransform());
			mCurrnetTime = 0;
		}
		else
		{
			

		}
	//if(DeltaSeconds * 180);


	}
	
}
