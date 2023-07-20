// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "ZedGameInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Ai/NpcCharacter.h"
#include "MyPlayerController.h"
//#include "Math/Vector.h"
#include "GameFramework/SpringArmComponent.h"

AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AniState = ZEDAniState::Idle;
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;
	//
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//캐릭터 이동 모션 관련
	GetCharacterMovement()->bOrientRotationToMovement = false;

	mSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	mSpringArmComp->SetupAttachment(RootComponent);
	mSpringArmComp->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
	mSpringArmComp->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	mFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	mFollowCamera->SetupAttachment(mSpringArmComp, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	mFollowCamera->bUsePawnControlRotation = false;

	
	mParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BlinkParticleComp"));
	mParticleSystemComp->SetupAttachment(GetMesh());

	mIsLockOn = false;
	
	
	

	//
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	WeaponMesh->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshLoader(TEXT("/Script/Engine.StaticMesh'/Game/Resource/BattleWizardPolyart/Meshes/MagicStaffs/Staff02SM.Staff02SM'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshLoader(GetGameInstance<UZedGameInstance>()->GetMesh(TEXT("Staff01SM")));
	if (true == MeshLoader.Succeeded())
	{
		WeaponArrays.Add(MeshLoader.Object);
	}

	
}

//void AMainCharacter::LockOnTarget()
//{
//	UZedGameInstance* Inst = GetGameInstance<UZedGameInstance>();
//
//	bool isEnemyHere = false;
//	
//	if (mIsLockOn == false) 
//	{
//
//		if (Inst->AllNpcCharac.Num() < 1){
//			return;
//		}
//
//		
//		
//
//		for (int i = 0; i < Inst->AllNpcCharac.Num(); ++i)
//		{
//			//UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation());
//			
//
//			
//			if (GetDistanceTo(Inst->AllNpcCharac[i]) < 1000.f)
//			{
//				mIsLockOn = true;
//				GetCharacterMovement()->bOrientRotationToMovement = false;
//				isEnemyHere = true;
//				bUseControllerRotationYaw = true;
//				SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation()));
//				mTargetNpcCharacter = Inst->AllNpcCharac[i];
//				Inst->AllNpcCharac[i]->mLockOnSphere->SetVisibility(true);
//				bUseControllerRotationYaw = false;
//			}
//			
//			
//
//			//mSpringArmComp.setro
//
//			
//
//			//mSpringArmComp->SetWorldRotation(this->GetActorRotation());
//
//			
//			//mSpringArmComp->AddLocalRotation(this->GetActorRotation());
//			//mSpringArmComp->AddLocalRotation(this->GetControlRotation());
//		}
//		if (isEnemyHere == false) {
//			return;
//		}
//	}
//	else
//	{
//		mIsLockOn = false;
//
//		for (int i = 0; i < Inst->AllNpcCharac.Num(); ++i)
//		{
//			//UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation());
//			//SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation()));
//			Inst->AllNpcCharac[i]->mLockOnSphere->SetVisibility(false);
//			mTargetNpcCharacter = nullptr;
//
//			//mSpringArmComp->AddLocalRotation(this->GetActorRotation());
//			//mSpringArmComp->AddLocalRotation(this->GetControlRotation());
//		}
//		GetCharacterMovement()->bOrientRotationToMovement = true;
//	}
//
//	
//}

// Sets default values

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UZedGameInstance* Inst = GetGameInstance<UZedGameInstance>();

	WeaponArrays.Add(GetGameInstance<UZedGameInstance>()->GetMesh(TEXT("Staff01SM")));
	//WeaponArrays.Add(GetGameInstance<UZedGameInstance>()->GetMesh(TEXT("Staff2")));
	//WeaponArrays.Add(GetGameInstance<UZedGameInstance>()->GetMesh(TEXT("Staff3")));


	WeaponMesh->SetStaticMesh(WeaponArrays[1]);

	

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Error, TEXT("%S(%u) %d "), __FUNCTION__, __LINE__, AniState);
	//AniState;
	/*FVector::Zero();

	UE_LOG(LogTemp, Error, TEXT("%S(%u) %f %f %f "), __FUNCTION__, __LINE__, GetCharacterMovement()->GetCurrentAcceleration().X
		, GetCharacterMovement()->GetCurrentAcceleration().Y
		, GetCharacterMovement()->GetCurrentAcceleration().Z);*/
	if (GetCharacterMovement()->GetCurrentAcceleration() == FVector::Zero())
	{
		GetCharacterMovement()->MaxWalkSpeed = 400.f;
		AMyPlayerController* myController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());

		if (myController == nullptr || myController->IsValidLowLevel() == false)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u) myController == nullptr || myController->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
			return;
		}
		UE_LOG(LogTemp, Error, TEXT("%S(%u) %f "), __FUNCTION__, __LINE__, GetCharacterMovement()->MaxWalkSpeed);
		
		if (myController->GetIsShift() == true) {
			myController->SetIsShift(false);
		}
	}
}


