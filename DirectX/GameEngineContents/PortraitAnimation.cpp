#include "PrecompileHeader.h"
#include "PortraitAnimation.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
PortraitAnimation::PortraitAnimation()
{
}

PortraitAnimation::~PortraitAnimation()
{
}

void PortraitAnimation::SetTexture(const std::string_view& _Texture)
{
	PortraitRender->SetTexture(_Texture);
	LipRender->Off();
}

void PortraitAnimation::SetPortrait(UnitIdentityCode _Value)
{
	std::string LipSprite;
	LipRender->GetTransform()->SetLocalPosition({ -128, -192 });
	switch (_Value)
	{
	case UnitIdentityCode::Lyn:
		PortraitRender->SetTexture("Portrait_Lyn.png");
		LipRender->GetTransform()->AddLocalPosition({ 64, 128 });
		LipSprite = "LipSync_Lyn.png";
		break;
	case UnitIdentityCode::BladeLordLyn:
		PortraitRender->SetTexture("Portrait_LynFront.png");
		LipRender->GetTransform()->AddLocalPosition({ 64, 128 });
		LipSprite = "LipSync_LynFront.png";
		break;
	case UnitIdentityCode::Sain:
	case UnitIdentityCode::SainSword:
		PortraitRender->SetTexture("Portrait_Sain.png");
		LipSprite = "LipSync_Sain.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Kent:
	case UnitIdentityCode::KentSword:
		PortraitRender->SetTexture("Portrait_Kent.png");
		LipSprite = "LipSync_Kent.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Florina:
		PortraitRender->SetTexture("Portrait_Florina.png");
		LipSprite = "LipSync_Florina.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 96 });
		break;
	case UnitIdentityCode::Wil:
		PortraitRender->SetTexture("Portrait_Wil.png");
		LipSprite = "LipSync_Wil.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Dorcas:
	case UnitIdentityCode::WarriorDorcas:
		PortraitRender->SetTexture("Portrait_Dorcas.png");
		LipSprite = "LipSync_Dorcas.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 208 });
		break;
	case UnitIdentityCode::Serra:
		PortraitRender->SetTexture("Portrait_Serra.png");
		LipSprite = "LipSync_Serra.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 128 });
		break;
	case UnitIdentityCode::Erk:
		PortraitRender->SetTexture("Portrait_Erk.png");
		LipSprite = "LipSync_Erk.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 128 });
		break;
	case UnitIdentityCode::Rath:
		PortraitRender->SetTexture("Portrait_Rath.png");
		LipSprite = "LipSync_Rath.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Matthew:
	case UnitIdentityCode::AssassinMatthew:
		PortraitRender->SetTexture("Portrait_Matthew.png");
		LipSprite = "LipSync_Matthew.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Ninian:
		PortraitRender->SetTexture("Portrait_Ninian.png");
		LipSprite = "LipSync_Ninian.png";
		LipRender->GetTransform()->AddLocalPosition({ 96, 128 });
		break;
	case UnitIdentityCode::Lucius:
		PortraitRender->SetTexture("Portrait_Lucius.png");
		LipSprite = "LipSync_Lucius.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Wallace:
	case UnitIdentityCode::GeneralWallace:
	case UnitIdentityCode::GeneralWallaceAxe:
		PortraitRender->SetTexture("Portrait_Wallace.png");
		LipSprite = "LipSync_Wallace.png";
		break;
	case UnitIdentityCode::Brigand:
		break;
	case UnitIdentityCode::Soldier:
		break;
	case UnitIdentityCode::Mercenary:
		break;
	case UnitIdentityCode::Archer:
		break;
	case UnitIdentityCode::Knight:
		break;
	case UnitIdentityCode::Mage:
		break;
	case UnitIdentityCode::DarkMage:
		break;
	case UnitIdentityCode::PegasusKnight:
		break;
	case UnitIdentityCode::Batta:
		PortraitRender->SetTexture("Portrait_Batta.png");
		LipSprite = "LipSync_Batta.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Zugu:
		PortraitRender->SetTexture("Portrait_Zugu.png");
		LipSprite = "LipSync_Zugu.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Glass:
		PortraitRender->SetTexture("Portrait_Glass.png");
		LipSprite = "LipSync_Glass.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Migal:
		PortraitRender->SetTexture("Portrait_Migal.png");
		LipSprite = "LipSync_Migal.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Carjiga:
		PortraitRender->SetTexture("Portrait_Carjiga.png");
		LipSprite = "LipSync_Carjiga.png";
		LipRender->GetTransform()->AddLocalPosition({ 68, 160 });
		break;
	case UnitIdentityCode::Bool:
		PortraitRender->SetTexture("Portrait_Bool.png");
		LipSprite = "LipSync_Bool.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Yogi:
		PortraitRender->SetTexture("Portrait_Yogi.png");
		LipSprite = "LipSync_Yogi.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Eagler:
		PortraitRender->SetTexture("Portrait_Eagler.png");
		LipSprite = "LipSync_Eagler.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::Lundgren:
		PortraitRender->SetTexture("Portrait_Lundgren.png");
		LipSprite = "LipSync_Lundgren.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::NPC1:
		PortraitRender->SetTexture("Portrait_NPC1.png");
		LipSprite = "LipSync_NPC1.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	case UnitIdentityCode::NPC2:
		PortraitRender->SetTexture("Portrait_NPC2.png");
		LipSprite = "LipSync_NPC2.png";
		LipRender->GetTransform()->AddLocalPosition({ 64, 160 });
		break;
	default:
		break;
	}
	if (nullptr == LipRender->FindAnimation(LipSprite))
	{
		if (nullptr == GameEngineSprite::Find(LipSprite))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToDirectory("ContentResources");
			Dir.Move("ContentResources");
			Dir.Move("Character");
			Dir.Move("Portrait");
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName(LipSprite).GetFullPath(), 4, 2);
		}
		LipRender->CreateAnimation({ .AnimationName = LipSprite, .SpriteName = LipSprite, .Start = 3, .End = 6, .FrameInter = 0.1f, .Loop = true });
	}
	LipRender->ChangeAnimation(LipSprite);
	PortraitRender->On();
}

