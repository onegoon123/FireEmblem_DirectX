#include "PrecompileHeader.h"	
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "BattleAnimationLevel.h"
#include "SpriteRenderer.h"
#include "BattleAnimationUnit.h"
#include "BattleAnimationUI.h"
std::shared_ptr<BattleUnit> BattleAnimationLevel::SubjectUnit = nullptr;
std::shared_ptr<BattleUnit> BattleAnimationLevel::TargetUnit = nullptr;
std::list<AttackCommand> BattleAnimationLevel::BattleData = std::list<AttackCommand>();
std::list<AttackCommand>::iterator BattleAnimationLevel::BattleIter = std::list<AttackCommand>::iterator();

BattleAnimationLevel::BattleAnimationLevel()
{
}

BattleAnimationLevel::~BattleAnimationLevel()
{
}

void BattleAnimationLevel::SetBattleData(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, const std::list<AttackCommand>& _Data)
{
	SubjectUnit = _SubjectUnit;
	TargetUnit = _TargetUnit;
	BattleData = _Data;
	BattleIter = BattleData.begin();
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
		UI->SetDamage((*BattleIter).TargetUnit);

		if (true == (*BattleIter).TargetUnit.GetIsDie())
		{
			TimeEvent.AddEvent(1.5f, std::bind(&BattleAnimationUnit::Die, DamageUnit));
		}
	}
	else
	{
		DamageUnit = SubjectAnimation;
		AttackUnit = TargetUnit;
		UI->SetDamage((*BattleIter).SubjectUnit);

		if (true == (*BattleIter).SubjectUnit.GetIsDie())
		{
			TimeEvent.AddEvent(1.5f, std::bind(&BattleAnimationUnit::Die, DamageUnit));
		}
	}

	if (AttackUnit->GetUnitData().GetClassValue() == BattleClass::Mage)
	{
		EffectName = "Fire";
		// 마법사 경우 다른 이펙트
	}

	if ((*BattleIter).IsCritical)
	{
		EffectName += "Critical";
	}
	else if ((*BattleIter).IsHit)
	{
		EffectName += "Hit";
	}
	else
	{
		DamageUnit->Dodge();
		EffectName += "Dodge";
	}


	DamageUnit->HitEffect(EffectName);
}

void BattleAnimationLevel::TurnEnd()
{
	BattleIter++;
	IsTurnEnd = true;
}

void BattleAnimationLevel::Start()
{


	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -554.0f });
	
}

void BattleAnimationLevel::Update(float _DeltaTime)
{
	TimeEvent.Update(_DeltaTime);

	if (GameEngineInput::IsPress("ButtonA") || GameEngineInput::IsPress("LeftClick"))
	{
		GameEngineTime::GlobalTime.SetTimeScale(2.0f);
	}
	if (GameEngineInput::IsFree("ButtonA") && GameEngineInput::IsFree("LeftClick"))
	{
		GameEngineTime::GlobalTime.SetTimeScale(1.0f);
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsDown("Start") || GameEngineInput::IsUp("RightClick"))
	{
		GameEngineCore::ChangeLevel("BattleLevel");
	}

	if (true == IsTurnEnd && true == UI->IsTurnEnd())
	{
		IsTurnEnd = false;
		TimeEvent.AddEvent(0.3f, std::bind(&BattleAnimationLevel::PlayAttack, this));
	}
}

void BattleAnimationLevel::LevelChangeStart()
{
	// 리소스 로딩
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		Dir.MoveParent();
		Dir.Move("Character");
		Dir.Move("BattleIcon");
		File = Dir.GetAllFile({ ".png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
		Dir.MoveParent();
		Dir.Move("Map");
		File = Dir.GetAllFile({ ".png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
		Dir.MoveParent();
		Dir.Move("Portrait");
		File = Dir.GetAllFile({ ".png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// 엑터 및 렌더러 생성
	if (nullptr == BackgroundRender)
	{
		std::shared_ptr<GameEngineActor> NewActor = CreateActor<GameEngineActor>();
		BackgroundRender = NewActor->CreateComponent<SpriteRenderer>(RenderOrder::Map);
		BackgroundRender->SetTexture("BattleBackground_Plains.png");
		BackgroundRender->SetLocalScale({ 960, 640 });

		TerrainLeft = NewActor->CreateComponent<SpriteRenderer>(RenderOrder::Tile);
		TerrainLeft->SetTexture("Plain_Close.png");
		TerrainLeft->SetLocalScale({ 480, 160 });
		TerrainLeft->GetTransform()->SetLocalPosition({ -240, -112 });

		TerrainRight = NewActor->CreateComponent<SpriteRenderer>(RenderOrder::Tile);
		TerrainRight->SetTexture("Plain_Close.png");
		TerrainRight->SetLocalScale({ -480, 160 });
		TerrainRight->GetTransform()->SetLocalPosition({ 240, -112 });

		RightUnit = CreateActor<BattleAnimationUnit>(RenderOrder::Unit);
		LeftUnit = CreateActor<BattleAnimationUnit>(RenderOrder::Unit);
		LeftUnit->GetTransform()->SetLocalNegativeScaleX();

		UI = CreateActor<BattleAnimationUI>(RenderOrder::UI);
	}

	// 유닛 지정
	if (SubjectUnit->GetIsPlayer())
	{
		SubjectAnimation = LeftUnit;
		TargetAnimation = RightUnit;
	}
	else
	{
		SubjectAnimation = RightUnit;
		TargetAnimation = LeftUnit;
	}

	SubjectAnimation->SetAnimation(SubjectUnit);
	TargetAnimation->SetAnimation(TargetUnit);
	UI->SetData(SubjectUnit->GetUnitData(), TargetUnit->GetUnitData());
	TimeEvent.Clear();
	UI->SetFadeIn(0.3f);
	TimeEvent.AddEvent(0.3f, std::bind(&BattleAnimationLevel::PlayAttack, this));
}

void BattleAnimationLevel::PlayAttack()
{
	if (BattleIter == BattleData.end())
	{
		TimeEvent.AddEvent(0.5f, std::bind(&BattleAnimationUI::SetFadeOut, UI, 0.3f));
		TimeEvent.AddEvent(1.0f, std::bind(&BattleAnimationLevel::End, this));
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
	GameEngineTime::GlobalTime.SetTimeScale(1.0f);
	GameEngineCore::ChangeLevel("BattleLevel");
}
