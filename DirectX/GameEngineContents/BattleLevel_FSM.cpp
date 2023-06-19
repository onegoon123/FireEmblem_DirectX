#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "FERandom.h"
#include "BattleAnimationLevel.h"
#include "SpriteRenderer.h"
#include "BattleUnit.h"
#include "BattleMap.h"
#include "MapCursor.h"
#include "TileRender.h"
#include "ArrowRender.h"
#include "UnitCommand.h"
#include "BattleLevelUI.h"
#include "UnitInformationUI.h"
#include "DebugWindow.h" // 임시
#include "FadeEffect.h"
void BattleLevel::ChangeState(BattleState _State)
{

	if (CurState != BattleState::None)
	{
		StateEnd();
	}
	CurState = _State;

	switch (_State)
	{
	case BattleLevel::BattleState::PlayerPhase:
		StateUpdate = std::bind(&BattleLevel::PlayerPhaseUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::PlayerPhaseEnd, this);
		PlayerPhaseStart();
		break;
	case BattleLevel::BattleState::Select:
		StateUpdate = std::bind(&BattleLevel::SelectUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::SelectEnd, this);
		SelectStart();
		break;
	case BattleLevel::BattleState::Move:
		StateUpdate = std::bind(&BattleLevel::MoveUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::MoveEnd, this);
		MoveStart();
		break;
	case BattleLevel::BattleState::MoveWait:
		StateUpdate = std::bind(&BattleLevel::MoveWaitUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::MoveWaitEnd, this);
		MoveWaitStart();
		break;
	case BattleLevel::BattleState::UnitCommand:
		StateUpdate = std::bind(&BattleLevel::UnitCommandUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::UnitCommandEnd, this);
		UnitCommandStart();
		break;
	case BattleLevel::BattleState::FieldCommand:
		StateUpdate = std::bind(&BattleLevel::FieldCommandUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::FieldCommandEnd, this);
		FieldCommandStart();
		break;
	case BattleLevel::BattleState::Battle:
		StateUpdate = std::bind(&BattleLevel::BattleUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::BattleEnd, this);
		BattleStart();
		break;
	case BattleLevel::BattleState::BattleReturn:
		StateUpdate = std::bind(&BattleLevel::BattleReturnUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::BattleReturnEnd, this);
		BattleReturnStart();
		break;
	case BattleLevel::BattleState::EnemyPhase:
		StateUpdate = std::bind(&BattleLevel::EnemyPhaseUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::EnemyPhaseEnd, this);
		EnemyPhaseStart();
		break;
	case BattleLevel::BattleState::EnemySelect:
		StateUpdate = std::bind(&BattleLevel::EnemySelectUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::EnemySelectEnd, this);
		EnemySelectStart();
		break;
	case BattleLevel::BattleState::EnemyMove:
		StateUpdate = std::bind(&BattleLevel::EnemyMoveUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::EnemyMoveEnd, this);
		EnemyMoveStart();
		break;
	case BattleLevel::BattleState::EnemyBattle:
		StateUpdate = std::bind(&BattleLevel::EnemyBattleUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::EnemyBattleEnd, this);
		EnemyBattleStart();
		break;
	case BattleLevel::BattleState::EnemyBattleReturn:
		StateUpdate = std::bind(&BattleLevel::EnemyBattleReturnUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::EnemyBattleReturnEnd, this);
		EnemyBattleReturnStart();
		break;
	case BattleLevel::BattleState::Information:
		StateUpdate = std::bind(&BattleLevel::InformationUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::InformationEnd, this);
		InformationStart();
		break;
	case BattleLevel::BattleState::GameOver:
		StateUpdate = std::bind(&BattleLevel::GameOverUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::GameOverEnd, this);
		GameOverStart();
		break;
	case BattleLevel::BattleState::TimeStone:
		StateUpdate = std::bind(&BattleLevel::TimeStoneUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::TimeStoneEnd, this);
		TimeStoneStart();
		break;
	case BattleLevel::BattleState::Opening:
		StateUpdate = std::bind(&BattleLevel::OpeningUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::OpeningEnd, this);
		OpeningStart();
		break;
	case BattleLevel::BattleState::Potion:
		StateUpdate = std::bind(&BattleLevel::PotionUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::PotionEnd, this);
		PotionStart();
		break;
	case BattleLevel::BattleState::Heal:
		StateUpdate = std::bind(&BattleLevel::HealUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::HealEnd, this);
		HealStart();
		break;
	case BattleLevel::BattleState::EnemyPotion:
		StateUpdate = std::bind(&BattleLevel::EnemyPotionUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::EnemyPotionEnd, this);
		EnemyPotionStart();
		break;
	case BattleLevel::BattleState::Clear:
		StateUpdate = std::bind(&BattleLevel::ClearUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::ClearEnd, this);
		ClearStart();
		break;
	case BattleLevel::BattleState::ClassChange:
		StateUpdate = std::bind(&BattleLevel::ClassChangeUpdate, this, std::placeholders::_1);
		StateEnd = std::bind(&BattleLevel::ClassChangeEnd, this);
		ClassChangeStart();
		break;
	default:
	{
		MsgAssert("아직 지정하지 않은 State 입니다");
		break;
	}
	}

}

void BattleLevel::PlayerPhaseStart()
{
	UnitCommand::PhaseStart(Faction::Player);
	// 모든 적 유닛 턴 복구
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		_Unit->SetIsTurnEnd(false);
		_Unit->SetIdle();
	}

	if (ClearTarget == BattleClearTarget::Survival)
	{
		if (SurvivalTurn < UnitCommand::GetCountTurn())
		{
			ChangeState(BattleState::Clear);
			return;
		}
	}
	// 지형에 따른 체력회복
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		switch (_Unit->GetUnitData().GetTerrainData())
		{
		case Terrain::Fort:
			_Unit->GetUnitData().RecoverPersent(0.2f);
			break;
		case Terrain::Gate:
			_Unit->GetUnitData().RecoverPersent(0.1f);
			break;
		default:
			break;
		}
	}
	MainCursor->Off();
	BattleUI->PhaseOn(Faction::Player);
}

