// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/Battle/MagicProjectile.h"
#include <MyPlayerController.h>
#include <MainCharacter.h>
#include <Ai/BossCharacter.h>
#include <Ai/MonsterNpc.h>
#include <ZedGameInstance.h>
#include <Data/SoundDataTable.h>
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = mSphereComp;
	mSphereComp->SetCollisionProfileName(TEXT("NoCollision"), true);
	mSphereComp->ComponentTags.Add(FName("SphereMagicProj"));
	
	
	mNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	mNiagaraComp->SetupAttachment(RootComponent, TEXT("attachNigara"));

	
	
		mProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		mProjectileMovementComponent->SetUpdatedComponent(mSphereComp);
		mProjectileMovementComponent->InitialSpeed = 30.0f;
		mProjectileMovementComponent->MaxSpeed = 1000.0f;
		mProjectileMovementComponent->bRotationFollowsVelocity = true;
		mProjectileMovementComponent->bShouldBounce = false;
		mProjectileMovementComponent->Bounciness = 0.3f;
		mProjectileMovementComponent->ProjectileGravityScale = 2.0f;
	
}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	mSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMagicProjectile::BeginOverLap);
	OnDestroyed.AddDynamic(this, &AMagicProjectile::DestroyProjectile);

	
	UZedGameInstance* inst = Cast<UZedGameInstance>(GetWorld()->GetGameInstance());

	if (inst == nullptr) {
		return;
	}

	FSoundDataTable* soundData = inst->GetSoundDataTable("mapSound");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), soundData->mAllSoundsMap[SoundName::Fireball], GetActorLocation());


	if (mDirection == FVector::Zero())
	{
		AMyPlayerController* playerController = GetWorld()->GetFirstPlayerController<AMyPlayerController>();
		SetActorRotation(playerController->GetMyCharacter()->GetFollowCameraRotator());
		mDirection = playerController->GetMyCharacter()->GetFollowCameraRotator().Vector();
	}
	else {
		mProjectileMovementComponent->AddForce(mDirection * mSpeed);
		//mProjectileMovementComponent->ve
		//AddActorWorldOffset(mDirection * DeltaTime * mSpeed);
	}
}

// Called every frame
void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mProjectileDestroyTime -= DeltaTime;
	
	UE_LOG(LogTemp, Error, TEXT("%S(%u) %f, %f, %f"), __FUNCTION__, __LINE__, GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

	if (mProjectileDestroyTime < 0.0f)
	{
		Destroy();
		return;
	}
	
	
	
	
	
	//FVector tmp = GetActorForwardVector() + playerController->GetMyCharacter()->GetFollowCameraRotator().Vector();
	
	
}

void AMagicProjectile::DestroyProjectile(AActor* _Destroy)
{
	if(nullptr == mDestroyEffectObject)
	{
		return;
	}

	AActor* Actor = GetWorld()->SpawnActor<AActor>(mDestroyEffectObject);

	Actor->SetActorLocation(GetActorLocation());
	Actor->SetActorRotation(GetActorRotation());

	UZedGameInstance* inst = Cast<UZedGameInstance>(GetWorld()->GetGameInstance());

	if (inst == nullptr) {
		return;
	}

	FSoundDataTable* soundData = inst->GetSoundDataTable("mapSound");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), soundData->mAllSoundsMap[SoundName::FireballHIT], GetActorLocation());
}

void AMagicProjectile::BeginOverLap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Boss")))
	{
		this->Destroy();
		ABossCharacter* bossCharacter = Cast<ABossCharacter>(OtherActor);
		if (bossCharacter == nullptr || bossCharacter->IsValidLowLevel() == false) {
			UE_LOG(LogTemp, Error, TEXT("%S(%u) bossCharacter == nullptr"), __FUNCTION__, __LINE__);
			return;
		}
		bossCharacter->TakeDamageNpcBase(10);
	}
	else if (OtherActor->ActorHasTag(TEXT("Monster")))
	{
		this->Destroy();

		AMonsterNpc* monsterCharacter = Cast<AMonsterNpc>(OtherActor);
		if (monsterCharacter == nullptr || monsterCharacter->IsValidLowLevel() == false) {
			UE_LOG(LogTemp, Error, TEXT("%S(%u) monsterCharacter == nullptr"), __FUNCTION__, __LINE__);
			return;
		}
		monsterCharacter->TakeDamageNpcBase(10);
	}
	/*if (OtherComp->ComponentHasTag(TEXT("Weapon")))
	{
		this->Destroy();
	}*/
}

