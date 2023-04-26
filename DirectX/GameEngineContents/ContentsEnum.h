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
	Sain,
	Kent,
	Florina,
	Wil,
	Dorcas,
	Serra,
	Erk,
	Rath,
	Matthew,
	Ninian,
	Lucius,
	Wallace,

	Brigand,
	Soldier,
	Mercenary,
	Archer,
	Knight,
	Mage,
};

enum class ItemCode
{
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