void BattleLevel::PlayerPhaseUpdate(float _DeltaTime)
{
	if (true == BattleUI->IsPhaseEnd())
	{
		ChangeState(BattleState::Select);
	}
}

void BattleLevel::PlayerPhaseEnd()
{
	// 플레이어 리스트 중 가장 앞에있는 유닛을 선택
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (_Unit->GetIsDie()) { continue; }
		SelectUnit = _Unit;
		MainCursor->SetCursorPos(SelectUnit->GetMapPos());
		CameraSetPos();
		break;
	}
}

void BattleLevel::SelectStart()
{
	// Select 상태가 시작될때 마다 모든 유닛의 행동이 끝났는지 체크
	bool IsTurnEnd = true;	// 턴이 끝났는가?
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }

		if (false == _Unit->GetIsTurnEnd())
		{
			// 아직 턴이 안끝난 유닛이 있다
			IsTurnEnd = false;
			break;
		}
	}
	// 모든 유닛의 턴이 끝났다면
	if (true == IsTurnEnd)
	{
		ChangeState(BattleState::EnemyPhase);	// 적 턴으로
		return;
	}

	// 선택 유닛 초기화
	//SelectUnit = nullptr;

	// Select State시 필요한 UI
	MainCursor->On();
	BattleUI->SelectOn();
	CursorDirCheck();
	// 적 타일 체크
	EnemyTileCheck();
	// 선택된 유닛이 있다면 유닛 데이터 지정
	if (nullptr != SelectUnit)
	{
		SetUI_UnitData();	// 유닛 정보 UI로 띄우기
		MoveSearch();	// 이동범위 탐색, 자동으로 공격범위도 탐색
		SetTile();
		MainCursor->Select();
	}

	BattleUI->SetTerrain(GetTerrain(MainCursor->WorldPos));
}

void BattleLevel::SelectUpdate(float _DeltaTime)
{
	if (true == IsMouseOn)
	{
		CursorMoveMouse();
	}
	else
	{
		CursorMove();	// 커서 이동
		if (true == IsMouseOn)
		{
			return;
		}
	}
	UnitSelect();	// 유닛 선택 동작들 처리
	CameraUpdate(_DeltaTime);
}

void BattleLevel::SelectEnd()
{
	// Select State 종료시 끄는 UI
	BattleUI->AllOff();
}

void BattleLevel::MoveStart()
{

	if (nullptr == SelectUnit)
	{
		MsgAssert("유닛 선택되지 않은 채 MoveState로 변경되었습니다.");
	}

	BeforePos = SelectUnit->GetMapPos();	// 이동 전 위치

	// 선택한 유닛이 없을때 기준 적 타일 체크
	SelectUnit->SetIsDie(true);
	EnemyTileCheck();
	SelectUnit->SetIsDie(false);

	MoveSearch();	// 이동범위 탐색, 자동으로 공격범위도 탐색

	SetTile();

	// Move State시 필요한 UI
	MainCursor->On();
	MainCursor->Idle();

	// 유닛 선택 애니메이션
	SelectUnit->Select();

	Arrows->On();

	if (0 < BeforePos.GetDistance(MainCursor->WorldPos))
	{
		return;
	}

	// 이동 화살표 초기화
	ArrowPos.clear();
	ArrowPos.push_back(SelectUnit->GetMapPos());	// 엑터 위치에서부터 화살표 시작
	AddArrow(ArrowPos.front());

	BattleUI->AllOff();
}

void BattleLevel::MoveUpdate(float _DeltaTime)
{

	if (true == IsMouseOn)
	{
		CursorAndArrowMoveMouse();
	}
	else
	{
		CursorAndArrowMove();	// 커서 이동 및 화살표 추가
	}

	CameraUpdate(_DeltaTime);

	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		// A버튼 (Z키) 입력시 유닛을 커서 위치로 이동
		UnitMove();
		return;
	}
	if (GameEngineInput::IsDown("ButtonB"))
	{
		// 커서를 선택한 유닛위치로 돌려놓은 후 Select State로 변경
		MainCursor->SetCursorPos(SelectUnit->GetMapPos());
		CameraSetPos();
		SelectUnit->SetIdle();
		ChangeState(BattleState::Select);
		return;
	}
	if (GameEngineInput::IsDown("RightClick"))
	{
		// 커서를 선택한 유닛위치로 돌려놓은 후 Select State로 변경
		SelectUnit->SetIdle();
		ChangeState(BattleState::Select);
		return;
	}
}

void BattleLevel::MoveEnd()
{
	// Move State 종료시 화살표와 이동타일을 제거
	Arrows->Off();
	Tiles->Clear();
	//SelectUnit->SetIdle();
	BattleUI->AllOff();
}

void BattleLevel::MoveWaitStart()
{
	// MoveWait State가 시작시 값을 초기화
	MainCursor->Off();
	MoveIndex = 0;
	SelectUnit->SetBeforeMapPos();
	SelectUnit->SetMapPosLerp(ArrowPos[0]);
}

void BattleLevel::MoveWaitUpdate(float _DeltaTime)
{
	if (true == UnitMoveAnim())
	{
		// 이동 종료
		ChangeState(BattleState::UnitCommand);
	}
}

void BattleLevel::MoveWaitEnd()
{
	// 정확한 위치로 다시 지정
	SelectUnit->SetMapPos(MainCursor->WorldPos);
	Terrain TerrainData = MainMap->TerrainData[SelectUnit->GetMapPos().y][SelectUnit->GetMapPos().x];
	SelectUnit->SetTerrain(TerrainData);
}

