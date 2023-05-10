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
	for (std::shared_ptr<Item> _Item : Items)
	{
		if (_Item->GetItemType() != ItemType::Weapon)
		{
			continue;
		}
		std::shared_ptr<Weapon> _Weapon = std::dynamic_pointer_cast<Weapon>(_Item);
		Return = Return > _Weapon->Range ? Return : _Weapon->Range;
	}
	return Return;
}


void Unit::NewItem(ItemCode _Code)
{
	std::shared_ptr<Item> NewItem = Items.emplace_back(Weapon::CreateWeapon(_Code));
	if (ItemType::Weapon == NewItem->GetItemType())
	{
		std::shared_ptr<Weapon> NewWeapon = std::static_pointer_cast<Weapon>(NewItem);
		Weapons.push_back(NewWeapon);
		UnitStat.EquipWeapon = NewWeapon;
	}
}

