// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "MainCharacter.h"
#include "ZedGameInstance.h"
#include "Kismet/KismetMathLibrary.h"


void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//GetCharacter()

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;
		
		FInputAxisKeyMapping("MainPlayer_MoveForward", EKeys::W, 1.f);
		FInputAxisKeyMapping("MainPlayer_MoveForward", EKeys::S, -1.f);

		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveForward", EKeys::Gamepad_LeftY, 1.f));

		//왼쪽 오른쪽 움직임
		FInputAxisKeyMapping("MainPlayer_MoveRight", EKeys::A, -1.f);
		FInputAxisKeyMapping("MainPlayer_MoveRight", EKeys::D, 1.f);

		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_TurnRate", EKeys::A, -1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_TurnRate", EKeys::D, 1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_Turn", EKeys::A, -1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_Turn", EKeys::D, 1.f));


		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveRight", EKeys::Gamepad_LeftX, 1.f));

		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveUp", EKeys::Gamepad_LeftThumbstick, 1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveUp", EKeys::Gamepad_RightThumbstick, -1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveUp", EKeys::Gamepad_FaceButton_Bottom, 1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveUp", EKeys::LeftControl, -1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveUp", EKeys::SpaceBar, 1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::C, -1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::E, 1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("DefaultPawn_MoveUp", EKeys::Q, -1.f));

		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_TurnRate", EKeys::Gamepad_RightX, 1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_TurnRate", EKeys::Left, -1.f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_TurnRate", EKeys::Right, 1.f));


		FInputAxisKeyMapping("MainPlayer_Turn", EKeys::MouseX, 1.f);

		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_LookUpRate", EKeys::Gamepad_RightY, 1.f));
		FInputAxisKeyMapping("MainPlayer_LookUp", EKeys::MouseY, -1.f);

		FInputActionKeyMapping(TEXT("PlayerAttack"), EKeys::LeftMouseButton);
		FInputActionKeyMapping(TEXT("PlayerJumpAction"), EKeys::SpaceBar);
		FInputActionKeyMapping(TEXT("Lock_On"), EKeys::Q);

	}
	InputComponent->BindAxis("MainPlayer_MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MainPlayer_MoveRight", this, &AMyPlayerController::MoveRight);
	//PlayerInputComponent->BindAxis("MainPlayer_MoveUp", this, &AMainCharacter::MoveUp_World);
	InputComponent->BindAxis("MainPlayer_TurnRate", this, &AMyPlayerController::TurnAtRate);

	//수정필요
	//FInputAxisBinding& BindAxis(const FName AxisName, UserClass * Object, typename FInputAxisHandlerSignature::TMethodPtr< UserClass > Func);
	InputComponent->BindAxis("MainPlayer_Turn", this, &AMyPlayerController::AddYawInput);
	//PlayerInputComponent->BindAxis("MainPlayer_FocusTurn", this, &AMainCharacter::AddControllerYawInput);

	InputComponent->BindAxis("MainPlayer_LookUp", this, &AMyPlayerController::AddPitchInput);//LookUpDown
	//PlayerInputComponent->BindAxis("MainPlayer_LookUp", this, &AMainCharacter::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("MainPlayer_LookUpRate", this, &AMainCharacter::LookUpAtRate);

	InputComponent->BindAction("PlayerAttack", EInputEvent::IE_Pressed, this, &AMyPlayerController::AttackAction);
	InputComponent->BindAction("PlayerJumpAction", EInputEvent::IE_Pressed, this, &AMyPlayerController::JumpAction);
	InputComponent->BindAction("Lock_On", EInputEvent::IE_Pressed, this, &AMyPlayerController::LockOnTarget);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	myCharacter = Cast<AMainCharacter>(GetCharacter());

	ACharacter* const myCharacter2 = GetCharacter();

	if (myCharacter == nullptr || myCharacter->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) myCharacter == nullptr Inst->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}
}


void AMyPlayerController::MoveForward(float Val)
{
	if (myCharacter->AniState == ZEDAniState::Attack || myCharacter->AniState == ZEDAniState::Jump) {
		return;
	}
	
	
	if (Val != 0.f)
	{
		if (this)
		{
			FRotator const ControlSpaceRot = this->GetControlRotation();
			const FRotator YawRotation(0, ControlSpaceRot.Yaw, 0);

			// transform to world space and add it
			myCharacter->AddMovementInput(FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X), Val); //ControlSpaceRot

			myCharacter->AniState = Val > 0.f ? ZEDAniState::ForwardMove : ZEDAniState::BackwardMove;
			return;
		}
	}
	else {
		if (myCharacter->AniState == ZEDAniState::ForwardMove || myCharacter->AniState == ZEDAniState::BackwardMove)
		{
			myCharacter->AniState = ZEDAniState::Idle;
		}
	}


}

void AMyPlayerController::MoveRight(float Val)
{
	if (myCharacter->AniState == ZEDAniState::Attack || myCharacter->AniState == ZEDAniState::Jump) {
		return;
	}



	if (Val != 0.f)
	{
		//float axisValue = Val * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation;
		//this->AddActorWorldRotation(FRotator(0.0f, axisValue, 0.0f));

		if (this)
		{
			FRotator const ControlSpaceRot = this->GetControlRotation();
			const FRotator YawRotation(0, ControlSpaceRot.Yaw, 0);

			// transform to world space and add it
			
			myCharacter->AddMovementInput(FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y), Val); //ControlSpaceRot

			myCharacter->AniState = Val > 0.f ? ZEDAniState::RightMove : ZEDAniState::LeftMove;
			return;
		}
	}
	else {
		if (myCharacter->AniState == ZEDAniState::RightMove || myCharacter->AniState == ZEDAniState::LeftMove)
		{
			myCharacter->AniState = ZEDAniState::Idle;
		}
	}
}

void AMyPlayerController::MoveUp_World(float Val)
{
	if (Val != 0.f)
	{
		myCharacter->AddMovementInput(FVector::UpVector, Val);
	}
}

void AMyPlayerController::TurnAtRate(float Rate)
{
	AddYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void AMyPlayerController::LookUpAtRate(float Rate)
{
	//AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
	AddPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void AMyPlayerController::FocusTurn(float Rate)
{

	//float axisValue = Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation;
	//mFollowCamera->AddLocalRotation(FRotator(0.0f, axisValue, 0.0f));

	//AddActorLocalRotation();
	//AddControllerPitchInput();
}

void AMyPlayerController::LockOnTarget()
{
	
	if (myCharacter) {
		myCharacter->LockOnTarget();
	}
	
}

void AMyPlayerController::AttackAction()
{
	myCharacter->AniState = ZEDAniState::Attack;
}

void AMyPlayerController::JumpAction()
{
	myCharacter->Jump();

	myCharacter->AniState = ZEDAniState::Jump;
}