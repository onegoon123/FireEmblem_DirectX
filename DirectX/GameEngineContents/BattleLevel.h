#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "Int2.h"

class BattleMap;
class MapCursor;
class BattleUnit;
class TileRender;
class ArrowRender;
class SelectUI;
class UnitCommandUI;
class BattleLevel : public GameEngineLevel
{
public:
	// constructer destructer
	BattleLevel();
	~BattleLevel();

	// delete Function
	BattleLevel(const BattleLevel& _Other) = delete;
	BattleLevel(BattleLevel&& _Other) = delete;
	BattleLevel& operator=(const BattleLevel& _Other) = delete;
	BattleLevel& operator=(BattleLevel&& _Other) = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	// State
	enum class BattleState
	{
		None,
		PlayerPhase,	// 플레이어 턴 시작
		Select,		// 커서로 유닛을 선택하는 단계
		Move,		// 선택한 유닛으로 이동할 위치를 정하는 단계
		MoveWait,	// 유닛이 이동하는 시간을 기다리는 단계
		UnitCommand,	// 유닛의 행동을 정하는 단계
		FieldCommand,	// 커서로 땅을 클릭하면 나오는 행동들을 정하는 단계
		Battle,		// 유닛끼리 전투를 하는 단계

		EnemyPhase,	// 적의 턴이 시작
		EnemySelect,	// 적 선택
		EnemyMove,			// 적이 이동
		EnemyBattle,		// 적이 공격

		GameOver,			// 게임 오버
	};
	BattleState CurState = BattleState::None;	// 스태이트
	void (BattleLevel::* StateUpdate)(float) = nullptr;		// 스테이트 업데이트
	void (BattleLevel::* StateEnd)() = nullptr;		// 스테이트 엔드

	// Actor
	std::shared_ptr<BattleMap> MainMap = nullptr;
	std::shared_ptr <MapCursor> MainCursor = nullptr;
	std::list<std::shared_ptr <BattleUnit>> PlayerUnits = std::list< std::shared_ptr <BattleUnit>>();
	std::list< std::shared_ptr <BattleUnit>> EnemyUnits = std::list< std::shared_ptr <BattleUnit>>();
	std::shared_ptr <BattleUnit> SelectUnit = nullptr;
	std::shared_ptr <BattleUnit> TargetUnit = nullptr;

	// Map 관련
	std::shared_ptr <TileRender> Tiles = nullptr;
	std::shared_ptr <ArrowRender> Arrows = nullptr;
	std::vector<int2> ArrowPos = std::vector<int2>();
	std::vector<std::vector<bool>> IsMove = std::vector<std::vector<bool>>();
	std::vector<std::vector<bool>> IsAttack = std::vector<std::vector<bool>>();
	bool IsArrowOut = false;

	// UI
	std::shared_ptr <SelectUI> UI_Select = nullptr;
	std::shared_ptr <UnitCommandUI> UI_UnitCommand = nullptr;

	const float MoveSpeed = 10;
	float MoveTimer = 0;
	int MoveIndex = 0;
	float4 MoveStartPos = float4::Zero;
	float4 MoveEndPos = float4::Zero;

	int2 BeforePos = int2::Zero;

#pragma region FSM
	void ChangeState(BattleState _State);

	void PlayerPhaseStart();
	void PlayerPhaseUpdate(float _DeltaTime);
	void PlayerPhaseEnd();

	void SelectStart();
	void SelectUpdate(float _DeltaTime);
	void SelectEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void MoveWaitStart();
	void MoveWaitUpdate(float _DeltaTime);
	void MoveWaitEnd();

	void UnitCommandStart();
	void UnitCommandUpdate(float _DeltaTime);
	void UnitCommandEnd();

	void FieldCommandStart();
	void FieldCommandUpdate(float _DeltaTime);
	void FieldCommandEnd();

	void BattleStart();
	void BattleUpdate(float _DeltaTime);
	void BattleEnd();

	void EnemyPhaseStart();
	void EnemyPhaseUpdate(float _DeltaTime);
	void EnemyPhaseEnd();

	void EnemySelectStart();
	void EnemySelectUpdate(float _DeltaTime);
	void EnemySelectEnd();

	void EnemyMoveStart();
	void EnemyMoveUpdate(float _DeltaTime);
	void EnemyMoveEnd();

	void EnemyBattleStart();
	void EnemyBattleUpdate(float _DeltaTime);
	void EnemyBattleEnd();

	void GameOverStart();
	void GameOverUpdate(float _DeltaTime);
	void GameOverEnd();

#pragma endregion


#pragma region Map

	// 유닛을 선택시 이동가능한 범위를 표시하는 기능 (탐사 과정이 포함)
	void MoveSearch();
	// 공격가능 범위를 표시 (MoveSearch 실행시 자동으로 실행)
	void AttackSearch();
	void AttackSearchBow();

	void MoveSearchForEnemy();
	void AttackSearchForEnemy();
	// 유닛을 이동시키는 기능
	void UnitMove();
	// _Pos값이 맵을 벗어나면 true를 반환하는 함수
	inline bool IsMapOut(int2 _Pos);
	// 유닛 이동과정에서 화살표를 표시하기위해 화살표를 추가하는 기능
	void AddArrow(int2 _TargetPos);
	// 유닛이 커서에 위치까지 이동하는 경로를 화살표로 표시하는 기능 (AddArrow 실행시 조건에 따라 자동으로 실행)
	void MoveCalculation();
	void MoveCalculationForEnemy();

	// 지상유닛기준 지형에 대한 이동 코스트를 계산. 이동 불가능 지형은 99가 반환
	int GetTerrainCostFoot(int2 _Pos);
	int GetTerrainDodge(int2 _Pos);
	int GetTerrainDef(int2 _Pos);


	bool UnitMoveAnim();
#pragma endregion

#pragma region Select


	void CursorMove();
	void CursorAndArrowMove();
	void CursorDirCheck();

	void UnitSelect();

#pragma endregion

};

