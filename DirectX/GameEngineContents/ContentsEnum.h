#pragma once

enum class RenderOrder
{
	Map,
	Tile,
	Arrow,
	Player,
	Monster,
	UI,
	UICursor,
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
	BladeLoadLyn,
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

	Brigand,
	Soldier,
	Mercenary,
	Archer,
	Knight,
	Mage,
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
