// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/InterObjStaticMeshAct.h"
#include "../ZedGameInstance.h"
#include "../Data/ObjDataTable.h"
#include "../MainCharacter.h"
#include "../UI/InGameHud.h"
#include "../UI/InteracTextListWidget.h"

//void AInterObjStaticMeshAct::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}
//
//void AInterObjStaticMeshAct::BeginPlay()
//{
//	Super::BeginPlay();
//}
//

AInterObjStaticMeshAct::AInterObjStaticMeshAct()
{
	

	//FObjDataTable = gameInst->GetObjInteractData(TEXT("TeleportGate"));


	mCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractiveCapsule"));
	
	/*FVector Origin, Extent;
	GetActorBounds(false, Origin, Extent);
	*/
	//mCapsuleComponent->InitCapsuleSize(Extent.X * 0.5f, Extent.Y * 0.5f);
	mCapsuleComponent->InitCapsuleSize(100.f, 100.f);
	
	mCapsuleComponent->ComponentTags.Add(TEXT("Interactive"));
	mCapsuleComponent->SetupAttachment(RootComponent);
	
	
	mCapsuleComponent->SetMobility(EComponentMobility::Static);
}

void AInterObjStaticMeshAct::BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag(TEXT("Weapon")))
	{
		this->Destroy();
	}
	if (OtherComp->ComponentHasTag(TEXT("PlayerCapsuleComp")))
	{
		

		UE_LOG(LogTemp, Warning, TEXT("%S(%u) Find"), __FUNCTION__, __LINE__);
	}
	//float x, y;
	//mCapsuleComponent->GetScaledCapsuleSize(x, y);
	// test static capsule can chagne size 
	//x += 100.f;
	//y += 100.f;
	//mCapsuleComponent->SetCapsuleSize(x, y, true);
	//UE_LOG(LogTemp, Warning, TEXT("%S(%u) %f, %f"), __FUNCTION__, __LINE__, x, y);
	

}

void AInterObjStaticMeshAct::BeginPlay()
{
	Super::BeginPlay();

	
	//UE_LOG(LogTemp, Error, TEXT("%S(%u) %s"), __FUNCTION__, __LINE__ , mObjData->InteractiveText.ToString());

	FVector Origin, Extent;
	GetActorBounds(false, Origin, Extent);
	//mCapsuleComponent->SetCapsuleSize(Extent.X * 0.5f, Extent.Y * 0.5f, true);
	mCapsuleComponent->SetCapsuleSize(Extent.X + 50.f , Extent.Y + 50.f, true);
	
	//mCapsuleComponent->InitCapsuleSize(Extent.X * 0.5f, Extent.Y * 0.5f);
	GetInteractCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AInterObjStaticMeshAct::BeginOverLap);
}