void BattleLevel::UnitCommandStart()
{
	CursorDirCheck();

	// 이동한 위치 기준으로 적 타일 체크
	EnemyTileCheck();

	// 현재 위치에 점령 목표가 있을 시
	if (ClearTarget == BattleClearTarget::Conquer && SelectUnit->GetMapPos() == ConquerPos)
	{
		BattleUI->UnitCommandOn();
		BattleUI->UnitCommandConquer();
		return;
	}

	// IsMove를 현재 위치만 true로 변경
	for (int y = 0; y < IsMove.size(); y++)
	{
		for (int x = 0; x < IsMove[y].size(); x++)
		{
			IsMove[y][x] = false;
		}
	}
	IsMove[SelectUnit->GetMapPos().y][SelectUnit->GetMapPos().x] = true;

	// 힐러 클래스일 경우
	if (SelectUnit->GetUnitData().GetClassValue() == BattleClass::Cleric)
	{
		AttackSearch();
		Tiles->SetTileHeal(IsAttack);
		bool IsCloseUnit = false;
		bool IsItem = false;

		// 근처에 아군 유닛이 있는지 판단
		CloseUnits.clear();
		for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
		{
			if (true == _Unit->GetIsDie()) { continue; }
			if (SelectUnit->GetUnitCode() == _Unit->GetUnitCode()) { continue; }

			int2 UnitPos = SelectUnit->GetMapPos();
			int2 _UnitPos = _Unit->GetMapPos();

			if (_UnitPos == UnitPos + int2::Up)
			{
				CloseUnits.push_back(_Unit);
				continue;
			}
			if (_UnitPos == UnitPos + int2::Down)
			{
				CloseUnits.push_back(_Unit);
				continue;
			}
			if (_UnitPos == UnitPos + int2::Left)
			{
				CloseUnits.push_back(_Unit);
				continue;
			}
			if (_UnitPos == UnitPos + int2::Right)
			{
				CloseUnits.push_back(_Unit);
				continue;
			}
		}

		// 근처에 아군 유닛이 있을때
		if (1 <= CloseUnits.size())
		{
			IsCloseUnit = true;
		}

		if (0 != SelectUnit->GetUnitData().GetItems().size())
		{
			IsItem = true;
		}
		// 커맨드 UI 켜기
		BattleUI->UnitCommandOn();
		BattleUI->UnitCommandHealSet(IsCloseUnit, IsItem);
		return;
	}
	// 활은 별도의 범위계산이 필요
	if (SelectUnit->GetUnitData().GetWeaponTypeValue() == WeaponType::Bow)
	{
		AttackSearchBow();
	}
	else
	{
		AttackSearch();
	}
	Tiles->SetTileAttack(IsAttack);


	bool IsAttackable = false;
	bool IsCloseUnit = false;
	bool IsItem = false;

	// 공격 범위 이내에 적이 있는지 판단
	AttackableUnits.clear();
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		int2 EnemyPos = _Unit->GetMapPos();
		if (true == IsAttack[EnemyPos.y][EnemyPos.x] && true == SelectUnit->IsAttackable(EnemyPos))
		{
			// 공격 범위 내의 적을 발견 시 리스트 저장
			AttackableUnits.push_back(_Unit);
		}
	}

	// 공격 가능한 적이 있을때
	if (1 <= AttackableUnits.size())
	{
		IsAttackable = true;
	}

	// 근처에 아군 유닛이 있는지 판단
	CloseUnits.clear();
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		if (SelectUnit->GetUnitCode() == _Unit->GetUnitCode()) { continue; }

		int2 UnitPos = SelectUnit->GetMapPos();
		int2 _UnitPos = _Unit->GetMapPos();

		if (_UnitPos == UnitPos + int2::Up)
		{
			CloseUnits.push_back(_Unit);
			continue;
		}
		if (_UnitPos == UnitPos + int2::Down)
		{
			CloseUnits.push_back(_Unit);
			continue;
		}
		if (_UnitPos == UnitPos + int2::Left)
		{
			CloseUnits.push_back(_Unit);
			continue;
		}
		if (_UnitPos == UnitPos + int2::Right)
		{
			CloseUnits.push_back(_Unit);
			continue;
		}
	}

	// 근처에 아군 유닛이 있을때
	if (1 <= CloseUnits.size())
	{
		IsCloseUnit = true;
	}

	if (0 != SelectUnit->GetUnitData().GetItems().size())
	{
		IsItem = true;
	}

	// 커맨드 UI 켜기
	BattleUI->UnitCommandOn();
	BattleUI->UnitCommandSet(IsAttackable, IsCloseUnit, IsItem);

	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	Window->Text = "";
	if (true == IsAttackable)
	{
		Window->Text += "공격\n";
	}
	Window->Text += "소지품\n";

	if (true == IsCloseUnit)
	{
		Window->Text += "교환\n";
	}
	Window->Text += "대기\n";
}

void BattleLevel::UnitCommandUpdate(float _DeltaTime)
{

}

void BattleLevel::UnitCommandEnd()
{
	Tiles->Clear();
	SelectUnit->SetIdle();
	BattleUI->AllOff();
}

void BattleLevel::FieldCommandStart()
{
	//UI_UnitCommand->SetCommand(false, false);
	BattleUI->FieldCommandOn();
	MainCursor->Off();

	// 커맨드 UI 켜기
	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	Window->Text = "시간석\n부대\n설정\n중단\n종료";
}

void BattleLevel::FieldCommandUpdate(float _DeltaTime)
{
}

void BattleLevel::FieldCommandEnd()
{
	//UI_FieldCommand->Off();
	BattleUI->AllOff();
	MainCursor->On();
}

