// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "ZedGameInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Ai/NpcCharacter.h"
#include "UI/InteracTextListWidget.h"
#include "UI/InGameHud.h"

#include "Interactive/InterObjStaticMeshAct.h"
#include "Data/ObjDataTable.h"
#include "UI/InteracTextSlot.h"
#include "UI/InvenAndStatus.h"

#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "InGameMode.h"
//#include "Math/Vector.h"
#include "GameFramework/SpringArmComponent.h"

AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mAniState = ZEDAniState::Idle;
	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;
	//
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	mSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractSphereComp"));
	mSphereComponent->SetupAttachment(RootComponent);
	mSphereComponent->SetSphereRadius(300.f, true);
	mSphereComponent->ComponentTags.Add(TEXT("Interact_PlayerComp"));
	
	//캐릭터 이동 모션 관련
	GetCharacterMovement()->bOrientRotationToMovement = false;

	mSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	mSpringArmComp->SetupAttachment(RootComponent);
	mSpringArmComp->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
	mSpringArmComp->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	mFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	mFollowCamera->SetupAttachment(mSpringArmComp, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	mFollowCamera->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	mFollowCamera->SetRelativeRotation(FRotator(-10.f, 0, 0));

	mFollowCamera->bUsePawnControlRotation = false;

	//mFollowCamera->ComponentTags.Add
	GetCapsuleComponent()->ComponentTags.Add(TEXT("PlayerCapsuleComp"));

	
	mParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BlinkParticleComp"));
	mParticleSystemComp->SetupAttachment(GetMesh());

	mIsLockOn = false;
	
	//addTag
	Tags.Add(TEXT("Player"));
	

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

void AMainCharacter::BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherComp->ComponentHasTag(TEXT("Interactive")))
	{
		APlayerController* HUDController = Cast<APlayerController>(GetController());
		AInGameHud* myHud = HUDController->GetHUD<AInGameHud>();
		
		//UUserWidget* Window;

		UInteracTextListWidget* listWdg = Cast<UInteracTextListWidget>(myHud->GetMainWidget()->GetWidgetFromName(TEXT("UI_IntractiveText")));
		UInteracTextSlot* tmp = Cast<UInteracTextSlot>(listWdg->GetWidgetFromName(TEXT("UI_InteracTextSlot")));

		UZedGameInstance* gameInst = GetWorld()->GetGameInstance<UZedGameInstance>();
		if (gameInst == nullptr || gameInst->IsValidLowLevel() == false)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u) Find failed"), __FUNCTION__, __LINE__);
			return;
		}



		AInterObjStaticMeshAct* objMeshAct = Cast<AInterObjStaticMeshAct>(OtherActor);
		if(objMeshAct == nullptr || objMeshAct->IsValidLowLevel() == false)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u) Find failed"), __FUNCTION__, __LINE__);
				return;
		}
		
		for (int i = 0; i < OtherComp->ComponentTags.Num(); ++i)
		{
			if (TEXT("TeleportGate") == OtherComp->ComponentTags[i])
			{
				UInteracObjData* Data = NewObject<UInteracObjData>();
				Data->mObjData = gameInst->GetObjInteractData("TeleportGate");
				Data->mOnwerActor = OtherActor;

				listWdg->GetInteractListView()->AddItem(Data);
				
				//listWdg->AddInteracTextSlot(Data, )
				//AddInteracTextSlot
				//Cast<InteracTextSlot>listWdg->GetInteractListView()->GetListItems();
				//UInteracTextSlot* tmp2 = Cast<UInteracTextSlot>(listWdg->GetWidgetFromName(TEXT("UI_InteracTextSlot")));
				//UListView* xxx = listWdg->GetInteractListView();
				/*
				UUserWidget* txx = listWdg->GetInteractListView()->GetEntryWidgetFromItem(Data);
				TSubclassOf<UUserWidget> ttp = listWdg->GetInteractListView()->GetEntryWidgetClass();
				UInteracTextSlot* tmp1 = Cast<UInteracTextSlot>(ttp.Get());
				UInteracTextSlot* tmp3 = Cast<UInteracTextSlot>(ttp);
				UInteracTextSlot* tmp2 = Cast<UInteracTextSlot>(ttp.GetDefaultObject());
				TArray<UUserWidget*> asdf = listWdg->GetInteractListView()->GetDisplayedEntryWidgets();
				tmp2->mArrowFocusVisibility = ESlateVisibility::Visible;
				const TArray<UObject*> ttt = listWdg->GetInteractListView()->GetListItems();*/



				AActor* addedObj = Cast<AActor>(OtherActor);
				mNearInteractObj.Add(addedObj);
			}
			else if (TEXT("MagnetOBJ") == OtherComp->ComponentTags[i])
			{
				AActor* addedObj = Cast<AActor>(OtherActor);
				mNearInteractObj.Add(addedObj);
				UInteracObjData* Data = NewObject<UInteracObjData>();
				Data->mObjData = gameInst->GetObjInteractData("MagnetOBJ");
				Data->mOnwerActor = OtherActor;
				listWdg->GetInteractListView()->AddItem(Data);
			}
			else if (TEXT("LootObj") == OtherComp->ComponentTags[i])
			{
				AActor* addedObj = Cast<AActor>(OtherActor);
				mNearInteractObj.Add(addedObj);
				UInteracObjData* Data = NewObject<UInteracObjData>();
				Data->mObjData = gameInst->GetObjInteractData("LootObj");
				Data->mOnwerActor = OtherActor;
				listWdg->GetInteractListView()->AddItem(Data);
			}

			else if (TEXT("DropItem") == OtherComp->ComponentTags[i])
			{
				AActor* addedObj = Cast<AActor>(OtherActor);
				mNearInteractObj.Add(addedObj);
				UInteracObjData* Data = NewObject<UInteracObjData>();
				Data->mObjData = gameInst->GetObjInteractData("DropItem");
				Data->mOnwerActor = OtherActor;
				listWdg->GetInteractListView()->AddItem(Data);
			}
		}

		

		/*TArray<UUserWidget*> asdfff = listWdg->GetInteractListView()->GetDisplayedEntryWidgets();
		if(asdfff.Num() != 0)
		{
		UInteracTextSlot* tmp2 = Cast<UInteracTextSlot>(asdfff[0]);
		tmp2->mArrowFocusVisibility = ESlateVisibility::Visible;
		}*/
		//UInteracTextSlot
		//objMeshAct.
		//FObjDataTable* objData = gameInst->GetObjInteractData(TEXT("TeleportGate"));
		////UObject tmpObj = 
		//UInteracTextSlot::CreateWidgetInstance(listWdg, <UInteracTextSlot>, TEXT("UI_InteracTextSlot"));
		//listWdg->AddInteracTextSlot(Cast<UObject>(objMeshAct), UInteracTextSlot::CreateWidgetInstance(listWdg, ));
		//FObjDataTable* mObjData = gameInst->GetObjInteractData(TEXT("TeleportGate"));


		//listWdg->AddInteracTextSlot(mObjData, )
		//listWdg.

		//AddInteracTextSlot(UObject* objData, UUserWidget* widgetData)
	}



}

