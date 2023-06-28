#include "PrecompileHeader.h"	
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BattleAnimationLevel.h"
#include "FadeEffect.h"
#include "SpriteRenderer.h"
#include "BattleAnimationUnit.h"
#include "BattleAnimationUI.h"
#include "ContentsEnum.h"
std::shared_ptr<BattleUnit> BattleAnimationLevel::SubjectUnit = nullptr;
std::shared_ptr<BattleUnit> BattleAnimationLevel::TargetUnit = nullptr;
bool BattleAnimationLevel::IsClassChange = false;
std::list<AttackCommand> BattleAnimationLevel::BattleData = std::list<AttackCommand>();
std::list<AttackCommand>::iterator BattleAnimationLevel::BattleIter = std::list<AttackCommand>::iterator();
std::string_view BattleAnimationLevel::ReturnLevelStr = "";
BattleClass BattleAnimationLevel::ChangeClass = BattleClass::BladeLord;
GameEngineSoundPlayer BattleAnimationLevel::BgmPlayer;

BattleAnimationLevel::BattleAnimationLevel()
{
}

BattleAnimationLevel::~BattleAnimationLevel()
{
}

void BattleAnimationLevel::SetBattleData(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, const std::list<AttackCommand>& _Data, const std::string_view& _Level)
{
	IsClassChange = false;
	SubjectUnit = _SubjectUnit;
	TargetUnit = _TargetUnit;
	BattleData = _Data;
	BattleIter = BattleData.begin();
	ReturnLevelStr = _Level;

	if (SubjectUnit->GetUnitData().GetIsPlayer() && TargetUnit->GetUnitData().GetIsPlayer())
	{
		BgmPlayer = GameEngineSound::Play("HealCommand.mp3");
	}
	else if (SubjectUnit->GetIsPlayer())
	{
		BgmPlayer = GameEngineSound::Play("PlayerAttack.mp3");
	}
	else
	{
		BgmPlayer = GameEngineSound::Play("EnemyAttack.mp3");
	}
	BgmPlayer.SoundFadeIn(1.0f);
}

void BattleAnimationLevel::SetDance(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, const std::string_view& _Level)
{
	BattleData.clear();
	AttackCommand NewAttack;
	SubjectUnit = _SubjectUnit;
	TargetUnit = _TargetUnit;
	NewAttack.SubjectUnit = _SubjectUnit->GetUnitData();
	NewAttack.TargetUnit = _TargetUnit->GetUnitData();
	NewAttack.IsHit = true;
	NewAttack.SubjectAttack = true;
	NewAttack.Exp = 20;
	NewAttack.IsLevelUp = 80 <= NewAttack.SubjectUnit.GetExp();
	BattleData.push_back(NewAttack);
	BattleIter = BattleData.begin();
	ReturnLevelStr = _Level;
	IsClassChange = false;

	BgmPlayer = GameEngineSound::Play("Dance.mp3");
	BgmPlayer.SoundFadeIn(1.0f);
}

void BattleAnimationLevel::SetClassChange(std::shared_ptr<BattleUnit> _BattleUnit, BattleClass _ClassValue, const std::string_view& _Level)
{
	SubjectUnit = _BattleUnit;
	IsClassChange = true;
	ChangeClass = _ClassValue;
	ReturnLevelStr = _Level;
	BgmPlayer = GameEngineSound::Play("ClassChange.mp3");
	BgmPlayer.SoundFadeIn(1.0f);
}

