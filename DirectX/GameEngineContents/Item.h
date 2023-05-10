#pragma once
#include <GameEngineCore/GameEngineNameObject.h>
#include "ContentsEnum.h"
enum class ItemType 
{
	None,
	Weapon,	// 무기
	Stave,	// 지팡이
	Potion,	// 포션
	Key
};

// 설명 :
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
	ItemCode GetItemCode()
	{
		return Code;
	}
protected:
	ItemCode Code = ItemCode::None;
	ItemType TypeValue = ItemType::None;

private:

};

