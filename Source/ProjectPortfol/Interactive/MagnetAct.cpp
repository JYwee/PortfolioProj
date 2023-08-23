// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/MagnetAct.h"


AMagnetAct::AMagnetAct()
{
	PrimaryActorTick.bCanEverTick = true;


	mCapsuleComponent->SetCapsuleSize(150.f, 150.f, true);
	mCapsuleComponent->ComponentTags.Add("MagnetOBJ");
	Tags.Add("MagnetOBJ");



	//materialerial
	mOriginMaterial = CreateDefaultSubobject<UMaterialInterface>("Originlmaterial");
	mActionMaterial = CreateDefaultSubobject<UMaterialInterface>("Actionlmaterial");;
	// = GetStaticMeshComponent()->GetMaterial(0);
	//mMaterial = UMaterialInterface::create

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

	mOriginMaterial = GetStaticMeshComponent()->GetMaterial(0);
}
	

void AMagnetAct::MovePast()
{
	FTransform pastTrans;
	if (!mPastPos.IsEmpty()) {
		GetStaticMeshComponent()->SetMaterial(0, mActionMaterial);
		mPastPos.Dequeue(pastTrans);
		SetActorTransform(pastTrans);
	}
	else
	{
		mCurrnetTime = 0.f;
		mIsGotoPast = false;
		GetStaticMeshComponent()->SetMaterial(0, mOriginMaterial);
	}
}

void AMagnetAct::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	mCurrnetTime += DeltaSeconds;
	mLimitTime += DeltaSeconds;
	
	if (mIsGotoPast == true)
	{
		MovePast();
		
		//GetStaticMeshComponent()->SetMaterial(0, );
		///Script/Engine.Material'/Engine/EngineDebugMaterials/MAT_LevelColorationLitLightmapUV.MAT_LevelColorationLitLightmapUV'
		//GetStaticMeshComponent().set
	}
	else
	{
		mPastPos.Enqueue(GetActorTransform());
		if (mCurrnetTime > 10.f)
		{
			mPastPos.Pop();
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("%S(%u) %f "), __FUNCTION__, __LINE__, mCurrnetTime);
	//if (mIsGotoPast == true)
	//{
	//	if (mCurrnetTime > 0.1)
	//	{
	//		//FTransform&

	//		MovePast();
	//		mCurrnetTime = 0;
	//	}
	//	else {

	//	}
	//}
	//else {
	//	if (mCurrnetTime > 0.1)
	//	{
	//	//FTransform&
	//	
	//		mPastPos.Enqueue(GetActorTransform());
	//		mCurrnetTime = 0;
	//	}
	//	else
	//	{
	//		

	//	}
	////if(DeltaSeconds * 180);


}
	

