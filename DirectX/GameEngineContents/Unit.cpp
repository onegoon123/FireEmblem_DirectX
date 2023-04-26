#include "PrecompileHeader.h"
#include "Unit.h"

Unit::Unit() 
{
}

Unit::~Unit() 
{
}

void Unit::NewItem(ItemCode _Code)
{
	std::shared_ptr<Item> NewItem = Items.emplace_back(Weapon::CreateWeapon(_Code));
	if (ItemType::Weapon == NewItem->GetItemType())
	{
		std::shared_ptr<Weapon> NewWeapon = std::static_pointer_cast<Weapon>(NewItem);
		UnitStat.EquipWeapon = NewWeapon;
	}
}