void BattleLevel::BattleStart()
{
	AttackRecord = UnitCommand::Attack(SelectUnit, TargetUnit);
	BattleAnimationLevel::SetBattleData(SelectUnit, TargetUnit, AttackRecord, GetName());

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	MainMap->GetRenderer()->SetIsBlur(true);
	BattleUI->SetFadeOut(0.3f);
	BeforeCamPos = MainCamera->GetTransform()->GetLocalPosition();
	MainCamera->SetProjectionType(CameraType::Perspective);

	return;
}

void BattleLevel::BattleUpdate(float _DeltaTime)
{
	static float CloseUpTimer = 0;
	CloseUpTimer += _DeltaTime;
	if (0.5f < CloseUpTimer)
	{
		CloseUpTimer = 0;
		GameEngineCore::ChangeLevel("BattleAnimationLevel");

		ChangeState(BattleState::BattleReturn);
		return;
	}

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	MainMap->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	MainCamera->GetTransform()->SetLocalPosition(float4::LerpClamp(MainCamera->GetTransform()->GetWorldPosition(), TargetUnit->GetTransform()->GetWorldPosition(), _DeltaTime * 5));
}

void BattleLevel::BattleEnd()
{
	SelectUnit->SetIsTurnEnd(true);
	if (SelectUnit->GetIsDie())
	{
		SelectUnit->Off();
		SelectUnit = nullptr;
	}
	if (TargetUnit->GetIsDie())
	{
		TargetUnit->Off();
		TargetUnit = nullptr;
	}
	MainCursor->SetCursorPos(SelectUnit->GetMapPos());
}

void BattleLevel::BattleReturnStart()
{
	BattleUI->SetFadeIn(0.3f);
}

void BattleLevel::BattleReturnUpdate(float _DeltaTime)
{
	static float ReturnTimer = 0;
	ReturnTimer += _DeltaTime;

	if (0.5f < ReturnTimer)
	{
		ReturnTimer = 0;
		if (AttackRecord.size() != 0)
		{
			SelectUnit->SetUnitData(Unit(AttackRecord.back().SubjectUnit));
			TargetUnit->SetUnitData(Unit(AttackRecord.back().TargetUnit));
		}
		if (false == GameOverCheck())
		{
			ChangeState(BattleState::Select);
		}
		return;
	}

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(2.5f - ReturnTimer * 5);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(2.5f - ReturnTimer * 5);
	}
	MainMap->GetRenderer()->SetBlurLevel(2.5f - ReturnTimer * 5);
	MainCamera->GetTransform()->SetLocalPosition(float4::LerpClamp(MainCamera->GetTransform()->GetWorldPosition(), BeforeCamPos, _DeltaTime * 10));

}

void BattleLevel::BattleReturnEnd()
{
	AttackRecord.clear();
	SelectUnit->SetIsTurnEnd(true);
	if (SelectUnit->GetIsDie())
	{
		SelectUnit->Off();
		SelectUnit = nullptr;
	}
	if (nullptr != TargetUnit && TargetUnit->GetIsDie())
	{
		TargetUnit->Off();
		TargetUnit = nullptr;
	}

	MainCamera->GetTransform()->SetLocalPosition(BeforeCamPos);
	MainCamera->SetProjectionType(CameraType::Orthogonal);

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
	}
	MainMap->GetRenderer()->SetIsBlur(false);
}

void BattleLevel::HealStart()
{
	AttackRecord = UnitCommand::Heal(SelectUnit, TargetUnit, UseItem);
	BattleAnimationLevel::SetBattleData(SelectUnit, TargetUnit, AttackRecord, GetName());

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	MainMap->GetRenderer()->SetIsBlur(true);
	BattleUI->SetFadeOut(0.3f);
	BeforeCamPos = MainCamera->GetTransform()->GetLocalPosition();
	MainCamera->SetProjectionType(CameraType::Perspective);

	return;
}
void BattleLevel::HealUpdate(float _DeltaTime)
{
	static float CloseUpTimer = 0;
	CloseUpTimer += _DeltaTime;
	if (0.5f < CloseUpTimer)
	{
		CloseUpTimer = 0;
		GameEngineCore::ChangeLevel("BattleAnimationLevel");

		ChangeState(BattleState::BattleReturn);
		return;
	}

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	MainMap->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	MainCamera->GetTransform()->SetLocalPosition(float4::LerpClamp(MainCamera->GetTransform()->GetWorldPosition(), TargetUnit->GetTransform()->GetWorldPosition(), _DeltaTime * 5));
}
void BattleLevel::HealEnd()
{
	SelectUnit->SetIsTurnEnd(true);
	if (SelectUnit->GetIsDie())
	{
		SelectUnit->Off();
		SelectUnit = nullptr;
	}
	if (TargetUnit->GetIsDie())
	{
		TargetUnit->Off();
		TargetUnit = nullptr;
	}
}

void BattleLevel::EnemyPhaseStart()
{

	UnitCommand::PhaseStart(Faction::Enemy);

	IsSkip = false;

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		_Unit->SetIsTurnEnd(false);
		_Unit->SetIdle();
	}

	bool AliveUnit = false;
	for (std::shared_ptr<BattleUnit> _Enemy : EnemyUnits)
	{
		if (true == _Enemy->GetIsDie()) { continue; }
		AliveUnit = true;
		break;
	}
	if (false == AliveUnit)
	{
		ChangeState(BattleState::PlayerPhase);
		return;
	}

	MainCursor->Off();
	Tiles->EnemyTileClear();

	// 지형에 따른 체력회복
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (true == _Unit->GetIsDie()) { continue; }
		switch (_Unit->GetUnitData().GetTerrainData())
		{
		case Terrain::Fort:
			_Unit->GetUnitData().RecoverPersent(0.2f);
			break;
		case Terrain::Gate:
			_Unit->GetUnitData().RecoverPersent(0.1f);
			break;
		default:
			break;
		}
	}
	BattleUI->PhaseOn(Faction::Enemy);
}

