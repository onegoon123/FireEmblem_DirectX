#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MapCursor;
class UICursor;
class GameEngineUIRenderer;
class BattleLevel;
class Weapon;
class BattleUnit;
class AttackUI : public GameEngineActor
{
public:
	// constrcuter destructer
	AttackUI();
	~AttackUI();

	// delete Function
	AttackUI(const AttackUI& _Other) = delete;
	AttackUI(AttackUI&& _Other) noexcept = delete;
	AttackUI& operator=(const AttackUI& _Other) = delete;
	AttackUI& operator=(AttackUI&& _Other) noexcept = delete;

	void Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor);
	void On(std::shared_ptr<BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits);
	//void On();
	void Off();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	void WeaponSelectStart();
	void WeaponSelectUpdate(float _DeltaTime);
	void WeaponSelectEnd();
	void SetWeapon();
	void TargetSelectStart();
	void TargetSelectUpdate(float _DeltaTime);
	void TargetSelectEnd();
	void SetTarget();
	BattleLevel* LevelPtr = nullptr;
	std::function<void(std::shared_ptr<BattleUnit>)> AttackFunction;
	std::function<void()> CancelFunction;

	std::shared_ptr<MapCursor> Cursor_Map = nullptr;	// 커서
	std::shared_ptr<UICursor> Cursor_UI = nullptr;	// 커서
	std::shared_ptr<GameEngineUIRenderer> SelectRender = nullptr; // 선택배경
	std::shared_ptr<GameEngineUIRenderer> WindowRender = nullptr;	// 배경창
	std::shared_ptr<GameEngineUIRenderer> InfoRender = nullptr;	// 스탯 정보
	std::shared_ptr<GameEngineUIRenderer> Portrait = nullptr;		// 초상화
	std::shared_ptr<GameEngineUIRenderer> BattleEx = nullptr;		// 전투 예상
	std::vector<std::shared_ptr<GameEngineUIRenderer>> WeaponeIcon;
	std::vector<std::shared_ptr<class NumberActor>> WeaponUses;

	std::shared_ptr<NumberActor> WeaponDamage;
	std::shared_ptr<NumberActor>  WeaponHit;
	std::shared_ptr<NumberActor>  WeaponCritical;
	std::shared_ptr<NumberActor>  WeaponWeight;

	std::shared_ptr<GameEngineUIRenderer> SubjectWeapon;
	std::shared_ptr<GameEngineUIRenderer> SubjectTriangle;
	std::shared_ptr<GameEngineUIRenderer> TargetWeapon;
	std::shared_ptr<GameEngineUIRenderer> TargetTriangle;

	std::shared_ptr<NumberActor> SubjectHP;
	std::shared_ptr<NumberActor> SubjectDamage;
	std::shared_ptr<class DoubleIconActor> SubjectDoubleAttack;
	std::shared_ptr<NumberActor> SubjectHit;
	std::shared_ptr<NumberActor> SubjectCritical;
	std::shared_ptr<NumberActor> TargetHP;
	std::shared_ptr<NumberActor> TargetDamage;
	std::shared_ptr<class DoubleIconActor> TargetDoubleAttack;
	std::shared_ptr<NumberActor> TargetHit;
	std::shared_ptr<NumberActor> TargetCritical;


	std::shared_ptr<BattleUnit> SelectUnit = nullptr;;
	std::list<std::shared_ptr<BattleUnit>> TargetUnits;
	std::list<std::shared_ptr<Weapon>> Weapons;
	std::shared_ptr<Weapon> SelectWeapon;
	std::list<std::shared_ptr<BattleUnit>> Targets;
	std::list<std::shared_ptr<BattleUnit>>::iterator TargetIter;
	std::shared_ptr<BattleUnit> TargetUnit;

	const float4 StartCursorPos = { -432, 192 };
	const float4 StartSelectPos = { -232, 192 };
	float4 CursorPos;
	size_t CurrentCursor = 0;
	float CursorTimer = 0;

	const float PreesTime = 0.2f;
	bool PressOK = false;
	bool IsOnFrame = false;	// UI를 켠 프레임인가
	bool IsWeaponSelect = false;// 무기를 선택했는가
};

