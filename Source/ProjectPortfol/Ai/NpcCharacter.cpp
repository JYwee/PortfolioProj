// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "MyAIController.h"
#include "../ZedGameInstance.h"
#include "../Data/MonsterDataTable.h"
#include <UI/UIHpBar.h>
#include <InGameMode.h>
#include "Kismet/GameplayStatics.h"
#include "NpcAnimInstance.h"


// Sets default values
ANpcCharacter::ANpcCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mLockOnSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	mLockOnSphere->SetupAttachment(RootComponent);
	mLockOnSphere->SetVisibility(false);

	mLockOnWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnArrowWDG"));
	mLockOnWidgetComp->SetupAttachment(RootComponent);
	mLockOnWidgetComp->SetVisibility(false);

	mHP_WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP_NPC_WDG"));
	
	mHP_WidgetComp->SetupAttachment(GetMesh());


	//mHP_WidgetComp->SetVisibility(true);
	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ANpcCharacter::BeginOverLap);
	//setcontroller
}

UBlackboardComponent* ANpcCharacter::GetBlackboardComponent()
{
	if (mBlackboardComponent == nullptr) 
	{
		AMyAIController* myAiCon = GetController<AMyAIController>();

		if (myAiCon == nullptr)
		{
			return nullptr;
		}

		mBlackboardComponent = myAiCon->GetBlackboardComponent();
	}
	return mBlackboardComponent;
}

void ANpcCharacter::TakeDamageNpcBase(uint8 damageValue)
{
	
}

// Called when the game starts or when spawned
void ANpcCharacter::BeginPlay()
{
	//UZedGameInstance* inst = Cast<UZedGameInstance>(GetWorld()->GetGameInstance());

	//if (inst == nullptr || inst->IsValidLowLevel() == false)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  inst->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
	//	return;
	//}

	//mMonsterDT = inst->GetMonsterDataTable(TEXT("meeleEnemy"));

	//SetAllAnimation<NPCAniState>(mMonsterDT->MapAnimation);


	Super::BeginPlay();


	// 

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ANpcCharacter::BeginOverLap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ANpcCharacter::EndOverLap);

	UZedGameInstance* Inst = GetGameInstance<UZedGameInstance>();
	
	if (Inst == nullptr || Inst->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr Inst->IsValidLowLevel() == false" ), __FUNCTION__, __LINE__);
		return;
	}

	Inst->AllNpcCharac.Add(this);
	
	

	//
	//UAnimInstance* tmp = GetMesh()->GetAnimInstance();
	
}

// Called every frame
void ANpcCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UUIHpBar* HealthBarWidget = Cast<UUIHpBar>(mHP_WidgetComp->GetWidget());

	if (HealthBarWidget != nullptr)
	{
	if (HealthBarWidget->mHpProgressBar != nullptr && Tags.Contains("InteracNPC") == false) {
		HealthBarWidget->mHpProgressBar->SetPercent(GetHpPercent());

		if (HealthBarWidget->mHpProgressBar->Percent < 1.0f)
		{
			HealthBarWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			HealthBarWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	}

	
	if (mIsOverlapWithPlayerAtt == true)
	{
		AInGameMode* myGameMode = Cast<AInGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (myGameMode->GetPlayerAttProcessing() == true)
		{
			TakeDamageNpcBase(20);
			myGameMode->SetPlayerAttProcess(false);
		}
	}

}

// Called to bind functionality to input
void ANpcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANpcCharacter::Destroyed()
{
	Super::Destroy();

	UZedGameInstance* Inst = GetGameInstance<UZedGameInstance>();

	if (Inst == nullptr || Inst->IsValidLowLevel() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u) Inst == nullptr  nst->IsValidLowLevel() == false"), __FUNCTION__, __LINE__);
		return;
	}

	for (int i = 0; i < Inst->AllNpcCharac.Num(); ++i)
	{
		if (Inst->AllNpcCharac[i] == this)
		{
			//mBlackboardComponent
		}
	}
}

void ANpcCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	mNpcAnimInstance = Cast<UNpcAnimInstance>(GetMesh()->GetAnimInstance());

	//mNpcAnimInstance->SetAllAnimations(mAllAnimations);
}

UAnimMontage* ANpcCharacter::GetAnimMontage(int index) const
{
	if (mAllAnimations.Contains(index))
	{
		return mAllAnimations[index];
	}
	return nullptr;
}



void ANpcCharacter::MontageEnd(UAnimMontage* animMontage, bool inter)
{
	//TSubclassOf<UAnimInstance> Inst = ANpcCharacter::StaticClass();
	//
	//if (Tags.Contains(TEXT("Boss")))
	//{
	//	int a =0;
	//}

	//// Anim ����� ��Ÿ��

	//if (mAllAnimations[static_cast<int>(NPCAniState::Attack)] == animMontage)
	//{
	//	SetAniState<NPCAniState>(NPCAniState::Idle);
	//	//Montage_Play(AllAnimations[ZEDAniState::Idle], 1.0f);
	//}

	//if (mAllAnimations[static_cast<int>(NPCAniState::Jump)] == animMontage)
	//{
	//	SetAniState<NPCAniState>(NPCAniState::Idle);
	//	//Montage_Play(AllAnimations[ZEDAniState::Idle], 1.0f)
	//}

}

void ANpcCharacter::BeginOverLap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{

	/*if (OtherActor->ActorHasTag(TEXT("Weapon")))
	{
		this->Destroy();
	}*/
	if (OtherComp->ComponentHasTag(TEXT("Weapon")))
	{
		AInGameMode* myGameMode = Cast<AInGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (myGameMode->GetPlayerAttProcessing() == true)
		{
			TakeDamageNpcBase(20);
			myGameMode->SetPlayerAttProcess(false);
		}
		else 
		{
			mIsOverlapWithPlayerAtt = true;
		}
		//OtherActor
		//UZedGameInstance* Inst = GetGameInstance<UZedGameInstance>();
		//AMainCharacter* character = Cast<AMainCharacter>(GetOwningActor());

		
	}

	SweepResult.Distance;
	SweepResult.FaceIndex;
	SweepResult.GetActor();

}

void ANpcCharacter::EndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->ComponentHasTag(TEXT("Weapon")))
	{
		mIsOverlapWithPlayerAtt = false;
	}
}


