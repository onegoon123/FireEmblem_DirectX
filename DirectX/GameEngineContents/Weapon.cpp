#include "PrecompileHeader.h"
#include "Weapon.h"
Weapon::Weapon() 
{
	TypeValue = ItemType::Weapon;
}

Weapon::Weapon(ItemCode _Code)
{
	TypeValue = ItemType::Weapon;
	switch (_Code)
	{
	case ItemCode::SlimSword:
		SetWeapon_SlimSword();
		break;
	case ItemCode::IronSword:
		SetWeapon_IronSword();
		break;
	case ItemCode::SteelSword:
		SetWeapon_SteelSword();
		break;
	case ItemCode::Lancereaver:
		SetWeapon_Lancereaver();
		break;
	case ItemCode::Armourslayer:
		SetWeapon_Armourslayer();
		break;
	case ItemCode::KillingSword:
		SetWeapon_KillingSword();
		break;
	case ItemCode::ManiKatti:
		SetWeapon_ManiKatti();
		break;
	case ItemCode::SlimLance:
		SetWeapon_SlimLance();
		break;
	case ItemCode::IronLance:
		SetWeapon_IronLance();
		break;
	case ItemCode::SteelLance:
		SetWeapon_SteelLance();
		break;
	case ItemCode::SilverLance:
		SetWeapon_SilverLance();
		break;
	case ItemCode::KillerLance:
		SetWeapon_KillerLance();
		break;
	case ItemCode::Axereaver:
		SetWeapon_Axereaver();
		break;
	case ItemCode::Horseslayer:
		SetWeapon_Horseslayer();
		break;
	case ItemCode::HandAxe:
		SetWeapon_HandAxe();
		break;
	case ItemCode::IronAxe:
		SetWeapon_IronAxe();
		break;
	case ItemCode::Swordreaver:
		SetWeapon_Swordreaver();
		break;
	case ItemCode::Hammer:
		SetWeapon_Hammer();
		break;
	case ItemCode::ShortBow:
		SetWeapon_ShortBow();
		break;
	case ItemCode::IronBow:
		SetWeapon_IronBow();
		break;
	case ItemCode::Ballista:
		SetWeapon_Ballista();
		break;
	case ItemCode::Fire:
		SetWeapon_Fire();
		break;
	case ItemCode::Flux:
		SetWeapon_Flux();
		break;
	case ItemCode::Lightning:
		SetWeapon_Lightning();
		break;
	case ItemCode::Heal:
	case ItemCode::Rescue:
	case ItemCode::DoorKey:
	case ItemCode::ChestKey:
	case ItemCode::Vulnerary:
	case ItemCode::Elixir:
	case ItemCode::Ring1:
	case ItemCode::Ring2:
	case ItemCode::Torch:
	case ItemCode::GoldCard:
	case ItemCode::MasterSeal:
	{
		MsgAssert("잘못된 코드의 무기를 생성하려 했습니다.");
		return;
	}
	default:
		break;
	}
}

Weapon::~Weapon() 
{
}

std::shared_ptr<Weapon> Weapon::CreateWeapon(ItemCode _Code)
{
	return std::make_shared<Weapon>(_Code);
}

void Weapon::SetWeapon_SlimSword()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("세신의 검");
	Damage = 3;
	Hit = 100;
	Critical = 5;
	Weight = 2;
	Range = 1;
	Uses = 30;
	MaxUses = 30;
}

void Weapon::SetWeapon_IronSword()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("철의 검");
	Damage = 5;
	Hit = 90;
	Critical = 0;
	Weight = 5;
	Range = 1;
	Uses = 46;
	MaxUses = 46;
}

void Weapon::SetWeapon_SteelSword()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("강철의 검");
	Damage = 10;
	Hit = 75;
	Critical = 0;
	Weight = 8;
	Range = 1;
	Uses = 30;
	MaxUses = 30;
}

void Weapon::SetWeapon_Lancereaver()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("랜스 버스터");
	IsReaver = true;
	Damage = 9;
	Hit = 75;
	Critical = 5;
	Weight = 9;
	Range = 1;
	Uses = 15;
	MaxUses = 15;
}

