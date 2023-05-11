#include "PrecompileHeader.h"
#include "Unit.h"

Unit::Unit() 
{
}

Unit::~Unit() 
{
}

int Unit::GetRangeStat()
{
	int Return = 0;
	for (std::shared_ptr<Weapon> _Weapon : Weapons)
	{
		Return = Return > _Weapon->Range ? Return : _Weapon->Range;
	}
	return Return;
}

void Unit::EquipWeapon(std::shared_ptr<Weapon> _Weapon)
{
	std::list<std::shared_ptr<Item>>::iterator ItemIter = std::find(Items.begin(), Items.end(), _Weapon);
	if (ItemIter == Items.end())
	{
		MsgAssert("아이템리스트에 해당무기가 존재하지 않습니다." + std::string(_Weapon->GetName()));
		return;
	}
	std::list<std::shared_ptr<Weapon>>::iterator WeaponIter = std::find(Weapons.begin(), Weapons.end(), _Weapon);
	if (WeaponIter == Weapons.end())
	{
		MsgAssert("무기리스트에 해당무기가 존재하지 않습니다." + std::string(_Weapon->GetName()));
		return;
	}

	Items.splice(Items.begin(), Items, ItemIter);
	Weapons.splice(Weapons.begin(), Weapons, WeaponIter);

	CurWeapon = _Weapon;
}

void Unit::UseItem(std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	if (Items.end() == _ItemIter)
	{
		MsgAssert("잘못된 Iterator 값입니다.");
	}
	std::shared_ptr<Item> _Item = *_ItemIter;
	
	switch (_Item->GetItemCode())
	{
	case ItemCode::Vulnerary:
		Recover(10);
		break;
	case ItemCode::Elixir:
		Recover(30);
		break;
	case ItemCode::DoorKey:
	case ItemCode::ChestKey:
	case ItemCode::GoldCard:
	case ItemCode::MasterSeal:
	{
		MsgAssert("아직 지정하지 않은 아이템입니다.");
	}
		break;
	default:
		break;
	}

	// 아이템을 소진시
	if (true == _Item->Use())
	{
		Items.erase(_ItemIter);
	}
}

void Unit::DropItem(std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	if (Items.end() == _ItemIter)
	{
		MsgAssert("잘못된 Iterator 값입니다.");
	}
	Items.erase(_ItemIter);
	if ((*_ItemIter)->GetItemType() == ItemType::Weapon)
	{
		std::list<std::shared_ptr<Weapon>>::iterator WeaponIter = std::find(Weapons.begin(), Weapons.end(), *_ItemIter);
		Weapons.erase(WeaponIter);
	}
}


void Unit::NewItem(ItemCode _Code)
{
	if (_Code <= ItemCode::Lightning)
	{
		// 무기 생성
		std::shared_ptr<Weapon> NewWeapon = Weapon::CreateWeapon(_Code);
		Items.push_back(NewWeapon);	// 아이템 리스트에 추가
		// 사용가능한 무기라면
		if (NewWeapon->IsUseWeapon(UnitStat.ClassValue))
		{
			// 무기 리스트에 추가
			Weapons.push_back(NewWeapon);
			// 사용중인 무기가 없다면
			if (nullptr == CurWeapon)
			{
				// 무기 장비
				CurWeapon = NewWeapon;
				std::list<std::shared_ptr<Item>>::iterator Iter = std::find(Items.begin(), Items.end(), CurWeapon);
				Items.splice(Items.begin(), Items, Iter);
			}
		}
		return;
	}
	

	Items.push_back(Item::CreateItem(_Code));

}