void BattleLevel::EnemyPhaseUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsDown("Start"))
	{
		IsSkip = true;
		BattleUI->SetFadeIn(0.2f);
		BattleUI->SetFadeWait(0.3f);
		BattleUI->PhaseOff();
		ChangeState(BattleState::EnemySelect);
		return;
	}
	if (true == BattleUI->IsPhaseEnd())
	{
		ChangeState(BattleState::EnemySelect);
	}
}

void BattleLevel::EnemyPhaseEnd()
{
}

void BattleLevel::EnemySelectStart()
{

	for (std::shared_ptr<BattleUnit> _Enemy : EnemyUnits)
	{
		if (true == _Enemy->GetIsDie()) { continue; }
		if (true == _Enemy->GetIsTurnEnd()) { continue; }

		if (_Enemy->GetDetectionRange() != 0)
		{
			bool Check = false;
			for (std::shared_ptr<BattleUnit> _Player : PlayerUnits)
			{
				if (true == _Player->GetIsDie()) { continue; }
				int Distance = _Enemy->GetMapPos().GetDistance(_Player->GetMapPos());
				if (Distance <= _Enemy->GetDetectionRange())
				{
					Check = true;
					break;
				}
			}
			if (false == Check) { continue; }
		}

		SelectUnit = _Enemy;
		SelectUnit->Select();
		MainCursor->SetCursorPos(_Enemy->GetMapPos());
		CameraSetPos();
		CameraUnit->SetMoveSpeed(5.0f);

		return;
	}
	ChangeState(BattleState::PlayerPhase);
}

void BattleLevel::EnemySelectUpdate(float _DeltaTime)
{
	CameraUpdate(_DeltaTime);
	static float EnemySelectTimer = 0;
	EnemySelectTimer += _DeltaTime;
	if (0.5f < EnemySelectTimer)
	{
		EnemySelectTimer = 0;
		ChangeState(BattleState::EnemyMove);
		return;
	}

	if (false == IsSkip && GameEngineInput::IsDown("Start"))
	{
		IsSkip = true;
		BattleUI->SetFadeIn(0.2f);
		BattleUI->SetFadeWait(0.3f);
	}
	if (true == IsSkip)
	{
		ChangeState(BattleState::EnemyMove);
		return;
	}
}

void BattleLevel::EnemySelectEnd()
{
	CameraUnit->SetMoveSpeed(15.0f);
}

void BattleLevel::EnemyMoveStart()
{
	int2 EnemyPos = SelectUnit->GetMapPos();
	SelectUnit->SetBeforeMapPos();
	int Min = 9999;

	MoveSearchForEnemy();
	EnemyFindTarget();

	if (TargetUnit == nullptr)
	{
		// 공격범위 내의 적이 없음
		// 최대한 적과 가까워질 방법을 찾는다

		int2 MovePos = SelectUnit->GetMapPos();
		int MinDistance = 99;
		for (int y = 0; y < IsMove.size(); y++)
		{
			for (int x = 0; x < IsMove[y].size(); x++)
			{
				if (false == IsMove[y][x])
				{
					continue;
				}
				int2 Pos = { x, y };
				for (std::shared_ptr<BattleUnit> _Player : PlayerUnits)
				{
					if (true == _Player->GetIsDie()) { continue; }
					int Distance = Pos.GetDistance(_Player->GetMapPos());
					if (Distance < MinDistance)
					{
						MovePos = Pos;
						MinDistance = Distance;
					}
				}
			}
		}
		MainCursor->SetCursorPos(MovePos);
		CameraSetPos();
		ArrowPos.clear();
		TargetSearchForEnemy();
		MoveIndex = 0;
		return;
	}

	// 공격범위내 적 포착
	MainCursor->SetCursorPos(TargetUnit->GetMapPos());
	ArrowPos.clear();
	MoveCalculationForEnemyAttack();
	MoveIndex = 0;

	MainCursor->SetCursorPos(TargetUnit->GetMapPos());
	MainCursor->On();
	MainCursor->Enemy();
	CameraSetPos();
	if (ArrowPos.size() == 0)
	{
		MoveIndex = -1;
		return;
	}
	int2 MovePos = ArrowPos.back();

}

void BattleLevel::EnemyMoveUpdate(float _DeltaTime)
{
	CameraUpdate(_DeltaTime);
	if (false == IsSkip && GameEngineInput::IsDown("Start"))
	{
		IsSkip = true;
		BattleUI->SetFadeIn(0.2f);
		BattleUI->SetFadeWait(0.3f);
	}
	if (true == IsSkip)
	{
		ChangeState(BattleState::EnemyBattle);
		return;
	}
	if (true == UnitMoveAnim())
	{
		ChangeState(BattleState::EnemyBattle);
	}
}

void BattleLevel::EnemyMoveEnd()
{
	MainCursor->Off();
	MainCursor->Idle();

	if (ArrowPos.size() != 0)
	{
		SelectUnit->SetMapPos(ArrowPos.back());
	}
	Terrain TerrainData = MainMap->TerrainData[SelectUnit->GetMapPos().y][SelectUnit->GetMapPos().x];
	SelectUnit->SetTerrain(TerrainData);
	SelectUnit->SetIdle();
}

void BattleLevel::EnemyBattleStart()
{
	if (nullptr != TargetUnit)
	{
		AttackRecord = UnitCommand::Attack(SelectUnit, TargetUnit);
		BattleAnimationLevel::SetBattleData(SelectUnit, TargetUnit, AttackRecord, GetName());
	}
	else
	{
		UnitCommand::Wait(SelectUnit);
		SelectUnit->SetIsTurnEnd(true);
		ChangeState(BattleState::EnemySelect);
		return;
	}

	BeforeCamPos = MainCamera->GetTransform()->GetLocalPosition();

	if (true == IsSkip)
	{
		return;
	}
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	BattleUI->SetFadeOut(0.3f);
	MainMap->GetRenderer()->SetIsBlur(true);
	MainCamera->SetProjectionType(CameraType::Perspective);

}

