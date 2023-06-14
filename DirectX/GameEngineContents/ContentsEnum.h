#pragma once

enum class RenderOrder
{
	Map,	// 맵 (배경)
	Tile,	// 타일 (이동, 공격 범위)
	Unit,	// 유닛
	Arrow,	// 화살표 (이동 방향)
	SelectUnit, // 선택된 유닛
	MapCursor,
	Effect, // 효과

	UIBackground,
	UI,		// UI
	UIText,		// UI
	UICursor,	// UI위 표시되는 이미지

	UI2,
	UI3,
	UI4,
	UI5,
	UI6,
	UI7,
	UI8,
	UI9,
	Fade,
};
enum class CollisionOrder
{
	Cursor,
	Button
};
enum class UIDir
{
	None,
	LeftUp,
	LeftDown,
	RightUp,
	RightDown
};
enum class Faction
{
	None,
	Player,
	Enemy
};

enum class UnitIdentityCode
{
	Lyn,
	BladeLordLyn,
	Sain,
	SainSword,
	Kent,
	KentSword,
	Florina,
	Wil,
	Dorcas,
	WarriorDorcas,
	Serra,
	Erk,
	Rath,
	Matthew,
	AssassinMatthew,
	Ninian,
	Lucius,
	Wallace,
	GeneralWallace,
	GeneralWallaceAxe,

	Brigand,
	Soldier,
	Mercenary,
	Archer,
	Knight,
	Mage,

	Batta,
};

enum class ItemCode
{
	None,
	SlimSword,
	IronSword,
	SteelSword,
	Lancereaver,
	Armourslayer,
	KillingSword,
	ManiKatti,

	SlimLance,
	IronLance,
	SteelLance,
	SilverLance,
	KillerLance,
	Axereaver,
	Horseslayer,

	HandAxe,
	IronAxe,
	Swordreaver,
	Hammer,

	ShortBow,
	IronBow,
	Ballista,

	Heal,
	Rescue,

	Fire,
	Flux,
	Lightning,

	DoorKey,
	ChestKey,

	Vulnerary,	// 상처약
	Elixir,		// 조합약

	Ring1,
	Ring2,
	Torch,
	GoldCard,
	MasterSeal,
};

enum class BattleClass
{
	Lord,		// 로드
	BladeLord,	// 블레이드 로드 *
	Cavalier,	// 소셜나이트
	PegasusKnight,// 페가수스 나이트
	Archer,		// 아쳐
	Fighter,	// 전사
	Warrior,	// 워리어 *
	Cleric,		// 시스터
	Mage,		// 마도사
	Nomad,		// 유목민
	Thief,		// 도적
	Assassin,	// 어쌔신 *
	Dancer,		// 무희
	Monk,		// 승려
	Knight,		// 아머나이트
	General,	// 제너럴 *
	Brigand,	// 산적 (도끼든 적)
	Soldier,	// 군인 (창든 적)
	Mercenary,	// 용병 (검든 적)
};


enum class Terrain
{
	Plain,	//평지
	Floor,	//바닥
	Road,	//길
	None,	//이동불가지역
	Forest,	//숲
	Cliff,	//벼랑
	Mountain,	//산
	Peak,		//높은 산
	Door,		//문 이동불가
	Gate,		//문 게이트 이동가능
	Ruins,		//폐허
	House,		//민가
	Shop,		//가게 (무기점)
	Sea,		//바다
	Lake,		//호수
	River,		//강
	Bridge,		//다리
	Wall,		//벽
	Fort,		//요새
	Pillar,		//기둥
	Throne,		//옥좌
};