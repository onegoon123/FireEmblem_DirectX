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
	std::list<std::shared_ptr<Item>>::iterator Iter = std::find(Items.begin(), Items.end(), _Weapon);
	if (Iter == Items.end())
	{
		MsgAssert("존재하지 않는 무기를 장비하려 했습니다.");
		return;
	}
	Items.splice(Items.begin(), Items, Iter);
	UnitStat.EquipWeapon = _Weapon;
}

void Unit::DropItem(std::shared_ptr<Item> _Item)
{
	std::list<std::shared_ptr<Item>>::iterator Iter = std::find(Items.begin(), Items.end(), _Item);
	Items.erase(Iter);
	if (_Item->GetItemType() == ItemType::Weapon)
	{
		std::list<std::shared_ptr<Weapon>>::iterator WeaponIter = std::find(Weapons.begin(), Weapons.end(), _Item);
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
			if (nullptr == UnitStat.EquipWeapon)
			{
				// 무기 장비
				UnitStat.EquipWeapon = NewWeapon;
				std::list<std::shared_ptr<Item>>::iterator Iter = std::find(Items.begin(), Items.end(), UnitStat.EquipWeapon);
				Items.splice(Items.begin(), Items, Iter);
			}
		}
		return;
	}
	

	Items.push_back(Item::CreateItem(_Code));

}

