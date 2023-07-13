#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ZEDAniState : uint8
{
	None UMETA(DisplayName = "사용안함"),
	Idle UMETA(DisplayName = "서있기"),
	LeftMove UMETA(DisplayName = "왼쪽이동"),
	RightMove UMETA(DisplayName = "오른쪽이동"),
	ForwardMove UMETA(DisplayName = "앞으로이동"),
	BackwardMove UMETA(DisplayName = "뒤로이동"),
	Jump UMETA(DisplayName = "점프"),
	Attack UMETA(DisplayName = "공격"),
};

UENUM(BlueprintType)
enum class ZEDElementalState : uint8
{
	None UMETA(DisplayName = "무속성"),
	FIRE UMETA(DisplayName = "불속성"),
	WATER UMETA(DisplayName = "물속성"),
	ICE UMETA(DisplayName = "얼음속성"),
};