void Weapon::SetWeapon_Armourslayer()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("아머 킬러");
	ValidArmour = true;
	Damage = 8;
	Hit = 80;
	Critical = 0;
	Weight = 11;
	Range = 1;
	Uses = 18;
	MaxUses = 18;
}

void Weapon::SetWeapon_KillingSword()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("킬소드");
	Damage = 9;
	Hit = 75;
	Critical = 30;
	Weight = 7;
	Range = 1;
	Uses = 20;
	MaxUses = 20;
}

void Weapon::SetWeapon_ManiKatti()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("마니 카티");
	Damage = 8;
	Hit = 80;
	Critical = 20;
	Weight = 3;
	Range = 1;
	Uses = 45;
	MaxUses = 45;
}

void Weapon::SetWeapon_SlimLance()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("세신의 창");
	Damage = 4;
	Hit = 85;
	Critical = 5;
	Weight = 4;
	Range = 1;
	Uses = 30;
	MaxUses = 30;
}

void Weapon::SetWeapon_IronLance()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("철의 창");
	Damage = 7;
	Hit = 80;
	Critical = 0;
	Weight = 8;
	Range = 1;
	Uses = 45;
	MaxUses = 45;
}

void Weapon::SetWeapon_SteelLance()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("강철의 창");
	Damage = 10;
	Hit = 70;
	Critical = 0;
	Weight = 13;
	Range = 1;
	Uses = 30;
	MaxUses = 30;
}

void Weapon::SetWeapon_SilverLance()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("은의 창");
	Damage = 14;
	Hit = 75;
	Critical = 0;
	Weight = 10;
	Range = 1;
	Uses = 20;
	MaxUses = 20;
}

void Weapon::SetWeapon_KillerLance()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("킬러랜스");
	Damage = 10;
	Hit = 70;
	Critical = 30;
	Weight = 9;
	Range = 1;
	Uses = 20;
	MaxUses = 20;
}

void Weapon::SetWeapon_Axereaver()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("엑스 버스터");
	IsReaver = true;
	Damage = 10;
	Hit = 70;
	Critical = 5;
	Weight = 11;
	Range = 1;
	Uses = 15;
	MaxUses = 15;
}

void Weapon::SetWeapon_Horseslayer()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("호스 킬러");
	ValidHorse = true;
	Damage = 7;
	Hit = 70;
	Critical = 0;
	Weight = 13;
	Range = 1;
	Uses = 16;
	MaxUses = 16;
}

void Weapon::SetWeapon_HandAxe()
{
	WeaponTypeValue = WeaponType::Axe;
	SetName("투척 도끼");
	Damage = 7;
	Hit = 60;
	Critical = 0;
	Weight = 12;
	Range = 2;
	Uses = 20;
	MaxUses = 20;
}

void Weapon::SetWeapon_IronAxe()
{
	WeaponTypeValue = WeaponType::Axe;
	SetName("철의 도끼");
	Damage = 8;
	Hit = 75;
	Critical = 0;
	Weight = 10;
	Range = 1;
	Uses = 45;
	MaxUses = 45;
}

void Weapon::SetWeapon_Swordreaver()
{
	WeaponTypeValue = WeaponType::Axe;
	SetName("소드 버스터");
	IsReaver = true;
	Damage = 11;
	Hit = 65;
	Critical = 5;
	Weight = 11;
	Range = 1;
	Uses = 15;
	MaxUses = 15;
}

void Weapon::SetWeapon_Hammer()
{
	WeaponTypeValue = WeaponType::Axe;
	SetName("해머");
	ValidArmour = true;
	Damage = 10;
	Hit = 55;
	Critical = 0;
	Weight = 15;
	Range = 1;
	Uses = 20;
	MaxUses = 20;
}

void Weapon::SetWeapon_ShortBow()
{
	WeaponTypeValue = WeaponType::Bow;
	SetName("단궁");
	Damage = 5;
	Hit = 85;
	Critical = 0;
	Weight = 3;
	Range = 2;
	Uses = 22;
	MaxUses = 22;
}

