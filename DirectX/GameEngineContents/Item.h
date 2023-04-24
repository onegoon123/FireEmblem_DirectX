#pragma once

enum class ItemType
{
	None,
	Weapon,
	Potion,
	Key
};

// Ό³Έν :
class Item
{
public:
	// constrcuter destructer
	Item();
	~Item();

protected:

	ItemType TypeValue = ItemType::None;

private:

};

