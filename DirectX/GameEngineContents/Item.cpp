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
		std::shared_ptr<Weapon> NewWeapon = Weapon::CreateWeapon(_Code);
		ReturnItem = NewWeapon;
		break;
	}
	case ItemCode::Heal:
		ReturnItem = std::make_shared<Item>();
		ReturnItem->TypeValue = ItemType::Stave;
		ReturnItem->SetName("라이브");
		ReturnItem->Uses = 30;
		ReturnItem->MaxUses = 30;
		break;
	case ItemCode::Rescue:
		ReturnItem = std::make_shared<Item>();
		ReturnItem->TypeValue = ItemType::Stave;
		ReturnItem->SetName("레스큐");
		ReturnItem->Uses = 3;
		ReturnItem->MaxUses = 3;
		break;
	case ItemCode::Vulnerary:
		ReturnItem = std::make_shared<Item>();
		ReturnItem->TypeValue = ItemType::Potion;
		ReturnItem->SetName("상처약");
		ReturnItem->Uses = 3;
		ReturnItem->MaxUses = 3;
		break;
	case ItemCode::Elixir:
		ReturnItem = std::make_shared<Item>();
		ReturnItem->TypeValue = ItemType::Potion;
		ReturnItem->SetName("조합약");
		ReturnItem->Uses = 3;
		ReturnItem->MaxUses = 3;
		break;
	case ItemCode::MasterSeal:
		ReturnItem = std::make_shared<Item>();
		ReturnItem->TypeValue = ItemType::Potion;
		ReturnItem->SetName("마스터 프루프");
		ReturnItem->Uses = 1;
		ReturnItem->MaxUses = 1;
		break;
	case ItemCode::DoorKey:
		ReturnItem = std::make_shared<Item>();
		ReturnItem->TypeValue = ItemType::Key;
		ReturnItem->SetName("문 열쇠");
		ReturnItem->Uses = 1;
		ReturnItem->MaxUses = 1;
		break;
	case ItemCode::ChestKey:
		ReturnItem = std::make_shared<Item>();
		ReturnItem->TypeValue = ItemType::Key;
		ReturnItem->SetName("보물상자 열쇠");
		ReturnItem->Uses = 1;
		ReturnItem->MaxUses = 1;
		break;
	case ItemCode::Ring1:
	case ItemCode::Ring2:
	case ItemCode::Torch:
	case ItemCode::GoldCard:
		ReturnItem = std::make_shared<Item>();
		ReturnItem->TypeValue = ItemType::None;
		break;
	default:
		break;
	}

	static int IdentityNum = 0;

	ReturnItem->IdentityCode = IdentityNum++;
	ReturnItem->Code = _Code;
	return ReturnItem;
}

Item Item::SaveItemData(std::shared_ptr<Item> _Item)
{
	Item NewItem;
	NewItem.SetName(_Item->GetName());
	NewItem.IdentityCode = _Item->IdentityCode;
	NewItem.Code = _Item->Code;
	NewItem.TypeValue = _Item->TypeValue;
	NewItem.Uses = _Item->Uses;
	NewItem.MaxUses = _Item->MaxUses;
	return NewItem;
}

std::list<Item> Item::SaveItemDataList(std::list<std::shared_ptr<Item>> _ItemList)
{
	std::list<Item> ReturnList;

	for (std::shared_ptr<Item> _Item : _ItemList)
	{
		ReturnList.push_back(SaveItemData(_Item));
	}

	return ReturnList;
}

void Item::LoadItemDataList(std::list<std::shared_ptr<Item>>& _ItemList, std::list<Item>& _LoadList)
{
	_ItemList.clear();
	for (Item _Item : _LoadList)
	{
		std::shared_ptr<Item> _ItemPtr = _ItemList.emplace_back(std::make_shared<Item>());
		_ItemPtr->SetName(_Item.GetName());
		_ItemPtr->IdentityCode = _Item.IdentityCode;
		_ItemPtr->Code = _Item.Code;
		_ItemPtr->TypeValue = _Item.TypeValue;
		_ItemPtr->Uses = _Item.Uses;
		_ItemPtr->MaxUses = _Item.MaxUses;
	}
}