void BattleAnimationLevel::HitEvent()
{
	std::shared_ptr<BattleAnimationUnit> DamageUnit = nullptr;
	std::shared_ptr<BattleUnit> AttackUnit = nullptr;
	std::string EffectName = "";

	if (true == (*BattleIter).SubjectAttack)
	{
		DamageUnit = TargetAnimation;
		AttackUnit = SubjectUnit;
		if (AttackUnit->GetUnitData().GetClassValue() == BattleClass::Mage)
		{
			TimeEvent.AddEvent(1.0f, std::bind(&BattleAnimationUI::SetDamage, UI, (*BattleIter).TargetUnit));
		}
		else if (AttackUnit->GetUnitData().GetClassValue() == BattleClass::Monk)
		{
			TimeEvent.AddEvent(0.5f, std::bind(&BattleAnimationUI::SetDamage, UI, (*BattleIter).TargetUnit));
		}
		else
		{
			UI->SetDamage((*BattleIter).TargetUnit);
		}
		if (true == (*BattleIter).TargetUnit.GetIsDie())
		{
			TimeEvent.AddEvent(1.0f, std::bind(&BattleAnimationUnit::Die, DamageUnit));
		}
	}
	else
	{
		DamageUnit = SubjectAnimation;
		AttackUnit = TargetUnit;
		if (AttackUnit->GetUnitData().GetClassValue() == BattleClass::Mage)
		{
			TimeEvent.AddEvent(1.0f, std::bind(&BattleAnimationUI::SetDamage, UI, (*BattleIter).SubjectUnit));
		}
		else
		{
			UI->SetDamage((*BattleIter).SubjectUnit);
		}
		if (true == (*BattleIter).SubjectUnit.GetIsDie())
		{
			TimeEvent.AddEvent(1.0f, std::bind(&BattleAnimationUnit::Die, DamageUnit));
		}
	}

	if (AttackUnit->GetUnitData().GetClassValue() == BattleClass::Mage)
	{
		WeaponType Type = AttackUnit->GetUnitData().GetCurWeapon()->GetWeaponTypeValue();
		if (Type == WeaponType::AnimaTome)
		{
			EffectName = "Fire";
		}
		else if (Type == WeaponType::DarkTome)
		{
			EffectName = "Flux";
		}
		// 마법사 경우 다른 이펙트

		if ((*BattleIter).IsCritical)
		{
			EffectName += "Critical";
			TimeEvent.AddEvent(0.8f, std::bind(&BattleAnimationLevel::CameraShake, this, 0.4f));
		}
		else if ((*BattleIter).IsHit)
		{
			EffectName += "Hit";
			TimeEvent.AddEvent(0.8f, std::bind(&BattleAnimationLevel::CameraShake, this, 0.2f));
			TimeEvent.AddEvent(0.8f, std::bind(&GameEngineSound::Play, "Slash1.wav"));
		}
		else
		{
			EffectName += "Dodge";
		}
	}
	else if (AttackUnit->GetUnitData().GetClassValue() == BattleClass::Monk)
	{
		EffectName = "Lightning";
		if ((*BattleIter).IsCritical)
		{
			EffectName += "Critical";
			TimeEvent.AddEvent(0.4f, std::bind(&BattleAnimationLevel::CameraShake, this, 0.4f));
		}
		else if ((*BattleIter).IsHit)
		{
			EffectName += "Hit";
			TimeEvent.AddEvent(0.4f, std::bind(&BattleAnimationLevel::CameraShake, this, 0.2f));
			TimeEvent.AddEvent(0.4f, std::bind(&GameEngineSound::Play, "Slash1.wav"));
		}
		else
		{
			EffectName += "Dodge";
		}
	}
	else if ((*BattleIter).IsCritical)
	{
		EffectName += "Critical";
		CameraShake(0.4f);
	}
	else if ((*BattleIter).IsHit)
	{
		EffectName += "Hit";
		GameEngineSound::Play("Slash1.wav");
		CameraShake(0.2f);
	}
	else
	{
		DamageUnit->Dodge();
		EffectName = "Dodge";
	}

	DamageUnit->HitEffect(EffectName);
}

void BattleAnimationLevel::HealEvent()
{
	TargetAnimation->HitEffect("Heal");
	TimeEvent.AddEvent(1.5f, std::bind(&BattleAnimationUI::SetDamage, UI, (*BattleIter).TargetUnit));
}

void BattleAnimationLevel::TurnEnd()
{
	BattleIter++;
	IsTurnEnd = true;
}


void BattleAnimationLevel::Start()
{

	CreateNewCamera(101)->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	CameraTransform = GetMainCamera()->GetTransform();
	CameraTransform->SetLocalPosition({ 0, 0, -554.0f });
	GetMainCamera()->SetSortType(RenderOrder::Unit, SortType::ZSort);
	//GetMainCamera()->SetSortType(RenderOrder::Effect, SortType::None);

}

