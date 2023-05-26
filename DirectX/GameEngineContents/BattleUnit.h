#pragma once
#include "MapUnit.h"
#include "Stat.h"
#include "Unit.h"
#include "ContentsEnum.h"
class BattleUnit : public MapUnit
{
public:

	BattleUnit();
	~BattleUnit();

	BattleUnit(const BattleUnit& _Other) = delete;
	BattleUnit(BattleUnit&& _Other) noexcept = delete;
	BattleUnit& operator=(const BattleUnit& _Other) = delete;
	BattleUnit& operator=(BattleUnit&& _Other) noexcept = delete;

	void Select();
	void SetIdle();

	// 유닛의 턴엔드 여부를 지정하는 함수
	void SetIsTurnEnd(bool _Value);
	// 유닛의 턴엔드 여부를 반환
	bool GetIsTurnEnd();
	// 유닛의 사망상태 지정
	void SetIsDie(bool _Value)
	{
		UnitData.IsDie = _Value;
	}
	// 유닛의 사망상태 반환
	bool GetIsDie()
	{
		return UnitData.IsDie;
	}
	// 유닛이 플레이어의 유닛인지 반환
	bool GetIsPlayer()
	{
		return UnitData.IsPlayer;
	}

	// 유닛코드를 지정 (초기 스탯 지정)
	void SetUnitCode(int _Code);
	// 유닛코드를 지정 (초기 스탯 지정)
	void SetUnitCode(UnitIdentityCode _Code);
	// 유닛코드를 반환 (유닛별 구분용)
	int GetUnitCode()
	{
		return UnitData.UnitCode;
	}

	// 유닛 데이터를 지정
	void SetUnitData(Unit _Value)
	{
		UnitData = _Value;
		if (false == UnitData.IsDie)
		{
			On();
		}
		SetIsTurnEnd(GetIsTurnEnd());
	}
	// 유닛 데이터를 반환
	Unit& GetUnitData()
	{
		return UnitData;
	}

	// 유닛의 이동스텟 반환
	int GetMoveStat()
	{
		return UnitData.UnitStat.Movement;
	}
	// 유닛의 사거리를 반환
	int GetRangeStat() {
		return UnitData.GetRangeStat();
	}
	// 이 유닛이 다른 유닛을 현재 공격가능한지를 반환. 두 유닛의 거리값 필요
	bool IsAttackable(int _Distance);
	// 이 유닛이 다른 유닛을 현재 공격가능한지를 반환. 다른 유닛의 포인터 필요
	bool IsAttackable(std::shared_ptr<BattleUnit> _Other);
	// 이 유닛이 다른 유닛을 현재 공격가능한지를 반환. 다른 유닛의 위치 필요
	bool IsAttackable(int2 _Other);

	// 지형을 지정
	void SetTerrain(Terrain _TerrainData)
	{
		UnitData.TerrainData = _TerrainData;
		UnitData.TerrainDodge = BattleMap::GetTerrainDodge(_TerrainData);
		UnitData.TerrainDeffence = BattleMap::GetTerrainDef(_TerrainData);
	}

	// 아이템을 추가
	void NewItem(ItemCode _Code)
	{
		UnitData.NewItem(_Code);
	}

	// 렌더러 반환
	std::shared_ptr<class SpriteRenderer> GetRenderer()
	{
		return Renderer;
	}
	std::string_view GetMapSpriteName()
	{
		return MapSpriteName;
	}

	// (적 전용) 공격범위 표시여부 반환
	bool GetIsCheckTile() { return IsCheckTile; }
	// (적 전용) 공격범위 표시여부 지정
	void SetIsCheckTile(bool _Value) { IsCheckTile = _Value; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetMoveDir(int2 _Dir) override;

	std::shared_ptr<class SpriteRenderer> Renderer = nullptr;
	std::shared_ptr<class SpriteRenderer> FrontRenderer = nullptr;
	std::string_view MapSpriteName = "";
private:
	Unit UnitData;

	bool IsCheckTile = false;
};

