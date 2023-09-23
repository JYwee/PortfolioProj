// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/NpcCharacter.h"
#include <ZedEnums.h>
#include "MonsterNpc.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API AMonsterNpc : public ANpcCharacter
{
	GENERATED_BODY()

		AMonsterNpc();

public:
	void BeginPlay() override;

	const struct FMonsterDataTable* mMonsterDT = nullptr;
	
	void TakeDamageNpcBase(uint8 damageValue) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* WeaponMesh;

protected:
	virtual void Tick(float DeltaTime) override;

private:
	class UMiniMapComponent* mMiniMapComp;

};
