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
	FrontRun  UMETA(DisplayName = "앞으로달리기"),
	RightRun  UMETA(DisplayName = "옆으로달리기"),
};

UENUM(BlueprintType)
enum class NPCAniState : uint8
{
	None UMETA(DisplayName = "사용안함"),
	Idle UMETA(DisplayName = "서있기"),
	LeftMove UMETA(DisplayName = "왼쪽이동"),
	RightMove UMETA(DisplayName = "오른쪽이동"),
	ForwardMove UMETA(DisplayName = "앞으로이동"),
	BackwardMove UMETA(DisplayName = "뒤로이동"),
	Jump UMETA(DisplayName = "점프"),
	Attack UMETA(DisplayName = "공격"),
	FrontRun  UMETA(DisplayName = "앞으로달리기"),
	RightRun  UMETA(DisplayName = "옆으로달리기"),
	Death UMETA(DisplayName = "죽음"),
};


UENUM(BlueprintType)
enum class NPCEnemyAIControlState : uint8
{
	None UMETA(DisplayName = "사용안함"),
	Idle UMETA(DisplayName = "서있기"),
	Move UMETA(DisplayName = "이동"),
	Attack UMETA(DisplayName = "공격"),
	Return UMETA(DisplayName = "복귀"),
	Patrol UMETA(DisplayName = "정찰"),
	Death UMETA(DisplayName = "죽음"),
};


UENUM(BlueprintType)
enum class BossAniState : uint8
{
	None UMETA(DisplayName = "사용안함"),
	Idle UMETA(DisplayName = "서있기"), //idle
	LeftMove UMETA(DisplayName = "왼쪽이동"),
	RightMove UMETA(DisplayName = "오른쪽이동"),
	ForwardMove UMETA(DisplayName = "앞으로걷기"), 
	BackwardMove UMETA(DisplayName = "뒤로이동"),
	TakeOff UMETA(DisplayName = "날아오르기시작"),
	FrontRun  UMETA(DisplayName = "앞으로달리기"),
	RightRun  UMETA(DisplayName = "오른쪽달리기"),
	LeftRun  UMETA(DisplayName = "왼쪽달리기"),
	Attack01 UMETA(DisplayName = "1번공격"),
	Attack02 UMETA(DisplayName = "2번공격"),
	Magic01 UMETA(DisplayName = "1번마법"),
	Magic02 UMETA(DisplayName = "2번마법"),
	Death UMETA(DisplayName = "죽음"),

};

UENUM(BlueprintType)
enum class BossDragonAIControlState : uint8
{
	None UMETA(DisplayName = "사용안함"),
	Idle UMETA(DisplayName = "서있기"),
	Move UMETA(DisplayName = "이동"),
	Attack UMETA(DisplayName = "공격"),
	Return UMETA(DisplayName = "복귀"),
	Patrol UMETA(DisplayName = "정찰"),
	Death UMETA(DisplayName = "죽음"),
	Skill_1 UMETA(DisplayName = "특수스킬1번"),
	Skill_2 UMETA(DisplayName = "특수스킬1번"),
};



UENUM(BlueprintType)
enum class ZEDElementalState : uint8
{
	None UMETA(DisplayName = "무속성"),
	FIRE UMETA(DisplayName = "불속성"),
	WATER UMETA(DisplayName = "물속성"),
	ICE UMETA(DisplayName = "얼음속성"),
};

