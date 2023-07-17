// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

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
	//InputComponent->BindAxis("MainPlayer_MoveForward", this, &AMyPlayerController::MoveForward);
	//InputComponent->BindAxis("MainPlayer_MoveRight", this, &AMyPlayerController::MoveRight);
	////PlayerInputComponent->BindAxis("MainPlayer_MoveUp", this, &AMainCharacter::MoveUp_World);
	//InputComponent->BindAxis("MainPlayer_TurnRate", this, &AMyPlayerController::TurnAtRate);

	////수정필요
	//InputComponent->BindAxis("MainPlayer_Turn", this, &AMyPlayerController::AddControllerYawInput);
	////PlayerInputComponent->BindAxis("MainPlayer_FocusTurn", this, &AMainCharacter::AddControllerYawInput);

	//InputComponent->BindAxis("MainPlayer_LookUp", this, &AMyPlayerController::AddControllerPitchInput);//LookUpDown
	////PlayerInputComponent->BindAxis("MainPlayer_LookUp", this, &AMainCharacter::AddControllerPitchInput);
	////PlayerInputComponent->BindAxis("MainPlayer_LookUpRate", this, &AMainCharacter::LookUpAtRate);

	//InputComponent->BindAction("PlayerAttack", EInputEvent::IE_Pressed, this, &AMyPlayerController::AttackAction);
	//InputComponent->BindAction("PlayerJumpAction", EInputEvent::IE_Pressed, this, &AMyPlayerController::JumpAction);
	//InputComponent->BindAction("Lock_On", EInputEvent::IE_Pressed, this, &AMyPlayerController::LockOnTarget);
}
