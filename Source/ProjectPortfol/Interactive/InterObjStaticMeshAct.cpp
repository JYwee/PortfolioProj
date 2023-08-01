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
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractiveCapsule"));
	CapsuleComponent->InitCapsuleSize(30.0f, 30.0f);
	CapsuleComponent->ComponentTags.Add(TEXT("Interactive"));
	CapsuleComponent->SetupAttachment(RootComponent);
}
