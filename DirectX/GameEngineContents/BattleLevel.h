#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "Int2.h"
#include "UnitCommand.h"
#include "EventSystem.h"

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

	std::shared_ptr <class MapCursor> GetMapCursor()
	{
		return MainCursor;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void StageSetting() = 0;

	void SetStage(int _StageNum);

	std::vector<int2> StartPos;
	void LoadPlayerUnits(std::list<Unit>& _Units);
	std::shared_ptr<BattleUnit> LoadPlayerUnit(const Unit& _Unit);

	std::shared_ptr<BattleUnit> NewPlayerUnit(UnitIdentityCode _Code, int _Level, int2 _Pos, std::vector<ItemCode> _Items);

	std::shared_ptr<BattleUnit> NewEnemyUnit(UnitIdentityCode _Code, int _Level, int2 _Pos, std::vector<ItemCode> _Items);

	enum class BattleClearTarget
	{
		AllKill,	// 적 전멸
		Conquer,	// 제압
		Survival,	// 생존
		BossKill,	// 보스처치
	};

	BattleClearTarget ClearTarget = BattleClearTarget::AllKill;
	int2 ConquerPos = { -1, -1 };

	std::shared_ptr<EventSystem> OpeningEvent;
	std::shared_ptr <EventSystem> ClearEvent;

private:

	// State
	enum class BattleState
	{
		None,
		Opening,		// 시작시 연출단계

		PlayerPhase,	// 플레이어 턴 시작
		Select,		// 커서로 유닛을 선택하는 단계
		Move,		// 선택한 유닛으로 이동할 위치를 정하는 단계
		MoveWait,	// 유닛이 이동하는 시간을 기다리는 단계
		UnitCommand,	// 유닛의 행동을 정하는 단계
		FieldCommand,	// 커서로 땅을 클릭하면 나오는 행동들을 정하는 단계
		Battle,		// 유닛끼리 전투를 하는 단계
		BattleReturn,	// 공격레벨에서 돌아옴
		Potion,	        // 회복약 사용
		Heal,	        // 힐 사용

		EnemyPhase,	// 적의 턴이 시작
		EnemySelect,	// 적 선택
		EnemyMove,			// 적이 이동
		EnemyBattle,		// 적이 공격
		EnemyBattleReturn,	// 적 공격레벨에서 돌아옴
		EnemyPotion,	    // 회복약 사용

		Information,		// 유닛 정보창을 연상태
		GameOver,			// 게임 오버
		TimeStone,			// 시간석 사용
		Clear,				// 클리어
	};
	BattleState CurState = BattleState::None;	// 스태이트
	std::function<void(float)> StateUpdate = nullptr;
	std::function<void()> StateEnd = nullptr;

	// Actor
	std::shared_ptr<class GameEngineCamera>	MainCamera = nullptr;
	std::shared_ptr<class BattleMap> MainMap = nullptr;
	std::shared_ptr <class MapCursor> MainCursor = nullptr;
	std::list<std::shared_ptr <class BattleUnit>> PlayerUnits = std::list< std::shared_ptr <BattleUnit>>();		// 플레이어 유닛 리스트
	std::list< std::shared_ptr <BattleUnit>> EnemyUnits = std::list< std::shared_ptr <BattleUnit>>();		// 적 유닛 리스트
	std::list< std::shared_ptr <BattleUnit>> AttackableUnits = std::list< std::shared_ptr <BattleUnit>>();	// 공격 가능한 유닛 리스트
	std::list< std::shared_ptr <BattleUnit>> CloseUnits = std::list< std::shared_ptr <BattleUnit>>();		// 주변에 있는 유닛 리스트
	std::shared_ptr <BattleUnit> SelectUnit = nullptr;	// 선택된 유닛
	std::shared_ptr <BattleUnit> TargetUnit = nullptr;
	std::shared_ptr <MapUnit> CameraUnit = nullptr;
	std::list<AttackCommand> AttackRecord;

	// Map 관련
	std::shared_ptr <class TileRender> Tiles = nullptr;
	std::shared_ptr <class ArrowRender> Arrows = nullptr;
	std::vector<int2> ArrowPos = std::vector<int2>();
	std::vector<std::vector<bool>> IsMove = std::vector<std::vector<bool>>();
	std::vector<std::vector<bool>> IsAttack = std::vector<std::vector<bool>>();
	bool IsArrowOut = false;
	bool IsEnemyRangeCheck = false;
	bool IsMouseOn = false;
	bool IsSkip = false;

	// UI
	std::shared_ptr<class BattleLevelUI> BattleUI = nullptr;
	std::shared_ptr <class UnitInformationUI> InfoUI = nullptr;

	const float MoveSpeed = 10;
	int MoveIndex = 0;

	int2 BeforePos = int2::Zero;
	float4 BeforeCamPos = float4::Zero;

	std::list<std::shared_ptr<Item>>::iterator UseItem;

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

	void BattleReturnStart();
	void BattleReturnUpdate(float _DeltaTime);
	void BattleReturnEnd();

	void HealStart();
	void HealUpdate(float _DeltaTime);
	void HealEnd();

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

	void EnemyBattleReturnStart();
	void EnemyBattleReturnUpdate(float _DeltaTime);
	void EnemyBattleReturnEnd();

	void InformationStart();
	void InformationUpdate(float _DeltaTime);
	void InformationEnd();

	void GameOverStart();
	void GameOverUpdate(float _DeltaTime);
	void GameOverEnd();

	void TimeStoneStart();
	void TimeStoneUpdate(float _DeltaTime);
	void TimeStoneEnd();

	void OpeningStart();
	void OpeningUpdate(float _DeltaTime);
	void OpeningEnd();

	bool GameOverCheck();


	void PotionStart();
	void PotionUpdate(float _DeltaTime);
	void PotionEnd();

	void EnemyPotionStart();
	void EnemyPotionUpdate(float _DeltaTime);
	void EnemyPotionEnd();

	void ClearStart();
	void ClearUpdate(float _DeltaTime);
	void ClearEnd();
#pragma endregion


#pragma region Map

	// 유닛을 선택시 이동가능한 범위를 표시하는 기능 (탐사 과정이 포함)
	void MoveSearch();
	// 공격가능 범위를 표시 (MoveSearch 실행시 자동으로 실행)
	void AttackSearch();
	void AttackSearchBow();

	void MoveSearchForEnemy();
	void AttackSearchForEnemy();
	// 커서의 위치에 다른 플레이어 유닛이 없다면 MoveWait State로 전환
	void UnitMove();
	// _Pos값이 맵을 벗어나면 true를 반환하는 함수
	inline bool IsMapOut(int2 _Pos);
	// 유닛 이동과정에서 화살표를 표시하기위해 화살표를 추가하는 기능
	void AddArrow(int2 _TargetPos);
	// 유닛이 커서에 위치까지 이동하는 경로를 화살표로 표시하는 기능 (AddArrow 실행시 조건에 따라 자동으로 실행)
	void MoveCalculation();
	// 적이 공격할 유닛을 찾아서 반환하는 기능
	void EnemyFindTarget();
	// 적이 공격을 위해 이동경로를 계산하는 기능
	void MoveCalculationForEnemyAttack();
	// 적이 이동을 위한 경로를 계산하는 기능
	void MoveCalculationForEnemy();

	// 다음턴의 적이 공격 가능한 범위를 표시하는 기능 (IsCheckTile가 true인 적 한정)
	void EnemyTileCheck();

	void SetTile();

	Terrain GetTerrain(int2 _Pos);
	// 지상유닛기준 지형에 대한 이동 코스트를 계산. 이동 불가능 지형은 99가 반환
	int GetTerrainCostFoot(int2 _Pos);
	int GetTerrainCostFly(int2 _Pos);
	int GetTerrainDodge(int2 _Pos);
	int GetTerrainDef(int2 _Pos);

	// float4::Lerp 를 이용하여 이동할 위치까지 화살표를 따라 유닛을 이동시키는 기능, 목적지에 도달 시 true를 리턴합니다.
	bool UnitMoveAnim();
#pragma endregion

#pragma region Select
	
	void CursorMove();
	void CursorUnitSelect();
	void CursorAndArrowMove();
	void CursorMoveMouse();
	void CursorAndArrowMoveMouse();

	// 커서에 따른 SeledctUI위치 조절
	void CursorDirCheck(); 

	void UnitSelect();
	// 선택된 유닛에 따른 SelectUI 내용 지정
	void SetUI_UnitData(); 

#pragma endregion

#pragma region UnitCommand

public:
	void UnitCommand_Item();
	void UnitCommand_Wait();
	void UnitCommand_Attack();
	void UnitCommand_Heal();
	void UnitCommand_Exchange();
	void UnitCommand_ExchangeEnd(std::shared_ptr<BattleUnit> _Target);
	void UnitCommand_Cancel();
	void UnitCommand_CommandCancel();
	void UnitCommand_TargetAttack(std::shared_ptr<BattleUnit> _Target);
	void UnitCommand_TargetHeal(std::shared_ptr<BattleUnit> _Target, std::list<std::shared_ptr<Item>>::iterator& _ItemIter);
	void UnitCommand_ItemUse(std::list<std::shared_ptr<class Item>>::iterator& _ItemIter);
	void UnitCommand_Conquer();
private:

#pragma endregion

#pragma region FieldCommand

public:
	void FieldCommand_TimeStone();
	void FieldCommand_ArmyUnit();
	void FieldCommand_Setting();
	void FieldCommand_Exit();
	void FieldCommand_PhaseEnd();
	void FieldCommand_Cancel();
private:

#pragma endregion

#pragma region UnitInformation

public:
	void UnitInformation_Cancel();

private:

#pragma endregion


	// 커서에 따른 카메라 조절
	void CameraSetting(int2 _Value);
	void CameraMove(int2 _Value);
	void CameraSetPos();
	void CameraUpdate(float _DeltaTime);
};

