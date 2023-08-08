// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/MagnetAct.h"


AMagnetAct::AMagnetAct()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMagnetAct::MovePast()
{
	FTransform pastTrans;
	mPastPos.Dequeue(pastTrans);

	SetActorTransform(pastTrans);
}

void AMagnetAct::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	mCurrnetTime += DeltaSeconds;
	mLimitTime += DeltaSeconds;
	if (mIsGotoPast == true)
	{
		if (mCurrnetTime > 60)
		{
			//FTransform&

			MovePast();
			mCurrnetTime = 0;
		}
		else {

		}
	}
	else {
		if (mCurrnetTime > 60)
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