void BattleLevel::EnemyBattleUpdate(float _DeltaTime)
{
	static float CloseUpTimer = 0;
	CloseUpTimer += _DeltaTime;
	if (0.5f < CloseUpTimer || true == IsSkip)
	{
		CloseUpTimer = 0;
		if (false == IsSkip)
		{
			GameEngineCore::ChangeLevel("BattleAnimationLevel");
		}
		ChangeState(BattleState::EnemyBattleReturn);
		return;
	}

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	MainMap->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	MainCamera->GetTransform()->SetLocalPosition(float4::LerpClamp(MainCamera->GetTransform()->GetWorldPosition(), TargetUnit->GetTransform()->GetWorldPosition(), _DeltaTime * 5));
}

void BattleLevel::EnemyBattleEnd()
{
}

void BattleLevel::EnemyBattleReturnStart()
{
	if (false == IsSkip)
	{
		BattleUI->SetFadeIn(0.3f);
	}
}

void BattleLevel::EnemyBattleReturnUpdate(float _DeltaTime)
{
	static float ReturnTimer = 0;
	ReturnTimer += _DeltaTime;

	if (0.5f < ReturnTimer || true == IsSkip)
	{
		ReturnTimer = 0;
		SelectUnit->SetUnitData(Unit(AttackRecord.back().SubjectUnit));
		TargetUnit->SetUnitData(Unit(AttackRecord.back().TargetUnit));
		if (false == GameOverCheck())
		{
			ChangeState(BattleState::EnemySelect);
		}
		return;
	}

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(2.5f - ReturnTimer * 5);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(2.5f - ReturnTimer * 5);
	}
	MainMap->GetRenderer()->SetBlurLevel(2.5f - ReturnTimer * 5);
	MainCamera->GetTransform()->SetLocalPosition(float4::LerpClamp(MainCamera->GetTransform()->GetWorldPosition(), BeforeCamPos, _DeltaTime * 10));

}

void BattleLevel::EnemyBattleReturnEnd()
{
	AttackRecord.clear();
	SelectUnit->SetIsTurnEnd(true);
	if (SelectUnit->GetIsDie())
	{
		SelectUnit->Off();
		SelectUnit = nullptr;
	}
	if (nullptr != TargetUnit && TargetUnit->GetIsDie())
	{
		TargetUnit->Off();
		TargetUnit = nullptr;
	}

	MainCamera->GetTransform()->SetLocalPosition(BeforeCamPos);
	MainCamera->SetProjectionType(CameraType::Orthogonal);

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
	}
	MainMap->GetRenderer()->SetIsBlur(false);
}

void BattleLevel::InformationStart()
{
	Tiles->Clear();
	FEffect->FadeIn(0.1f);
	MainCursor->Off();
	InfoUI->On();
	InfoUI->SetUnit(SelectUnit);
}

void BattleLevel::InformationUpdate(float _DeltaTime)
{
}

void BattleLevel::InformationEnd()
{
	FEffect->FadeIn(0.1f);
	MainCursor->On();
	InfoUI->Off();
}

static std::list<UnitCommand> Command;
static std::list<UnitCommand>::reverse_iterator RIter;
static std::list<UnitCommand>::reverse_iterator RIterEnd;

void BattleLevel::GameOverStart()
{
	Command = UnitCommand::GetCommandList();
	RIter = Command.rbegin();
	RIterEnd = Command.rend();
}
void BattleLevel::GameOverUpdate(float _DeltaTime)
{
	static float Timer = 0;
	Timer += _DeltaTime;

	if (1.0f < Timer)
	{
		Timer = 0;


		if (RIter != RIterEnd)
		{
			switch (RIter->TypeValue)
			{
			case CommandType::Attack:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
					else if ((*RIter).BeforeTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeTargetUnit);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
					else if ((*RIter).BeforeTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeTargetUnit);
					}
				}
			}
			break;
			case CommandType::Item:
				break;
			case CommandType::Wait:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}
			}
			break;
			default:
				break;
			}
			FERandom::AddRandomCount(-(*RIter).RandomNum);
			int randc = FERandom::GetRandomCount();
			RIter++;
		}
		else
		{
			UnitCommand::ResetCommandList();
			ChangeState(BattleState::PlayerPhase);
			return;
		}
	}
}

void BattleLevel::GameOverEnd()
{
}

float EffectTimer = 0;
float MapEffectTimer = 0;
int RewindNum = 0;
enum TimeStoneState
{
	EffectIn,
	EffectOut,
	Control
};
TimeStoneState CurTimeStoneState = EffectIn;

void BattleLevel::TimeStoneStart()
{
	EffectTimer = 0;
	MapEffectTimer = 0;
	CurTimeStoneState = EffectIn;
	RewindNum = 0;

	Tiles->Clear();
	MainCursor->Off();
	Command = UnitCommand::GetCommandList();
	RIter = Command.rbegin();
	RIterEnd = Command.rend();

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	MainMap->GetRenderer()->SetIsBlur(true);

}

