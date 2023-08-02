// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/InterObjStaticMeshAct.h"

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
	mCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractiveCapsule"));
	
	FVector Origin, Extent;
	GetActorBounds(false, Origin, Extent);
	
	//mCapsuleComponent->InitCapsuleSize(Extent.X * 0.5f, Extent.Y * 0.5f);
	mCapsuleComponent->InitCapsuleSize(100.f, 100.f);
	mCapsuleComponent->ComponentTags.Add(TEXT("Interactive"));
	mCapsuleComponent->SetupAttachment(RootComponent);
	
	mCapsuleComponent->SetMobility(EComponentMobility::Static);
}

void AInterObjStaticMeshAct::BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	float x, y;
	mCapsuleComponent->GetScaledCapsuleSize(x, y);
	UE_LOG(LogTemp, Warning, TEXT("%S(%u) %f, %f"), __FUNCTION__, __LINE__, x, y);
}

void AInterObjStaticMeshAct::BeginPlay()
{
	Super::BeginPlay();

	FVector Origin, Extent;
	GetActorBounds(false, Origin, Extent);
	mCapsuleComponent->SetCapsuleSize(Extent.X * 0.5f, Extent.Y * 0.5f, true);
	
	
	//mCapsuleComponent->InitCapsuleSize(Extent.X * 0.5f, Extent.Y * 0.5f);
	GetInteractCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AInterObjStaticMeshAct::BeginOverLap);
}