void Weapon::SetWeapon_IronBow()
{
	WeaponTypeValue = WeaponType::Bow;
	SetName("철의 활");
	Damage = 6;
	Hit = 85;
	Critical = 0;
	Weight = 5;
	Range = 2;
	Uses = 45;
	MaxUses = 45;
}

void Weapon::SetWeapon_Ballista()
{
	WeaponTypeValue = WeaponType::Bow;
	SetName("발리스타");
	Damage = 8;
	Hit = 70;
	Critical = 0;
	Weight = 20;
	Range = 8;
	Uses = 5;
	MaxUses = 5;
}

void Weapon::SetWeapon_Fire()
{
	WeaponTypeValue = WeaponType::AnimaTome;
	SetName("파이어");
	Damage = 5;
	Hit = 90;
	Critical = 0;
	Weight = 4;
	Range = 2;
	Uses = 40;
	MaxUses = 40;
}

void Weapon::SetWeapon_Flux()
{
	WeaponTypeValue = WeaponType::DarkTome;
	SetName("밀");
	Damage = 7;
	Hit = 80;
	Critical = 0;
	Weight = 8;
	Range = 2;
	Uses = 45;
	MaxUses = 45;
}

void Weapon::SetWeapon_Lightning()
{
	WeaponTypeValue = WeaponType::LightTome;
	SetName("라이트닝");
	Damage = 4;
	Hit = 95;
	Critical = 0;
	Weight = 6;
	Range = 2;
	Uses = 35;
	MaxUses = 35;
}

int Weapon::GetWeaponeTriangle(std::shared_ptr<Weapon> _SubjectWeapon, std::shared_ptr<Weapon> _TargetWeapon)
{

	switch (_SubjectWeapon->WeaponTypeValue)
	{
	case WeaponType::Sword:
	{
		switch (_TargetWeapon->WeaponTypeValue)
		{
		case WeaponType::Lance:
		case WeaponType::SwordReaver:
			return -1;
		case WeaponType::AxeReaver:
		case WeaponType::Axe:
			return 1;
		case WeaponType::LanceReaver:
		case WeaponType::Sword:
		default:
			return 0;
		}
	}
	case WeaponType::LanceReaver:
	{
		switch (_TargetWeapon->WeaponTypeValue)
		{
		case WeaponType::AxeReaver:
		case WeaponType::Axe:
			return -1;
		case WeaponType::SwordReaver:
		case WeaponType::Lance:
			return 1;
		case WeaponType::LanceReaver:
		case WeaponType::Sword:
		default:
			return 0;
		}
	}
	case WeaponType::Lance:
	{
		switch (_TargetWeapon->WeaponTypeValue)
		{
		case WeaponType::Axe:
		case WeaponType::LanceReaver:
			return -1;
		case WeaponType::Sword:
		case WeaponType::SwordReaver:
			return 1;
		case WeaponType::AxeReaver:
		case WeaponType::Lance:
		default:
			return 0;
		}
	}
	case WeaponType::AxeReaver:
	{
		switch (_TargetWeapon->WeaponTypeValue)
		{
		case WeaponType::Sword:
		case WeaponType::SwordReaver:
			return -1;
		case WeaponType::Axe:
		case WeaponType::LanceReaver:
			return 1;
		case WeaponType::Lance:
		case WeaponType::AxeReaver:
		default:
			return 0;
		}
	}
	case WeaponType::Axe:
	{
		switch (_TargetWeapon->WeaponTypeValue)
		{
		case WeaponType::AxeReaver:
		case WeaponType::Sword:
			return -1;
		case WeaponType::LanceReaver:
		case WeaponType::Lance:
			return 1;
		case WeaponType::SwordReaver:
		case WeaponType::Axe:
		default:
			return 0;
		}
	}
	case WeaponType::SwordReaver:
	{
		switch (_TargetWeapon->WeaponTypeValue)
		{
		case WeaponType::Lance:
		case WeaponType::LanceReaver:
			return -1;
		case WeaponType::Sword:
		case WeaponType::AxeReaver:
			return 1;
		case WeaponType::Axe:
		case WeaponType::SwordReaver:
		default:
			return 0;
		}
	}
	case WeaponType::None:
	case WeaponType::Bow:
	case WeaponType::AnimaTome:
	case WeaponType::DarkTome:
	case WeaponType::LightTome:
	default:
		return 0;
	}
	return 0;
}