void BattleLevel::TimeStoneUpdate(float _DeltaTime)
{
	EffectTimer += _DeltaTime;
	MapEffectTimer += _DeltaTime * 2;

	if (MapEffectTimer < 0.7f) {
		MainMap->GetRenderer()->SetLerp({ 0.3f, 0.0f, 0.6f }, MapEffectTimer);
		MainMap->GetRenderer()->SetBlurLevel(MapEffectTimer * 2.0f);
	}

	switch (CurTimeStoneState)
	{
	case EffectIn:
	{
		if (0.05 < EffectTimer)
		{
			CurTimeStoneState = EffectOut;
			return;
		}
		for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
		{
			_Unit->GetRenderer()->SetBlurLevel(EffectTimer * 200);
			_Unit->GetRenderer()->SetLerp({ 1, 1, 1 }, EffectTimer * 200);
		}
		for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
		{
			_Unit->GetRenderer()->SetBlurLevel(EffectTimer * 200);
			_Unit->GetRenderer()->SetLerp({ 1, 1, 1 }, EffectTimer * 200);
		}

		break;
	}
	case EffectOut:
	{
		if (1.0f < EffectTimer)
		{
			for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
			{
				_Unit->GetRenderer()->OffLerp();
			}
			for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
			{
				_Unit->GetRenderer()->OffLerp();
			}

			CurTimeStoneState = Control;
			return;
		}
		for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
		{
			_Unit->GetRenderer()->SetBlurLevel(10.f - EffectTimer * 10);
			_Unit->GetRenderer()->SetLerp({ 1, 1, 1 }, 1.f - EffectTimer);
		}
		for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
		{
			_Unit->GetRenderer()->SetBlurLevel(10.f - EffectTimer * 10);
			_Unit->GetRenderer()->SetLerp({ 1, 1, 1 }, 1.f - EffectTimer);
		}
		break;
	}
	case Control:
	{
		if (GameEngineInput::IsDown("Up") || GameEngineInput::IsUp("MiddleClick"))
		{
			if (RIter == RIterEnd) {
				return;
			}
			if (RewindNum + 1 == Command.size())
			{
				return;
			}
			RewindNum++;
			FERandom::AddRandomCount(-(*RIter).RandomNum);

			switch (RIter->TypeValue)
			{
			case CommandType::Attack:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
						_Unit->GetUnitData().LoadItemData((*RIter).BeforeSubjectItems);
					}
					else if ((*RIter).BeforeTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeTargetUnit);
						_Unit->GetUnitData().LoadItemData((*RIter).BeforeTargetItems);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
						_Unit->GetUnitData().LoadItemData((*RIter).BeforeSubjectItems);
					}
					else if ((*RIter).BeforeTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeTargetUnit);
						//_Unit->GetUnitData().LoadItemData((*RIter).BeforeTargetItems);
					}
				}
				break;
			}
			case CommandType::Item:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
						_Unit->GetUnitData().LoadItemData((*RIter).BeforeSubjectItems);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
						_Unit->GetUnitData().LoadItemData((*RIter).BeforeSubjectItems);
					}
				}
				break;
			}
			case CommandType::Wait:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).BeforeSubjectUnit);
						_Unit->SetMapPos((*RIter).BeforeSubjectUnitPos);
					}
				}

				break;
			}
			case CommandType::EnemyPhaseStart:
			{
				static std::list<UnitCommand>::reverse_iterator NewRIter;
				NewRIter = RIter;
				//NewRIter++;
				while (NewRIter != RIterEnd)
				{
					if ((*NewRIter).TypeValue == CommandType::PlayerPhaseStart)
					{
						break;
					}

					for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
					{
						if ((*NewRIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitCode())
						{
							_Unit->SetIsTurnEnd(true);
							break;
						}
					}
					NewRIter++;
				}
				break;
			}
			case CommandType::PlayerPhaseStart:
			{
				static std::list<UnitCommand>::reverse_iterator NewRIter;
				NewRIter = RIter;

				//NewRIter++;
				while (NewRIter != RIterEnd)
				{
					if ((*NewRIter).TypeValue == CommandType::EnemyPhaseStart)
					{

						break;
					}

					for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
					{
						if ((*NewRIter).BeforeSubjectUnit.GetUnitCode() == _Unit->GetUnitCode())
						{
							_Unit->SetIsTurnEnd(true);
							break;
						}
					}
					NewRIter++;
				}
				break;
			}

			case CommandType::None:
			{
				MsgAssert("커맨드 타입 오류");
				break;
			}
			default:
			{
				RIter;
				MsgAssert("커맨드 타입 오류");
				break;
			}
			}

			RIter++;


			return;
		}
		if (GameEngineInput::IsDown("Down"))
		{
			if (RIter == Command.rbegin()) {
				return;
			}
			RIter--;
			RewindNum--;
			FERandom::AddRandomCount((*RIter).RandomNum);

			switch (RIter->TypeValue)
			{
			case CommandType::Attack:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
						_Unit->GetUnitData().LoadItemData((*RIter).AfterSubjectItems);
					}
					else if ((*RIter).AfterTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterTargetUnit);
						_Unit->GetUnitData().LoadItemData((*RIter).AfterTargetItems);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
						_Unit->GetUnitData().LoadItemData((*RIter).AfterSubjectItems);
					}
					else if ((*RIter).AfterTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterTargetUnit);
						_Unit->GetUnitData().LoadItemData((*RIter).AfterTargetItems);
					}
				}
				break;
			}
			case CommandType::Item:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
						_Unit->GetUnitData().LoadItemData((*RIter).AfterSubjectItems);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
						_Unit->GetUnitData().LoadItemData((*RIter).AfterSubjectItems);
					}
				}
				break;
			}
			case CommandType::Wait:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
				}
				break;
			}
			case CommandType::PlayerPhaseStart:
			case CommandType::EnemyPhaseStart:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					_Unit->SetIsTurnEnd(false);
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					_Unit->SetIsTurnEnd(false);
				}
				break;
			}
			case CommandType::None:
			{
				MsgAssert("커맨드 타입 오류");
				break;
			}
			default:
			{
				MsgAssert("커맨드 타입 오류");
				break;
			}
			}

			return;
		}
		break;
	}
	default:
		break;
	}


	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		for (int i = 0; i < RewindNum; i++)
		{
			UnitCommand::PopCommandList();
		}
		ChangeState(BattleState::Select);
		return;
	}
	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		while (RIter != Command.rbegin()) {
			RIter--;
			RewindNum--;
			FERandom::AddRandomCount((*RIter).RandomNum);

			switch (RIter->TypeValue)
			{
			case CommandType::Attack:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
					else if ((*RIter).AfterTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterTargetUnit);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
					else if ((*RIter).AfterTargetUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterTargetUnit);
					}
				}
				break;
			}
			case CommandType::Item:
				break;
			case CommandType::Wait:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					if ((*RIter).AfterSubjectUnit.GetUnitCode() == _Unit->GetUnitData().GetUnitCode())
					{
						_Unit->SetUnitData((*RIter).AfterSubjectUnit);
						_Unit->SetMapPos((*RIter).AfterSubjectUnitPos);
					}
				}
				break;
			}
			case CommandType::PlayerPhaseStart:
			case CommandType::EnemyPhaseStart:
			{
				for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
				{
					_Unit->SetIsTurnEnd(false);
				}
				for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
				{
					_Unit->SetIsTurnEnd(false);
				}
				break;
			}
			case CommandType::None:
			{
				MsgAssert("커맨드 타입 오류");
				break;
			}
			default:
			{
				MsgAssert("커맨드 타입 오류");
				break;
			}
			}
		}
		ChangeState(BattleState::Select);
		return;
	}
	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	{
		if (nullptr == Window)
		{
			MsgAssert("윈도우 테스트 코드 미작동");
		}
		Window->Text = "";
		size_t i = Command.size();
		for (UnitCommand _Command : Command)
		{
			Window->Text += _Command.Record;
			if (RewindNum == --i)
			{
				Window->Text += " <";
			}
			Window->Text += '\n';
		}
	}
}