void BattleAnimationLevel::Update(float _DeltaTime)
{
	TimeEvent.Update(_DeltaTime);

	if (true == IsShake)
	{
		ShakeUpdate(_DeltaTime);
	}
	if (true == IsFadeOut)
	{
		return;
	}
	if (true == IsClassChange)
	{
		return;
	}

	if (GameEngineInput::IsPress("ButtonA") || GameEngineInput::IsPress("LeftClick"))
	{
		GameEngineTime::GlobalTime.SetGlobalTimeScale(2.0f);
	}
	if (GameEngineInput::IsFree("ButtonA") && GameEngineInput::IsFree("LeftClick"))
	{
		GameEngineTime::GlobalTime.SetGlobalTimeScale(1.0f);
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsDown("Start") || GameEngineInput::IsUp("RightClick"))
	{
		GameEngineCore::ChangeLevel(ReturnLevelStr);
	}

	if (true == IsTurnEnd && true == UI->IsTurnEnd())
	{
		IsTurnEnd = false;
		TimeEvent.AddEvent(0.3f, std::bind(&BattleAnimationLevel::PlayAttack, this));
	}
}

void BattleAnimationLevel::LevelChangeStart()
{
	IsFadeOut = false;
	TimeEvent.Clear();
	// 엑터 및 렌더러 생성
	if (nullptr == BackgroundRender)
	{

		std::shared_ptr<GameEngineActor> NewActor = CreateActor<GameEngineActor>();
		std::shared_ptr<SpriteRenderer> Black = NewActor->CreateComponent<SpriteRenderer>(0);
		Black->SetTexture("Black.png");
		Black->SetLocalScale({ 1152, 768 });

		BackgroundRender = NewActor->CreateComponent<SpriteRenderer>(RenderOrder::Map);
		BackgroundRender->SetTexture("BattleBackground_Plains.png");
		BackgroundRender->SetLocalScale({ 960, 640, 1 });

		TerrainLeft = NewActor->CreateComponent<SpriteRenderer>(RenderOrder::Tile);
		TerrainLeft->SetTexture("Plain_Close.png");
		TerrainLeft->SetLocalScale({ 480, 160, 1 });
		TerrainLeft->GetTransform()->SetLocalPosition({ -240, -112 });

		TerrainRight = NewActor->CreateComponent<SpriteRenderer>(RenderOrder::Tile);
		TerrainRight->SetTexture("Plain_Close.png");
		TerrainRight->SetLocalScale({ -480, 160, 1 });
		TerrainRight->GetTransform()->SetLocalPosition({ 240, -112 });

		RightUnit = CreateActor<BattleAnimationUnit>(RenderOrder::Unit);
		LeftUnit = CreateActor<BattleAnimationUnit>(RenderOrder::Unit);
		LeftUnit->GetTransform()->SetLocalNegativeScaleX();

		UI = CreateActor<BattleAnimationUI>(RenderOrder::UI);

		FEffect = GetLastTarget()->CreateEffect<FadeEffect>();
	}

	if (true == IsClassChange)
	{
		TerrainLeft->SetTexture("Castle_Close.png");
		TerrainRight->SetTexture("Castle_Close.png");
		BackgroundRender->SetTexture("BattleBackground_ClassChange.png");
		LeftUnit->SetAnimation(SubjectUnit->GetUnitData().GetIdentityCode());
		UI->SetClassChange();
		FEffect->FadeIn(0.3f);

		RightUnit->Off();
		TimeEvent.AddEvent(1.0f, std::bind(&BattleAnimationLevel::ClassChangeEvent, this));
		return;
	}
	else
	{
		UI->SetDefault();
		RightUnit->On();
	}

	// 유닛 지정
	if (SubjectUnit->GetIsPlayer())
	{
		SubjectAnimation = LeftUnit;
		TargetAnimation = RightUnit;

		// 지형 지정
		TerrainLeft->SetTexture(GetTerrainTexture(SubjectUnit->GetUnitData().GetTerrainData()));
		TerrainRight->SetTexture(GetTerrainTexture(TargetUnit->GetUnitData().GetTerrainData()));

	}
	else
	{
		SubjectAnimation = RightUnit;
		TargetAnimation = LeftUnit;

		// 지형 지정
		TerrainLeft->SetTexture(GetTerrainTexture(TargetUnit->GetUnitData().GetTerrainData()));
		TerrainRight->SetTexture(GetTerrainTexture(SubjectUnit->GetUnitData().GetTerrainData()));
	}
	BackgroundRender->SetTexture(GetBackgroundTexture(SubjectUnit->GetUnitData().GetTerrainData()));
	if (SubjectUnit->GetUnitData().GetIdentityCode() == UnitIdentityCode::Lundgren || TargetUnit->GetUnitData().GetIdentityCode() == UnitIdentityCode::Lundgren || SubjectUnit->GetUnitData().GetIdentityCode() == UnitIdentityCode::Bool || TargetUnit->GetUnitData().GetIdentityCode() == UnitIdentityCode::Bool)
	{
		TerrainLeft->SetTexture(GetTerrainTexture(Terrain::Fort));
		TerrainRight->SetTexture(GetTerrainTexture(Terrain::Fort));
		BackgroundRender->SetTexture(GetBackgroundTexture(Terrain::Fort));
	}
	SubjectAnimation->SetAnimation(SubjectUnit);
	TargetAnimation->SetAnimation(TargetUnit);
	if (SubjectUnit->GetUnitData().GetIsPlayer() && TargetUnit->GetUnitData().GetIsPlayer())
	{
		UI->SetDataHeal(SubjectUnit, TargetUnit);
	}
	else
	{
		UI->SetData(SubjectUnit, TargetUnit, SubjectUnit->IsAttackable(TargetUnit), TargetUnit->IsAttackable(SubjectUnit));
	}
	FEffect->FadeIn(0.3f);

	TimeEvent.AddEvent(0.3f, std::bind(&BattleAnimationLevel::PlayAttack, this));
}