void AMainCharacter::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->ComponentHasTag(TEXT("Interactive")))
	{
		APlayerController* HUDController = Cast<APlayerController>(GetController());
		AInGameHud* myHud = HUDController->GetHUD<AInGameHud>();

		//UUserWidget* Window;

		UInteracTextListWidget* listWdg = Cast<UInteracTextListWidget>(myHud->GetMainWidget()->GetWidgetFromName(TEXT("UI_IntractiveText")));
		UInteracTextSlot* tmp = Cast<UInteracTextSlot>(listWdg->GetWidgetFromName(TEXT("UI_InteracTextSlot")));

		UZedGameInstance* gameInst = GetWorld()->GetGameInstance<UZedGameInstance>();
		if (gameInst == nullptr || gameInst->IsValidLowLevel() == false)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u) Find failed"), __FUNCTION__, __LINE__);
			return;
		}

		AInterObjStaticMeshAct* objMeshAct = Cast<AInterObjStaticMeshAct>(OtherActor);
		if (objMeshAct == nullptr || objMeshAct->IsValidLowLevel() == false)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u) Find failed"), __FUNCTION__, __LINE__);
			return;
		}

		/*UInteracObjData* Data = NewObject<UInteracObjData>();
		Data->mObjData = gameInst->GetObjInteractData("TeleportGate");*/
		
		UListView* tmp2 = listWdg->GetInteractListView()/*->RemoveItem()*/;
		TArray<UObject*> listItems = tmp2->GetListItems();
		for (int i = 0; i < listItems.Num(); ++i)
		{

			UInteracObjData* tmpData = Cast<UInteracObjData>(listItems[i]);

			//if( tmpData == 
			if (tmpData != nullptr || tmpData->IsValidLowLevel() == true)
			{
				UE_LOG(LogTemp, Error, TEXT("%S(%u) tmpData != nullptr "), __FUNCTION__, __LINE__);
				
				if (OtherActor == tmpData->mOnwerActor)
				{
					if (tmpData == listWdg->GetNowFocusSlotObj()){

						UObject* moveFocus = listWdg->GetUpFocusSlotObj();
						
						if (moveFocus == nullptr)
						{
							listWdg->SetNowFocusSlotObj(nullptr);
						}
						else if (moveFocus == tmpData)
						{
								moveFocus = listWdg->GetDownFocusSlotObj();
								if (moveFocus == nullptr) {
									listWdg->SetNowFocusSlotObj(nullptr);
								//tmpData->mWidget->mArrowFocusVisibility = ESlateVisibility::Hidden;
								//else if (moveFocus == tmpData) {
								//	//tmpData->mWidget->mArrowFocusVisibility = ESlateVisibility::Hidden;
								//	}
								}

							
						}
					}
					
					tmp2->RemoveItem(tmpData);

					AActor* removeObj = Cast<AActor>(OtherActor);
					if (mNearInteractObj.Contains(removeObj))
					{
						mNearInteractObj.Remove(removeObj);
					}
					
				}
			}
		}

		


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

	myController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());

	if (myController == nullptr || myController->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) myController == nullptr || myController->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}

	//AInGameMode* myGameMode = Cast<AInGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	AInGameMode* myGameMode = Cast<AInGameMode>(GetWorld()->GetAuthGameMode());
	if (myGameMode == nullptr || myGameMode->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  myGameMode->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}
	myGameMode->SetMainCharacter(this);

	if (mInventoryData.Num() == 0)
	{
		APlayerController* HUDController = Cast<APlayerController>(GetController());
		AInGameHud* myHud = HUDController->GetHUD<AInGameHud>();
		UInvenAndStatus* InventoryWdg = Cast<UInvenAndStatus>(myHud->GetMainWidget()->GetWidgetFromName(TEXT("UI_InventoryStatus")));

		for (int i = 0; i < 25; ++i)
		{
			UInventoryItemData* Data = NewObject<UInventoryItemData>();
			//Data->mData = gameInst->GetObjInteractData("TeleportGate");
			Data->mData = nullptr;
			mInventoryData.Add(Data);
			InventoryWdg->GetInvenList()->AddItem(Data);
			//mInventoryData[i] = Cast<UInventoryItemData>(InventoryWdg->GetInvenList()->GetListItems()[i]);


		

	}

		/*const TArray<UObject*>& Items = InvenList->GetListItems();
		for (size_t i = 0; i < 3; i++)
		{
			UInvenItemData* DataObject = Cast<UInvenItemData>(Items[i]);
			DataObject->Data = GameInstance->GetRandomItemData();
		}*/
	}



	//for interativeObj
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::BeginOverLap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::EndOverlap);

	//mSphereComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::BeginOverLap);
	//mSphereComponent()->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::EndOverlap);


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
		
		//UE_LOG(LogTemp, Error, TEXT("%S(%u) %f "), __FUNCTION__, __LINE__, GetCharacterMovement()->MaxWalkSpeed);
		
		if (myController->GetIsShift() == true) {
			myController->SetIsShift(false);
		}
	}

	if (GetDistanceTo(mTargetNpcCharacter) > 2000.f)
	{
		SetIsLockOn(false);

		mTargetNpcCharacter->mLockOnSphere->SetVisibility(false);
		mTargetNpcCharacter->mLockOnWidgetComp->SetVisibility(false);
			//SetLockOnTargetNpc(nullptr);
			mTargetNpcCharacter = nullptr;
			myController->mWdgLockOn->SetVisibility(ESlateVisibility::Hidden);    //적 hp창 ui 보이게
		
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	
}

