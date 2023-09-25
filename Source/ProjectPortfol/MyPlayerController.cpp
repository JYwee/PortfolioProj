// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "MainCharacter.h"
#include "ZedGameInstance.h"
#include "Ai/NpcCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interactive/MagnetAct.h"
#include "Interactive/PortalActor.h"

#include <Interactive/LootObject.h>
#include "UI/InteracTextListWidget.h"
#include "UI/InteracObjData.h"
#include "UI/InvenAndStatus.h"
#include <UI/InGameHud.h>
#include "UI/InGameMainWidget.h"
#include "Ai/CrowdNpc.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::PostInitializeComponents()
{	
	Super::PostInitializeComponents();
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//GetCharacter()

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveForward", EKeys::S, -1.f));

		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveForward", EKeys::Gamepad_LeftY, 1.f));

		//왼쪽 오른쪽 움직임
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_MoveRight", EKeys::D, 1.f));

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
			
			
			UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_Turn", EKeys::MouseX, 1.f));

			//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_LookUpRate", EKeys::Gamepad_RightY, 1.f));
			UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_LookUp", EKeys::MouseY, -1.f));
			UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MainPlayer_Aim", EKeys::RightMouseButton, 1.f));

			//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("ShiftAction", EKeys::LeftShift));

			UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerAttack"), EKeys::LeftMouseButton));
			UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("JumpOrNextAction"), EKeys::SpaceBar));
			UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("Lock_On"), EKeys::Q));
			UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("ShiftAction"), EKeys::LeftShift));
			UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("InteractAction"), EKeys::E));
			UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("OpenInvenStatusAction"), EKeys::I));
			UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("UPInteractUI"), EKeys::T));
			UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("DOWNInteractUI"), EKeys::G));

	}
	InputComponent->BindAxis("MainPlayer_MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MainPlayer_MoveRight", this, &AMyPlayerController::MoveRight);

	InputComponent->BindAxis("MainPlayer_Aim", this, &AMyPlayerController::Aiming);

	//PlayerInputComponent->BindAxis("MainPlayer_MoveUp", this, &AMainCharacter::MoveUp_World);
	//InputComponent->BindAxis("MainPlayer_TurnRate", this, &AMyPlayerController::TurnAtRate);

	//수정필요
	//FInputAxisBinding& BindAxis(const FName AxisName, UserClass * Object, typename FInputAxisHandlerSignature::TMethodPtr< UserClass > Func);
	InputComponent->BindAxis("MainPlayer_Turn", this, &AMyPlayerController::AddYawInput);
	//PlayerInputComponent->BindAxis("MainPlayer_FocusTurn", this, &AMainCharacter::AddControllerYawInput);

	InputComponent->BindAxis("MainPlayer_LookUp", this, &AMyPlayerController::AddPitchInput);//LookUpDown

	//InputComponent->BindAxis("ShiftAction", IE_Pressed, this, &AMyPlayerController::ShiftAxis);
	//PlayerInputComponent->BindAxis("MainPlayer_LookUp", this, &AMainCharacter::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("MainPlayer_LookUpRate", this, &AMainCharacter::LookUpAtRate);

	InputComponent->BindAction("PlayerAttack", IE_Pressed, this, &AMyPlayerController::AttackAction);
	InputComponent->BindAction("JumpOrNextAction", IE_Pressed, this, &AMyPlayerController::JumpOrNextAction);
	InputComponent->BindAction("Lock_On", IE_Pressed, this, &AMyPlayerController::LockOnTarget);
	
	InputComponent->BindAction("ShiftAction", IE_Pressed, this, &AMyPlayerController::ShiftAction);
	InputComponent->BindAction("InteractAction", IE_Pressed, this, &AMyPlayerController::InteractAction);
	InputComponent->BindAction("OpenInvenStatusAction", IE_Pressed, this, &AMyPlayerController::OpenInvenStatusAction);
	InputComponent->BindAction("UPInteractUI", IE_Pressed, this, &AMyPlayerController::UpUiInteractAction);
	InputComponent->BindAction("DOWNInteractUI", IE_Pressed, this, &AMyPlayerController::DownUiInteractAction);

	

}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//GetCharacter null 뜰때 있음.

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
	if (mIsUiControlling == true)
	{
		return;
	}


	if (myCharacter->GetAniState() == ZEDAniState::Attack || myCharacter->GetAniState() == ZEDAniState::Jump) {
		return;
	}
	
	
	if (Val != 0.f)
	{
		//if (this)
		//{
			FRotator const ControlSpaceRot = this->GetControlRotation();
			const FRotator YawRotation(0, ControlSpaceRot.Yaw, 0);

			

			// transform to world space and add it
			myCharacter->AddMovementInput(FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X), Val); //ControlSpaceRot
			
			if (myCharacter->IsLockOnTarget() == true)
			{
				myCharacter->SetAniState(Val > 0.f ? ZEDAniState::ForwardMove : ZEDAniState::BackwardMove);
				myCharacter->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(myCharacter->GetActorLocation(), myCharacter->GetTargetNpcChar()->GetActorLocation()));
			}
			else
			{
				myCharacter->SetAniState(ZEDAniState::FrontRun);
				//UE_LOG(LogTemp, Log, TEXT("%S(%u) %d, %d"), __FUNCTION__, __LINE__, myCharacter->AniState , ZEDAniState::FrontRun);
			}
			return;
		//}
	}
	else {
		if (myCharacter->GetAniState() == ZEDAniState::ForwardMove || myCharacter->GetAniState() == ZEDAniState::BackwardMove || myCharacter->GetAniState() == ZEDAniState::FrontRun)//|| myCharacter->AniState == ZEDAniState::Run
		{
			myCharacter->SetAniState(ZEDAniState::Idle);
			//UE_LOG(LogTemp, Log, TEXT("%S(%u) %d"), __FUNCTION__, __LINE__, myCharacter->AniState);
		}
	}


}

