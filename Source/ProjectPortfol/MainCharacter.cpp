// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "ZedGameInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Ai/NpcCharacter.h"
//#include "Math/Vector.h"
#include "GameFramework/SpringArmComponent.h"

AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	mSpringArmComp->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	mSpringArmComp->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	mFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	mFollowCamera->SetupAttachment(mSpringArmComp, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	mFollowCamera->bUsePawnControlRotation = false;


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

void AMainCharacter::LockOnTarget()
{
	UZedGameInstance* Inst = GetGameInstance<UZedGameInstance>();
	
	if (mIsLockOn == false) 
	{

		if (Inst->AllNpcCharac.Num() < 1){
			return;
		}

		mIsLockOn = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;

		for (int i = 0; i < Inst->AllNpcCharac.Num(); ++i)
		{
			//UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation());
			SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation()));

			mTargetNpcCharacter = Inst->AllNpcCharac[i];
			Inst->AllNpcCharac[i]->mLockOnSphere->SetVisibility(true);

			mSpringArmComp->AddLocalRotation(this->GetActorRotation());
			mSpringArmComp->AddLocalRotation(this->GetControlRotation());
		}
	}
	else
	{
		mIsLockOn = false;

		for (int i = 0; i < Inst->AllNpcCharac.Num(); ++i)
		{
			//UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation());
			//SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation()));
			Inst->AllNpcCharac[i]->mLockOnSphere->SetVisibility(false);
			mTargetNpcCharacter = nullptr;

			mSpringArmComp->AddLocalRotation(this->GetActorRotation());
			mSpringArmComp->AddLocalRotation(this->GetControlRotation());
		}
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}

	
}

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

}



 //Called to bind functionality to input
//void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//static bool bBindingsAdded = false;
	//if (!bBindingsAdded)
	//{
	//	bBindingsAdded = true;

	//	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveForward", EKeys::W, 1.f));
	//	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveForward", EKeys::S, -1.f));

	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveForward", EKeys::Gamepad_LeftY, 1.f));

	//	//왼쪽 오른쪽 움직임
	//	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveRight", EKeys::A, -1.f));
	//	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveRight", EKeys::D, 1.f));

	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_TurnRate", EKeys::A, -1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_TurnRate", EKeys::D, 1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_Turn", EKeys::A, -1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_Turn", EKeys::D, 1.f));


	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveRight", EKeys::Gamepad_LeftX, 1.f));

	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveUp", EKeys::Gamepad_LeftThumbstick, 1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveUp", EKeys::Gamepad_RightThumbstick, -1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveUp", EKeys::Gamepad_FaceButton_Bottom, 1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveUp", EKeys::LeftControl, -1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveUp", EKeys::SpaceBar, 1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::C, -1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::E, 1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Q, -1.f));

	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_TurnRate", EKeys::Gamepad_RightX, 1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_TurnRate", EKeys::Left, -1.f));
	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_TurnRate", EKeys::Right, 1.f));
	//	
	//	
	//	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_Turn", EKeys::MouseX, 1.f));

	//	//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_LookUpRate", EKeys::Gamepad_RightY, 1.f));
	//	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_LookUp", EKeys::MouseY, -1.f));

	//	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerAttack"), EKeys::LeftMouseButton));
	//	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJumpAction"), EKeys::SpaceBar));
	//	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("Lock_On"), EKeys::Q));

	//}
	//PlayerInputComponent->BindAxis("MainPlayer_MoveForward", this, &AMainCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("MainPlayer_MoveRight", this, &AMainCharacter::MoveRight);
	////PlayerInputComponent->BindAxis("MainPlayer_MoveUp", this, &AMainCharacter::MoveUp_World);
	//PlayerInputComponent->BindAxis("MainPlayer_TurnRate", this, &AMainCharacter::TurnAtRate);

	////수정필요
	//PlayerInputComponent->BindAxis("MainPlayer_Turn", this, &AMainCharacter::AddControllerYawInput);
	////PlayerInputComponent->BindAxis("MainPlayer_FocusTurn", this, &AMainCharacter::AddControllerYawInput);

	//PlayerInputComponent->BindAxis("MainPlayer_LookUp", this, &AMainCharacter::AddControllerPitchInput);//LookUpDown
	////PlayerInputComponent->BindAxis("MainPlayer_LookUp", this, &AMainCharacter::AddControllerPitchInput);
	////PlayerInputComponent->BindAxis("MainPlayer_LookUpRate", this, &AMainCharacter::LookUpAtRate);

	//PlayerInputComponent->BindAction("PlayerAttack", EInputEvent::IE_Pressed, this, &AMainCharacter::AttackAction);
	//PlayerInputComponent->BindAction("PlayerJumpAction", EInputEvent::IE_Pressed, this, &AMainCharacter::JumpAction);
	//PlayerInputComponent->BindAction("Lock_On", EInputEvent::IE_Pressed, this, &AMainCharacter::LockOnTarget);
//}
//
//void AMainCharacter::AttackAction()
//{
//	AniState = ZEDAniState::Attack;
//}
//
//void AMainCharacter::JumpAction()
//{
//	Jump();
//
//	AniState = ZEDAniState::Jump;
//}

//void AMainCharacter::Look(const FInputActionValue& Value)
//{
//	// input is a Vector2D
//	FVector2D LookAxisVector = Value.Get<FVector2D>();
//
//	if (Controller != nullptr)
//	{
//		// add yaw and pitch input to controller
//		AddControllerYawInput(LookAxisVector.X);
//		AddControllerPitchInput(LookAxisVector.Y);
//	}
//}


//void AMainCharacter::JumpAxis(float Rate)
//{
//}