void AMainCharacter::AimingAction()
{
	if (mIsAimingNow == true)
	{
		mSpringArmComp->TargetArmLength = 100;
		//set 말고 add 로 바꿀것 나중에
		//mSpringArmComp.addlo
		//mSpringArmComp->SetRelativeLocation(FVector(0.f, 45.f, 0.f));
		mFollowCamera->SetRelativeLocation(FVector(0.f, 45.f, 100.f));
		mFollowCamera->SetRelativeRotation(FRotator(0, 0, 0));
		bUseControllerRotationYaw = true;
		//mFollowCamera.
	}
	else {
		mSpringArmComp->TargetArmLength = 500;
		////set 말고 add 로 바꿀것 나중에
		////mSpringArmComp.addlo
		////mSpringArmComp->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		mFollowCamera->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
		mFollowCamera->SetRelativeRotation(FRotator(-10.f, 0, 0));
		//UE_LOG(LogTemp, Error, TEXT("%S(%u) %f %f %f "), __FUNCTION__, __LINE__, mSpringArmComp->GetRelativeLocation().X, mSpringArmComp->GetRelativeLocation().Y, mSpringArmComp->GetRelativeLocation().Z);
		bUseControllerRotationYaw = false;
		UE_LOG(LogTemp, Error, TEXT("%S(%u) %f %f %f "), __FUNCTION__, __LINE__, mSpringArmComp->GetRelativeLocation().X, mSpringArmComp->GetRelativeLocation().Y, mSpringArmComp->GetRelativeLocation().Z);
		UE_LOG(LogTemp, Error, TEXT("%S(%u) %f %f %f "), __FUNCTION__, __LINE__, mFollowCamera->GetRelativeLocation().X, mFollowCamera->GetRelativeLocation().Y, mFollowCamera->GetRelativeLocation().Z);
	}
}

