#pragma once
#include <GameEngineCore/GameEngineNameObject.h>
#include "ContentsEnum.h"
enum class ItemType 
{
	None,
	Weapon,
	Potion,
	Key
};

// Ό³Έν :
class Item : public GameEngineNameObject
{
public:
	// constrcuter destructer
	Item();
	virtual ~Item();

	static std::shared_ptr<Item> CreateItem(ItemCode _Code);

	ItemType GetItemType()
	{
		return TypeValue;
	}

protected:

	ItemType TypeValue = ItemType::None;

private:

};