void AMyPlayerController::MoveRight(float Val)
{
	if (mIsUiControlling == true)
	{
		return;
	}

	if (myCharacter->GetAniState() == ZEDAniState::Attack || myCharacter->GetAniState() == ZEDAniState::Jump) {
		return;
	}



	if (Val != 0.f)
	{
		//float axisValue = Val * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation;
		//this->AddActorWorldRotation(FRotator(0.0f, axisValue, 0.0f));

		///if (this)
	//	{
			FRotator const ControlSpaceRot = this->GetControlRotation();
			const FRotator YawRotation(0, ControlSpaceRot.Yaw, 0);

			// transform to world space and add it
			
			myCharacter->AddMovementInput(FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y), Val); //ControlSpaceRot
			if (myCharacter->IsLockOnTarget() == true)
			{
				myCharacter->SetAniState(Val > 0.f ? ZEDAniState::RightMove : ZEDAniState::LeftMove);
				myCharacter->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(myCharacter->GetActorLocation(), myCharacter->GetTargetNpcChar()->GetActorLocation()));
			}
			else
			{
				myCharacter->SetAniState(ZEDAniState::RightRun);
			}
			
			return;
//		}
	}
	else {
		if (myCharacter->GetAniState() == ZEDAniState::RightMove || myCharacter->GetAniState() == ZEDAniState::LeftMove || myCharacter->GetAniState() == ZEDAniState::RightRun)
		{
			myCharacter->SetAniState(ZEDAniState::Idle);
			//UE_LOG(LogTemp, Log, TEXT("%S(%u) %d"), __FUNCTION__, __LINE__, myCharacter->AniState);
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

void AMyPlayerController::ShiftAction()
{
	if (mIsUiControlling == true)
	{
		return;
	}

	if (myCharacter->IsLockOnTarget() == true)
	{
		FVector curFVector = myCharacter->GetCharacterMovement()->GetCurrentAcceleration();
		FVector tpFVector;
		tpFVector.X = myCharacter->GetActorLocation().X + (curFVector.X * 0.1);
		tpFVector.Y = myCharacter->GetActorLocation().Y + (curFVector.Y * 0.1);
		tpFVector.Z = myCharacter->GetActorLocation().Z + 30;   /*+ (curFVector.Z * 0.5f);*/

		UE_LOG(LogTemp, Log, TEXT("%S(%u) %f, %f, %f"), __FUNCTION__, __LINE__, tpFVector.X, tpFVector.Y, tpFVector.Z);

		myCharacter->TeleportTo(tpFVector, myCharacter->GetActorRotation(), false, false);
		//myCharacter->SetActorLocation(tpFVector);
	}
	else {
		if (mIsShift == false)
		{
		mIsShift = true;

		myCharacter->GetCharacterMovement()->MaxWalkSpeed = 1000.f;
		}
	}
}

void AMyPlayerController::LockOnTarget()
{
	if (mIsUiControlling == true)
	{
		return;
	}


	UZedGameInstance* Inst = GetGameInstance<UZedGameInstance>();

	bool isEnemyHere = false;

	if (myCharacter) {

		if (myCharacter->IsLockOnTarget() == false)
		{

			if (Inst->AllNpcCharac.Num() < 1) {
				return;
			}




			for (int i = 0; i < Inst->AllNpcCharac.Num(); ++i)
			{
				//UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation());



				if (myCharacter->GetDistanceTo(Inst->AllNpcCharac[i]) < 1500.f)
				{
					
					//Inst->TimerManager->TimerExists();

					float recentTime = UGameplayStatics::GetRealTimeSeconds(GetLevel()) - Inst->AllNpcCharac[i]->GetLastRenderTime();
					if(Visibility_GetRenderedActors(Inst->AllNpcCharac[i], recentTime) != nullptr)
					{
						//UE_LOG(LogTemp, Warning, TEXT("%S(%u) %f, %f"), __FUNCTION__, __LINE__, npcCharacter->GetLastRenderTime(), MinRecentTime);
					myCharacter->SetIsLockOn(true);
					myCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
					//SetLockOnTargetNpc(Inst->AllNpcCharac[i]);
					isEnemyHere = true;
					myCharacter->bUseControllerRotationYaw = true;
					myCharacter->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(myCharacter->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation()));
					SetControlRotation(UKismetMathLibrary::FindLookAtRotation(myCharacter->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation()));
					myCharacter->mTargetNpcCharacter = Inst->AllNpcCharac[i];
					Inst->AllNpcCharac[i]->mLockOnSphere->SetVisibility(true);
					Inst->AllNpcCharac[i]->mLockOnWidgetComp->SetVisibility(true);
					//mWdgLockOn->SetVisibility(ESlateVisibility::Visible);    //적 hp창 ui 보이게
					myCharacter->bUseControllerRotationYaw = false;
					}
				}

			}
			if (isEnemyHere == false) {
				return;
			}
		}
		else
		{
			
			myCharacter->SetIsLockOn(false);

			for (int i = 0; i < Inst->AllNpcCharac.Num(); ++i)
			{
				Inst->AllNpcCharac[i]->mLockOnSphere->SetVisibility(false);
				Inst->AllNpcCharac[i]->mLockOnWidgetComp->SetVisibility(false);
				//SetLockOnTargetNpc(nullptr);
				myCharacter->mTargetNpcCharacter = nullptr;
				//mWdgLockOn->SetVisibility(ESlateVisibility::Hidden);    //적 hp창 ui 보이게
			}
			myCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
			
		}
	}


	
	//UZedGameInstance* Inst = GetGameInstance<UZedGameInstance>();
	//
	//if (myCharacter) {

	//	for (int i = 0; i < Inst->AllNpcCharac.Num(); ++i)
	//	{
	//		UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation());
	//		


	//		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation()));
	//		
	//		/*SetControlRotation(UKismetMathLibrary::FindLookAtRotation(myCharacter->GetActorLocation(), Inst->AllNpcCharac[i]->GetActorLocation()));
	//		myCharacter->mTargetNpcCharacter = Inst->AllNpcCharac[i];
	//		Inst->AllNpcCharac[i]->mLockOnSphere->SetVisibility(true);*/

	//		myCharacter->bUseControllerRotationRoll = false; // not work
	//		myCharacter->bUseControllerRotationPitch = false;
	//		myCharacter->bUseControllerRotationYaw = false;

	//		bUseControllerRotationYaw = false;
	//		mSpringArmComp->AddLocalRotation(this->GetActorRotation());
	//		mSpringArmComp->AddLocalRotation(this->GetControlRotation());
	//	}

	//	myCharacter->LockOnTarget();
	//	
	//}
	
}

void AMyPlayerController::InteractAction()
{
	AInGameHud* myHud = GetHUD<AInGameHud>();

	UInteracTextListWidget* listWdg = Cast<UInteracTextListWidget>(myHud->GetMainWidget()->GetWidgetFromName(TEXT("UI_IntractiveText")));

	UInteracObjData* focusedSlotObjData = Cast<UInteracObjData>(listWdg->GetNowFocusSlotObj());
	
	if (focusedSlotObjData == nullptr)
	{
		return;
	}
		
		if (focusedSlotObjData->mOnwerActor->Tags.Contains(TEXT("MagnetOBJ")))
		{
			AMagnetAct* magnetAct = Cast<AMagnetAct>(focusedSlotObjData->mOnwerActor);
			magnetAct->SetIsGotoPast(true);
			//magnetAct->MovePast();
			//UE_LOG(LogTemp, Error, TEXT("%S(%u) %S"), __FUNCTION__, __LINE__, myCharacter->GetNearInteractObj()[i]->StaticConfigName());
		}
		else if (focusedSlotObjData->mOnwerActor->Tags.Contains(TEXT("TeleportGate")))
		{
			APortalActor* portalAct = Cast<APortalActor>(focusedSlotObjData->mOnwerActor);
			portalAct->PlayerTeleport();
			//magnetAct->MovePast();

			//UE_LOG(LogTemp, Error, TEXT("%S(%u) %S"), __FUNCTION__, __LINE__, myCharacter->GetNearInteractObj()[i]->StaticConfigName());
		}
		else if (focusedSlotObjData->mOnwerActor->Tags.Contains(TEXT("LootObj")))
		{
			ALootObject* lootObj = Cast<ALootObject>(focusedSlotObjData->mOnwerActor);
			lootObj->TestDropItem();
		}
		else if (focusedSlotObjData->mOnwerActor->Tags.Contains(TEXT("DropItem")))
		{
			ADropItem* dropItem = Cast<ADropItem>(focusedSlotObjData->mOnwerActor);

			if (myCharacter->AddInventoryItem(dropItem->mItemData, dropItem->mCount) == true)
			{
				dropItem->Destroy();
			};

		}
		else if (focusedSlotObjData->mOnwerActor->Tags.Contains(TEXT("InteracNPC")))
		{
			ACrowdNpc* crowdNpcCharacter = Cast<ACrowdNpc>(focusedSlotObjData->mOnwerActor);

			mIsUiControlling = true;

			if (crowdNpcCharacter->GetInteractDialogues().Num() > 0)
			{
				myHud->GetMainWidget()->SetTalkTextWindowOnOff(ESlateVisibility::Hidden);
				myHud->GetMainWidget()->GetUIMainTextBox()->mArrMainText = crowdNpcCharacter->GetInteractDialogues();
				myHud->GetMainWidget()->GetUIMainTextBox()->indexMainText = 0;
				myHud->GetMainWidget()->GetUIMainTextBox()->mMainText =
					crowdNpcCharacter->GetInteractDialogues()[0];
				myHud->GetMainWidget()->GetUIMainTextBox()->mMainTextName = crowdNpcCharacter->GetNpcName();
				myHud->GetMainWidget()->SetMainTextWindowOnOff(ESlateVisibility::Visible);
				
			}


				//crowdNpcCharacter->GetInteractDialogues();

			/*ADropItem* dropItem = Cast<ADropItem>(focusedSlotObjData->mOnwerActor);

			myCharacter->AddInventoryItem(dropItem->mItemData);*/
		}

	
	//기존의 예전 테스트 코드 //캐릭터 근처의 오브잭트 전부를 훑음.
	// 
	//for (int i = 0; i < myCharacter->GetNearInteractObj().Num(); ++i)
	//{

	//	if (myCharacter->GetNearInteractObj()[i]->Tags.Contains(TEXT("MagnetOBJ")))
	//	{
	//		AMagnetAct* magnetAct = Cast<AMagnetAct>(myCharacter->GetNearInteractObj()[i]);
	//		magnetAct->SetIsGotoPast(true);
	//		//magnetAct->MovePast();
	//		UE_LOG(LogTemp, Error, TEXT("%S(%u) %S"), __FUNCTION__, __LINE__, myCharacter->GetNearInteractObj()[i]->StaticConfigName());
	//	}
	//	else if (myCharacter->GetNearInteractObj()[i]->Tags.Contains(TEXT("TeleportGate")))
	//	{
	//		APortalActor* portalAct = Cast<APortalActor>(myCharacter->GetNearInteractObj()[i]);
	//		portalAct->PlayerTeleport();
	//		//magnetAct->MovePast();

	//		//UE_LOG(LogTemp, Error, TEXT("%S(%u) %S"), __FUNCTION__, __LINE__, myCharacter->GetNearInteractObj()[i]->StaticConfigName());
	//	}
	//	else if (myCharacter->GetNearInteractObj()[i]->Tags.Contains(TEXT("LootObj")))
	//	{
	//		ALootObject* lootObj = Cast<ALootObject>(myCharacter->GetNearInteractObj()[i]);
	//		lootObj->TestDropItem();
	//	}
	//	else if (myCharacter->GetNearInteractObj()[i]->Tags.Contains(TEXT("DropItem")))
	//	{
	//		ADropItem* dropItem = Cast<ADropItem>(myCharacter->GetNearInteractObj()[i]);
	//		//myCharacter->GetInventoryData().Add(dropItem)
	//	}

	//	//UE_LOG(LogTemp, Error, TEXT("%S(%u) %S"), __FUNCTION__, __LINE__, mNearInteractObj[i]->StaticConfigName());


	//	//UE_LOG mNearInteractObj[i];
	//}


	//myCharacter->InteractAction();
}
//ui 위로 한칸
void AMyPlayerController::UpUiInteractAction()
{
	AInGameHud* myHud = GetHUD<AInGameHud>();
	
	UInteracTextListWidget* listWdg = Cast<UInteracTextListWidget>(myHud->GetMainWidget()->GetWidgetFromName(TEXT("UI_IntractiveText")));

	if (listWdg->GetUpFocusSlotObj() == nullptr)
	{
		
	}
}

//ui 아래로 한칸
void AMyPlayerController::DownUiInteractAction()
{
	AInGameHud* myHud = GetHUD<AInGameHud>();

	UInteracTextListWidget* listWdg = Cast<UInteracTextListWidget>(myHud->GetMainWidget()->GetWidgetFromName(TEXT("UI_IntractiveText")));

	if (listWdg->GetDownFocusSlotObj() == nullptr)
	{

	}
}

void AMyPlayerController::OpenInvenStatusAction()
{
	if (mIsUiControlling == true)
	{
		return;
	}

	if (GetHUD() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) GetHud failed"), __FUNCTION__, __LINE__);
		return;
	}

	AInGameHud* ingameHUD = Cast<AInGameHud>(GetHUD());
	
	if(ingameHUD->GetMainWidget()->mInvenStatusWindowOnOff == ESlateVisibility::Visible)
	{
		ingameHUD->GetMainWidget()->mInvenStatusWindowOnOff = ESlateVisibility::Hidden;
		return;
	}
	//	ingameHUD->GetMainWidget().

	UInvenAndStatus* invenAndStatusWdg = Cast<UInvenAndStatus>(ingameHUD->GetMainWidget()->GetWidgetFromName(TEXT("UI_InventoryStatus")));
	UTileView* invenTilelist = invenAndStatusWdg->GetInvenList();

	TArray<UObject*> invenUIitems = invenTilelist->GetListItems();
	TArray<UInventoryItemData*> invenCharacterItems = myCharacter->GetInventoryData();
	
	for (int i = 0; i < invenCharacterItems.Num(); ++i)
	{	
		UInventoryItemData* tmpItemData = Cast<UInventoryItemData>(invenUIitems[i]);
		if (tmpItemData == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u) Item Casting failed"), __FUNCTION__, __LINE__)
		}
		else
		{
			tmpItemData = invenCharacterItems[i];
			ingameHUD->GetMainWidget()->mInvenStatusWindowOnOff = ESlateVisibility::Visible;
			/*tmpItemData->mWidget = invenCharacterItems[i]->mWidget;
			tmpItemData->mData = invenCharacterItems[i]->mData;
			tmpItemData->mCount = invenCharacterItems[i]->mCount;*/
		}
		
	}
	//UInventoryItemData

	//invenTilelist.
	//invenTilelist
	//myCharacter->GetInventoryData();
	//mInventoryData
}