void BattleAnimationLevel::LevelChangeEnd()
{
	if (SubjectUnit->GetUnitData().GetClassValue() == BattleClass::Dancer)
	{
		SubjectUnit->GetUnitData().AddExp(20);
	}
	GameEngineTime::GlobalTime.SetGlobalTimeScale(1.0f);
	BgmPlayer.Stop();
}

void BattleAnimationLevel::PlayAttack()
{
	if (BattleIter == BattleData.end())
	{
		
		if (false == LeftUnit->GetIsDie())
		{
			if (SubjectUnit->GetIsPlayer())
			{
				UI->SetEXP(SubjectUnit->GetUnitData().GetExp(), BattleData.back().Exp, BattleData.back().SubjectUnit);
			}
			else
			{
				UI->SetEXP(TargetUnit->GetUnitData().GetExp(), BattleData.back().Exp, BattleData.back().TargetUnit);
			}

			

			if (true == BattleData.back().IsLevelUp)
			{
				return;
			}
		}

		if (true == LeftUnit->GetIsDie() || true == RightUnit->GetIsDie())
		{
			TimeEvent.AddEvent(3.0f, std::bind(&BattleAnimationLevel::FadeOut, this, 0.15f));
			TimeEvent.AddEvent(3.3f, std::bind(&BattleAnimationLevel::End, this));
			return;
		}
		TimeEvent.AddEvent(2.0f, std::bind(&BattleAnimationLevel::FadeOut, this, 0.15f));
		TimeEvent.AddEvent(2.3f, std::bind(&BattleAnimationLevel::End, this));
		return;
	}

	AttackCommand& Command = (*BattleIter);

	if (Command.IsCritical)
	{
		if (true == Command.SubjectAttack)
		{
			SubjectAnimation->Critical();
		}
		else
		{
			TargetAnimation->Critical();
		}
	}
	else if (Command.IsHit)
	{
		if (true == Command.SubjectAttack)
		{
			SubjectAnimation->Attack();
		}
		else
		{
			TargetAnimation->Attack();
		}
	}
	else
	{
		if (true == Command.SubjectAttack)
		{
			SubjectAnimation->Attack();
		}
		else
		{
			TargetAnimation->Attack();
		}
	}

}

void BattleAnimationLevel::End()
{
	GameEngineCore::ChangeLevel(ReturnLevelStr);
}