void AMainCharacter::InteractAction()
{
	

	
}

FRotator AMainCharacter::GetFollowCameraRotator() const
{
	return mFollowCamera->GetComponentRotation();
}


bool AMainCharacter::AddInventoryItem(const struct FItemDataTable* itemData)
{
	if (itemData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) itemData == nullptr"), __FUNCTION__, __LINE__);
		return false;
	}

	if (itemData->StackSize == 1)
	{
		for (int i = 0; i < mInventoryData.Num(); ++i)
		{
			if (mInventoryData[i]->mData == nullptr)
			{
				mInventoryData[i]->mData = itemData;
				mInventoryData[i]->mCount=1;
				

				return true;
			}
		}
	}
	else
	{
		int firstFindIndex = FindIndexItemInInv(itemData, 0);
		if (firstFindIndex < 0)
		{
			for (int i = 0; i < mInventoryData.Num(); ++i)
			{
				if (mInventoryData[i]->mData == nullptr)
				{
					mInventoryData[i]->mData = itemData;
					return true;
				}
			}
		}
		else if(mInventoryData[firstFindIndex]->mData->StackSize == itemData->StackSize)
		{
			int a = 9;
		}
	}
	return false;
}


int AMainCharacter::FindIndexItemInInv(const struct FItemDataTable* itemData, int index)
{
	for (int i = index; i < mInventoryData.Num(); ++i)
	{
		if (mInventoryData[i]->mData == itemData)
		{
			return i;
		}
	}
	return -1;
}