void BattleLevel::TimeStoneEnd()
{
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
		_Unit->GetRenderer()->OffLerp();
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(false);
		_Unit->GetRenderer()->OffLerp();
	}
	MainMap->GetRenderer()->OffLerp();
	MainMap->GetRenderer()->SetIsBlur(false);
}

bool BattleLevel::GameOverCheck()
{
	// 주인공 유닛(린)이 죽었는지 체크
	bool IsAliveUnit = false;
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (UnitIdentityCode::Lyn == _Unit->GetUnitData().GetIdentityCode() || UnitIdentityCode::BladeLordLyn == _Unit->GetUnitData().GetIdentityCode())
		{
			IsAliveUnit = true;
			break;
		}
	}
	if (false == IsAliveUnit)
	{
		// 게임오버
		ChangeState(BattleState::TimeStone);
		return true;
	}

	if (ClearTarget != BattleClearTarget::AllKill) { return false; }
	// 적 전멸이 클리어 목표일때
	// 적 유닛이 모두 죽었는지 체크
	IsAliveUnit = false;
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (false == _Unit->GetIsDie())
		{
			IsAliveUnit = true;
		}
	}
	if (false == IsAliveUnit)
	{
		ChangeState(BattleState::Clear);
		return true;
	}

	return false;
}

void BattleLevel::OpeningStart()
{
	OpeningEvent->EventStart();
}

void BattleLevel::OpeningUpdate(float _DeltaTime)
{
	if (true == OpeningEvent->GetIsEnd())
	{
		ChangeState(BattleState::PlayerPhase);
	}
}

void BattleLevel::OpeningEnd()
{
	OpeningEvent->Off();
}

void BattleLevel::PotionStart()
{
	BattleUI->AllOff();
	BattleUI->PotionUIOn();
	BattleUI->SetUnitData(SelectUnit);
	UnitCommand::ItemUse(SelectUnit, UseItem);
	BattleUI->SetHPLerp(SelectUnit->GetUnitData().GetHP());
	SelectUnit->SetIsTurnEnd(true);
}

void BattleLevel::PotionUpdate(float _DeltaTime)
{
	static float PotionTimer = 0;
	PotionTimer += _DeltaTime;

	if (2 < PotionTimer)
	{
		PotionTimer = 0;
		ChangeState(BattleState::Select);
		return;
	}
}

void BattleLevel::PotionEnd()
{
	BattleUI->PotionUIOff();
}

void BattleLevel::EnemyPotionStart()
{
}

void BattleLevel::EnemyPotionUpdate(float _DeltaTime)
{
}

void BattleLevel::EnemyPotionEnd()
{
}

void BattleLevel::ClearStart()
{
	BattleUI->AllOff();
	MainCursor->Off();
	ClearEvent->EventStart();
}
void BattleLevel::ClearUpdate(float _DeltaTime)
{
}
void BattleLevel::ClearEnd()
{

}

void BattleLevel::ClassChangeStart()
{
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetIsBlur(true);
	}
	MainMap->GetRenderer()->SetIsBlur(true);
	BattleUI->SetFadeOut(0.3f);
	BeforeCamPos = MainCamera->GetTransform()->GetLocalPosition();
	MainCamera->SetProjectionType(CameraType::Perspective);

	return;
}

void BattleLevel::ClassChangeUpdate(float _DeltaTime)
{
	static float CloseUpTimer = 0;
	CloseUpTimer += _DeltaTime;
	if (0.5f < CloseUpTimer)
	{
		CloseUpTimer = 0;
		GameEngineCore::ChangeLevel("BattleAnimationLevel");

		ChangeState(BattleState::BattleReturn);
		return;
	}

	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		_Unit->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	}
	MainMap->GetRenderer()->SetBlurLevel(CloseUpTimer * 5);
	MainCamera->GetTransform()->SetLocalPosition(float4::LerpClamp(MainCamera->GetTransform()->GetWorldPosition(), SelectUnit->GetTransform()->GetWorldPosition(), _DeltaTime * 5));
}

void BattleLevel::ClassChangeEnd()
{
	//SelectUnit->SetUnitData(Unit(UnitCommand::GetCommandList().back().AfterSubjectUnit));
}