std::string_view BattleAnimationLevel::GetTerrainTexture(Terrain _Value)
{
	switch (_Value)
	{
	case Terrain::None:
	case Terrain::Plain:
	case Terrain::Gate:
		return "Plain_Close.png";
	case Terrain::Floor:
	case Terrain::Door:
	case Terrain::Wall:
	case Terrain::Fort:
	case Terrain::Pillar:
	case Terrain::Throne:
		return "Castle_Close.png";
	case Terrain::Road:
	case Terrain::Bridge:
		return "Path_Close.png";
	case Terrain::Forest:
	case Terrain::Cliff:
		return "Forest_Close.png";
	case Terrain::Mountain:
	case Terrain::Peak:
		return "Mountain_Close.png";
	case Terrain::Ruins:
	case Terrain::House:
	case Terrain::Shop:
		return "Building_Close.png";
	case Terrain::Sea:
	case Terrain::Lake:
	case Terrain::River:
		return "River_Close.png";
	default:
		break;
	}

	return "Plain_Close.png";
}

std::string_view BattleAnimationLevel::GetBackgroundTexture(Terrain _Value)
{
	switch (_Value)
	{
	case Terrain::None:
	case Terrain::Plain:
	case Terrain::Gate:
		return "BattleBackground_Plains.png";
	case Terrain::Floor:
	case Terrain::Door:
	case Terrain::Wall:
	case Terrain::Fort:
	case Terrain::Pillar:
	case Terrain::Throne:
		return "BattleBackground_Castle.png";
	case Terrain::Road:
	case Terrain::Bridge:
		return "BattleBackground_Town.png";
	case Terrain::Forest:
	case Terrain::Cliff:
		return "BattleBackground_Forest.png";
	case Terrain::Mountain:
	case Terrain::Peak:
		return "BattleBackground_Mountain.png";
	case Terrain::Ruins:
	case Terrain::House:
	case Terrain::Shop:
		return "BattleBackground_Town.png";
	case Terrain::Sea:
	case Terrain::Lake:
	case Terrain::River:
		return "BattleBackground_River.png";
	default:
		break;
	}

	return "BattleBackground_Plains.png";
}

void BattleAnimationLevel::ClassChangeEvent()
{
	UI->SetFadeWhite();
	UI->SetFadeIn(0.5f);
	UI->SetFadeWait(0.5f);
	SubjectUnit->ClassChange(ChangeClass);
	LeftUnit->SetAnimation(SubjectUnit->GetUnitData().GetIdentityCode());

	TimeEvent.AddEvent(1.5f, std::bind(&BattleAnimationUI::ClassChangeStart, UI, SubjectUnit->GetUnitData(), SubjectUnit->GetName()));
}

void BattleAnimationLevel::FadeOut(float _Time)
{
	IsFadeOut = true;
	FEffect->FadeOut(_Time);
	BgmPlayer.SoundFadeOut(_Time);

	GameEngineTime::GlobalTime.SetGlobalTimeScale(1.0f);
}

void BattleAnimationLevel::CameraShake(float _Time)
{
	IsShake = true;
	ShakeTimer = _Time;
	ShakeDelayTimer = 0;
}
GameEngineRandom Random;

void BattleAnimationLevel::ShakeUpdate(float _DeltaTime)
{
	ShakeTimer -= _DeltaTime;
	ShakeDelayTimer -= _DeltaTime;
	if (ShakeTimer < 0)
	{
		IsShake = false;
		CameraTransform->SetLocalPosition({ 0, 0, -554.0f });
		return;
	}
	if (0 < ShakeDelayTimer) { return; }
	float Random1 = Random.RandomFloat(-1, 1);
	float Random2 = Random.RandomFloat(-1, 1);
	CameraTransform->SetLocalPosition(float4(0, 0, -554.0f) + float4(ShakeAmount.x * Random1, ShakeAmount.y * Random2));
	ShakeDelayTimer = ShakeDelay;
}

void BattleAnimationLevel::BattleEnd()
{
	IsFadeOut = true;
	FEffect->FadeOut(0.15f);
	BgmPlayer.SoundFadeOut(0.3f);
	TimeEvent.AddEvent(0.3f, std::bind(&BattleAnimationLevel::End, this));
	GameEngineTime::GlobalTime.SetGlobalTimeScale(1.0f);
}