void AMyPlayerController::Aiming(float Rate)
{
	if (mIsUiControlling == true)
	{
		return;
	}

	if (Rate != 0.0f) {

		if (myCharacter->IsAimingNow() == false)
		{
			myCharacter->SetIsAimingNow(true);
			if (GetHUD() == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("%S(%u) GetHud failed"), __FUNCTION__, __LINE__);
				return;
			}
			AInGameHud* ingameHUD = Cast<AInGameHud>(GetHUD());
			ingameHUD->GetMainWidget()->SetCrossHairOnOffOnOff(ESlateVisibility::Visible);

			myCharacter->AimingAction();
		}
	}
	else
	{
		if (myCharacter->IsAimingNow() == true)
		{
			myCharacter->SetIsAimingNow(false);
			AInGameHud* ingameHUD = Cast<AInGameHud>(GetHUD());
			ingameHUD->GetMainWidget()->SetCrossHairOnOffOnOff(ESlateVisibility::Hidden);

			myCharacter->AimingAction();
		}
	}
	
	//aiming right mouse btn
}

ANpcCharacter* AMyPlayerController::Visibility_GetRenderedActors(ANpcCharacter* npcCharacter, float MinRecentTime)
{
	
	UE_LOG(LogTemp, Error, TEXT("%S(%u) %f, %f"), __FUNCTION__, __LINE__, npcCharacter->GetLastRenderTime(), MinRecentTime);
	if (0.5f < MinRecentTime)
	{

		return nullptr;
	}
	return npcCharacter;
}

