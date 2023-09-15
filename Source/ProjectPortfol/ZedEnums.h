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
	SimpleMagicCasting UMETA(DisplayName = "주문 시전"),

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
	PhaseChange  UMETA(DisplayName = "페이즈변화"),
	LeftMove UMETA(DisplayName = "왼쪽이동"),
	RightMove UMETA(DisplayName = "오른쪽이동"),
	ForwardMove UMETA(DisplayName = "앞으로걷기"), 
	BackwardMove UMETA(DisplayName = "뒤로이동"),
	FrontRun  UMETA(DisplayName = "앞으로달리기"),
	RightRun  UMETA(DisplayName = "오른쪽달리기"),
	LeftRun  UMETA(DisplayName = "왼쪽달리기"),
	Attack01 UMETA(DisplayName = "1번공격"),
	Attack02 UMETA(DisplayName = "2번공격"),
	Magic01 UMETA(DisplayName = "1번마법"),
	Magic02 UMETA(DisplayName = "2번마법"),
	GetHit01 UMETA(DisplayName = "피격1번"),
	GetHit02 UMETA(DisplayName = "피격2번"),
	Death UMETA(DisplayName = "죽음"),
	TakeOff UMETA(DisplayName = "날아오르기시작"),
	FlyGetHit  UMETA(DisplayName = "비행중피격"),
	FlyGetHitToFalling UMETA(DisplayName = "비행중피격후추락"),
	FlyStaionary UMETA(DisplayName = "제자리비행"),
	FlyStationaryGetHit UMETA(DisplayName = "제자리비행중피격"),
	FlyStationaryGetHitToFalling UMETA(DisplayName = "제자리비행중피격후추락"),
	FlyFront UMETA(DisplayName = "앞으로 날기"),
	FlyStationarySpitFireBall UMETA(DisplayName = "제자리비행중원거리공격"),
	FlyStationarySpreadFire UMETA(DisplayName = "제자리비행중브래쓰"),
	FlyStationaryToLanding UMETA(DisplayName = "제자리비행중착륙"),
	Glide  UMETA(DisplayName = "활공"),
	GlideToLanding UMETA(DisplayName = "활공후착륙"),
	Falling UMETA(DisplayName = "추락"),
	DeathHitGround  UMETA(DisplayName = "추락중지면충돌"),


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
	RangeAttack UMETA(DisplayName = "특수스킬1번"),
	Breath UMETA(DisplayName = "특수스킬2번"),
	TakeOff  UMETA(DisplayName = "이륙"),
	FlyStaionary  UMETA(DisplayName = "제자리비행"),
	FlyingMove  UMETA(DisplayName = "비행이동"),
	GetHit   UMETA(DisplayName = "피격"),
	Falling UMETA(DisplayName = "추락"),
	PhaseChange UMETA(DisplayName = "페이즈"),
	

};

UENUM(BlueprintType)
enum class BossPhase : uint8
{
	None UMETA(DisplayName = "사용안함"),
	FIRST UMETA(DisplayName = "1페이즈"),
	SECOND UMETA(DisplayName = "2페이즈"),
	THIRD UMETA(DisplayName = "3페이즈"),
};


UENUM(BlueprintType)
enum class ZEDElementalState : uint8
{
	None UMETA(DisplayName = "무속성"),
	FIRE UMETA(DisplayName = "불속성"),
	WATER UMETA(DisplayName = "물속성"),
	ICE UMETA(DisplayName = "얼음속성"),
	EARTH UMETA(DisplayName = "대지속성"),
};


UENUM(BlueprintType)
enum class ItemType : uint8
{
	Consumption_Postion UMETA(DisplayName = "포션 소비재"),
	Consumption_Scroll UMETA(DisplayName = "스크롤 소비재"),
	Equipment_Weapon UMETA(DisplayName = "무기"),
	Equipment_Clothes UMETA(DisplayName = "방어구"),
	Quest UMETA(DisplayName = "퀘스트관련"),
	Etc UMETA(DisplayName = "퀘스트관련"),
};



UENUM(BlueprintType)
enum class RankItem : uint8
{
	SS UMETA(DisplayName = "유니크"),
	S UMETA(DisplayName = "s등급"),
	A UMETA(DisplayName = "a등급"),
	Normal UMETA(DisplayName = "일반"),
	// UMETA(DisplayName = "퀘스트관련"),
};


UENUM(BlueprintType)
enum class NPCType : uint8
{
	None UMETA(DisplayName = "None"),
	Gaurd UMETA(DisplayName = "장비함"),
	Trader UMETA(DisplayName = "거래상"),
	
};