bool Weapon::IsUseWeapon(BattleClass _Class)
{
	switch (_Class)
	{
	case BattleClass::Lord:
	{
		if (WeaponTypeValue == WeaponType::Sword) { return true; }
		if (WeaponTypeValue == WeaponType::LanceReaver) { return true; }
		return false;
	}
	case BattleClass::BladeLord:
	{
		if (WeaponTypeValue == WeaponType::Sword) { return true; }
		if (WeaponTypeValue == WeaponType::LanceReaver) { return true; }
		return false;
	}
	case BattleClass::Cavalier:
	{
		if (WeaponTypeValue == WeaponType::Sword) { return true; }
		if (WeaponTypeValue == WeaponType::LanceReaver) { return true; }
		if (WeaponTypeValue == WeaponType::Lance) { return true; }
		if (WeaponTypeValue == WeaponType::AxeReaver) { return true; }
		return false;
	}
	case BattleClass::PegasusKnight:
	{
		if (WeaponTypeValue == WeaponType::Lance) { return true; }
		if (WeaponTypeValue == WeaponType::AxeReaver) { return true; }
		return false;
	}
	case BattleClass::Archer:
	{
		if (WeaponTypeValue == WeaponType::Bow) { return true; }
		return false;
	}
	case BattleClass::Fighter:
	{
		if (WeaponTypeValue == WeaponType::Axe) { return true; }
		if (WeaponTypeValue == WeaponType::SwordReaver) { return true; }
		return false;
	}
	case BattleClass::Warrior:
	{
		if (WeaponTypeValue == WeaponType::Axe) { return true; }
		if (WeaponTypeValue == WeaponType::SwordReaver) { return true; }
		return false;
	}
	case BattleClass::Cleric:
	{
		return false;
	}
	case BattleClass::Mage:
	{
		if (WeaponTypeValue == WeaponType::AnimaTome) { return true; }
		return false;
	}
	case BattleClass::Nomad:
	{
		if (WeaponTypeValue == WeaponType::Bow) { return true; }
		return false;
	}
	case BattleClass::Thief:
	{
		if (WeaponTypeValue == WeaponType::Sword) { return true; }
		if (WeaponTypeValue == WeaponType::LanceReaver) { return true; }
		return false;
	}
	case BattleClass::Assassin:
	{
		if (WeaponTypeValue == WeaponType::Sword) { return true; }
		if (WeaponTypeValue == WeaponType::LanceReaver) { return true; }
		return false;
	}
	case BattleClass::Dancer:
	{
		return false;
	}
	case BattleClass::Monk:
	{
		if (WeaponTypeValue == WeaponType::LightTome) { return true; }
		return false;
	}
	case BattleClass::Knight:
	{
		if (WeaponTypeValue == WeaponType::Lance) { return true; }
		if (WeaponTypeValue == WeaponType::AxeReaver) { return true; }
		return false;
	}
	case BattleClass::General:
	{
		if (WeaponTypeValue == WeaponType::Lance) { return true; }
		if (WeaponTypeValue == WeaponType::AxeReaver) { return true; }
		if (WeaponTypeValue == WeaponType::Axe) { return true; }
		if (WeaponTypeValue == WeaponType::SwordReaver) { return true; }
		return false;
	}
	case BattleClass::Brigand:
	{
		if (WeaponTypeValue == WeaponType::Axe) { return true; }
		if (WeaponTypeValue == WeaponType::SwordReaver) { return true; }
		return false;
	}
	case BattleClass::Soldier:
	{
		if (WeaponTypeValue == WeaponType::Lance) { return true; }
		if (WeaponTypeValue == WeaponType::AxeReaver) { return true; }
		return false;
	}
	case BattleClass::Mercenary:
	{
		if (WeaponTypeValue == WeaponType::Sword) { return true; }
		if (WeaponTypeValue == WeaponType::LanceReaver) { return true; }
		return false;
	}
	default:
		break;
	}
	return false;
}