void AMyPlayerController::AttackAction()
{
	if (mIsUiControlling == true)
	{
		return;
	}

	//UZedGameInstance* Inst = GetWorld()->GetGameInstance<UZedGameInstance>();

	
	if (myCharacter->IsAimingNow() == false) {
		myCharacter->SetAniState(ZEDAniState::Attack);
	}
	else
	{
		myCharacter->SetAniState(ZEDAniState::SimpleMagicCasting);
	}
}

void AMyPlayerController::JumpOrNextAction()
{
	if (mIsUiControlling == false)
	{
		myCharacter->Jump();

		myCharacter->SetAniState(ZEDAniState::Jump);
		
		return;
	}

	AInGameHud* myHud = GetHUD<AInGameHud>();

	UInteracTextListWidget* listWdg = Cast<UInteracTextListWidget>(myHud->GetMainWidget()->GetWidgetFromName(TEXT("UI_IntractiveText")));

	UInteracObjData* focusedSlotObjData = Cast<UInteracObjData>(listWdg->GetNowFocusSlotObj());

	TArray<FText> arrTextDilog = myHud->GetMainWidget()->GetUIMainTextBox()->mArrMainText;

	int indexText = myHud->GetMainWidget()->GetUIMainTextBox()->indexMainText;

	if (indexText < arrTextDilog.Num() - 1)
	{
		++indexText;
		myHud->GetMainWidget()->GetUIMainTextBox()->indexMainText = indexText;

		myHud->GetMainWidget()->GetUIMainTextBox()->mMainText = arrTextDilog[indexText];
	}
	else
	{
		myHud->GetMainWidget()->SetMainTextWindowOnOff(ESlateVisibility::Hidden);
		mIsUiControlling = false;
		myHud->GetMainWidget()->GetUIMainTextBox()->indexMainText = 0;
		myHud->GetMainWidget()->SetTalkTextWindowOnOff(ESlateVisibility::Visible);
	}
	//arrTextDilog
	//myHud->GetMainWidget()->GetUIMainTextBox()->indexMainText
}