#include "PrecompileHeader.h"
#include "Item.h"
#include "Weapon.h"

Item::Item() 
{
}

Item::~Item() 
{
}

std::shared_ptr<Item> Item::CreateItem(ItemCode _Code)
{
	std::shared_ptr<Item> ReturnItem = nullptr;

	switch (_Code)
	{
	case ItemCode::SlimSword:
	case ItemCode::IronSword:
	case ItemCode::SteelSword:
	case ItemCode::Lancereaver:
	case ItemCode::Armourslayer:
	case ItemCode::KillingSword:
	case ItemCode::ManiKatti:
	case ItemCode::SlimLance:
	case ItemCode::IronLance:
	case ItemCode::SteelLance:
	case ItemCode::SilverLance:
	case ItemCode::KillerLance:
	case ItemCode::Axereaver:
	case ItemCode::Horseslayer:
	case ItemCode::HandAxe:
	case ItemCode::IronAxe:
	case ItemCode::Swordreaver:
	case ItemCode::Hammer:
	case ItemCode::ShortBow:
	case ItemCode::IronBow:
	case ItemCode::Ballista:
	case ItemCode::Fire:
	case ItemCode::Flux:
	case ItemCode::Lightning:
	{
		//std::shared_ptr<Weapon> NewWeapon = std::make_shared<Weapon>(new Weapon(_Code));
		//ReturnItem = std::make_shared<Item>(dynamic_cast<Item*>(_Code)));
		break;
	}

	case ItemCode::Heal:
	case ItemCode::Rescue:

		break;
	case ItemCode::Vulnerary:
	case ItemCode::Elixir:

		break;
	case ItemCode::MasterSeal:

		break;
	case ItemCode::DoorKey:
	case ItemCode::ChestKey:

		break;
	case ItemCode::Ring1:
	case ItemCode::Ring2:
	case ItemCode::Torch:
	case ItemCode::GoldCard:

		break;
	default:
		break;
	}

	return ReturnItem;
}