void PortraitAnimation::SetLipAnimation(float _Time)
{
	LipRender->On();
	Timer = _Time;
}

void PortraitAnimation::SetFadeIn(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 0;
	IsFadeIn = true;
	PortraitRender->ColorOptionValue.MulColor.a = 0;
	//PortraitRender->On();
	//LipRender->Off();
}

void PortraitAnimation::SetFadeOut(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 1;
	IsFadeOut = true;
	PortraitRender->ColorOptionValue.MulColor.a = 1;
	//PortraitRender->On();
	//LipRender->Off();
}

void PortraitAnimation::SetLerpPos(const float4& _Pos, float _Time)
{
	LerpStartPos = GetTransform()->GetLocalPosition();
	LerpEndPos = _Pos;
	LerpSpeed = 1 / _Time;
	LerpTimer = 0;
	IsLerp = true;
}

void PortraitAnimation::Start()
{
	PortraitRender = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	PortraitRender->GetTransform()->SetParent(GetTransform());
	PortraitRender->GetTransform()->SetLocalScale({ 384, 320 });
	PortraitRender->Off();

	LipRender = GetActor()->CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	LipRender->GetTransform()->SetParent(GetTransform());
	LipRender->GetTransform()->SetLocalScale({ 128, 64 });
	LipRender->Off();
}

void PortraitAnimation::Update(float _DeltaTime)
{
	LerpUpdate(_DeltaTime);
	FadeUpdate(_DeltaTime);

	if (Timer <= 0) { return; }
	Timer -= _DeltaTime;
	if (Timer <= 0) {
		LipRender->Off();
	}

}

void PortraitAnimation::LerpUpdate(float _DeltaTime)
{
	if (false == IsLerp) { return; }
	LerpTimer += _DeltaTime * LerpSpeed;
	GetTransform()->SetLocalPosition(float4::LerpClamp(LerpStartPos, LerpEndPos, LerpTimer));
	if (1 < LerpTimer)
	{
		IsLerp = false;
	}
}

void PortraitAnimation::FadeUpdate(float _DeltaTime)
{
	if (true == IsFadeIn)
	{
		FadeTimer += _DeltaTime * FadeSpeed;
		if (FadeTimer > 1)
		{
			IsFadeIn = false;
			PortraitRender->ColorOptionValue.MulColor.a = 1;
			return;
		}
		PortraitRender->ColorOptionValue.MulColor.a = FadeTimer;
	}

	if (true == IsFadeOut)
	{
		FadeTimer -= _DeltaTime * FadeSpeed;
		if (FadeTimer < 0)
		{
			IsFadeOut = false;
			PortraitRender->ColorOptionValue.MulColor.a = 0;
			return;
		}
		PortraitRender->ColorOptionValue.MulColor.a = FadeTimer;
	}
}
