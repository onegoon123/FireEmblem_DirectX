#include "PrecompileHeader.h"
#include "Stage0.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
Stage0::Stage0() 
{
	StartPos.push_back({ 13, 2 });
	StartPos.push_back({ 13, 4 });
	StartPos.push_back({ 14, 3 });
	StartPos.push_back({ 13, 0 });
	StartPos.push_back({ 13, 1 });
	StartPos.push_back({ 14, 1 });
	StartPos.push_back({ 14, 2 });
	StartPos.push_back({ 12, 2 });
	StartPos.push_back({ 13, 3 });
	StartPos.push_back({ 14, 4 });
}

Stage0::~Stage0() 
{
}

void Stage0::StageSetting()
{
	SetStage(0);
	ClearTarget = BattleClearTarget::Conquer;
	ConquerPos = { 3, 7 };
	ClearTargetText = "목표:문 제압";

	// 린
	Unit_Lyn = NewPlayerUnit(UnitIdentityCode::Lyn, 1, {13, 2}, { ItemCode::IronSword, ItemCode::Vulnerary, ItemCode::Vulnerary, ItemCode::MasterSeal });
	
	// 산적
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 2, 3 }, { ItemCode::IronAxe });
	// 바타
	NewEnemyUnit(UnitIdentityCode::Batta, 1, { 3, 7 }, { ItemCode::IronAxe})->SetDetectionRange(1);

	
	OpeningEventInit();
	ClearEventInit();
}

void Stage0::OpeningEventInit()
{
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->SetTexture("Black.png");
		OpeningEvent->Background->On();
		}
	, false, 1.0f);
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetSize({ 26, 5 });
		OpeningEvent->Dialogue->Text->SetTextAnim(L"...정신이 들어?");
		OpeningEvent->Dialogue->SetFadeIn(.5f);
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ -324, -128 });
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(0.5f);
		}
	, false, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->SetTexture("EventScene1.png");
		OpeningEvent->SetFadeIn(1.0f);
		BgmPlayer = GameEngineSound::Play("LynTheme.mp3");
		}
	, false, 1.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->Text->SetTextAnim(L"너, 초원 입구에\n쓰러져 있었어.");
		OpeningEvent->Dialogue->SetFadeIn(.5f);
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ -324, -128 });
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(0.5f);
		}
	, false, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeOut(1.0f);
		}
	, false, 1.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->On();
		OpeningEvent->Portrait2->SetPortrait(UnitIdentityCode::BladeLordLyn);
		OpeningEvent->Background->SetTexture("EventBackground_House.png");
		OpeningEvent->SetFadeIn(1.0f);
		}
	, false, 1.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetSize({ 17, 5 });
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Dialogue->SetFadeIn(.2f);
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"나는 린.\n로르카족 사람이야.");
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ -32, 164 });
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"너는?\n네 이름을 알려줘");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"마크라고?\n...신기한 울림이네.");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetPortrait(UnitIdentityCode::Lyn);
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"! 밖이 시끄러운걸...");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetPortrait(UnitIdentityCode::Lyn);
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"잠깐 보고 올 테니까\n마크는 여기에 있어!");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeOut(0.7f);
		OpeningEvent->Dialogue->SetFadeOut(0.5f);
		BgmPlayer.SoundFadeOut(1.5f);
		}
	, false, 1.0f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->Off();
		OpeningEvent->Portrait2->Off();
		OpeningEvent->SetFadeIn(1.0f);
		Unit_Lyn->SetMapPos({ 14, 0 });
		}
	, false, 1.0f);


	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->Off();
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->SetMoveSpeed(5.0f);
		Unit_Lyn->IsEventMove = true;
		Unit_Lyn->MoveMapPosLerp(int2::Up * 2);
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->MoveMapPosLerp(int2::Left * 1);
		}
	, false, 1.0f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->MoveMapPosLerp(int2::Right * 1);
		}
	, false, 0.2f);
	OpeningEvent->PushEvent([this] {
		Unit_Lyn->MoveMapPosLerp(int2::Down * 2);
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeOut(0.5f);
		}
	, false, 0.5f);

	OpeningEvent->PushEvent([this] {
		BgmPlayer = GameEngineSound::Play("An Unexpected Caller.mp3");
		OpeningEvent->Background->On();
		OpeningEvent->Portrait1->On();
		OpeningEvent->Portrait1->GetTransform()->SetLocalPosition({ -1000, -160 });
		OpeningEvent->Portrait1->SetLerpPos({ -284, -160 } , 0.5f);
		OpeningEvent->Portrait1->SetPortrait(UnitIdentityCode::Lyn);
		OpeningEvent->SetFadeIn(.5f);
		}
	, false, 1.0f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeIn(.2f);
		OpeningEvent->Dialogue->SetSize({ 22, 5 });
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Dialogue->ArrowRender->SetFlipX();
		OpeningEvent->Portrait1->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"큰일이야! 베른의 산적 놈들이\n산에서 내려왔어!");
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ -432, 164 });
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait1->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"또 근처의 마을을 약탈할거야...\n그렇게 놔두진 않을 거야!");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(0.5f);
		OpeningEvent->SetFadeOut(1.0f);
		}
	, false, 1.0f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeIn(0.2f);
		OpeningEvent->Background->Off();
		OpeningEvent->Portrait1->Off();
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->SetMoveSpeed(5.0f);
		Unit_Lyn->MoveMapPosLerp(int2::Up * 2);
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->MoveMapPosLerp(int2::Left * 1);
		}
	, false, 0.5f);

	OpeningEvent->PushEvent([this] {
		Unit_Lyn->IsEventMove = false;
		Unit_Lyn->SetMoveSpeed(15.0f);
		}
	, false, .0f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait1->SetPortrait(UnitIdentityCode::Lyn);
		OpeningEvent->Portrait1->On();
		OpeningEvent->Portrait1->SetFadeIn(0.5f);
		}
	, false, 0.2f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeIn(.2f);
		OpeningEvent->Dialogue->SetSize({ 22, 5 });
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Portrait1->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"뭐!? 같이 가겠다니...\n너 쓸 줄 아는 무기는 있어?");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait1->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"...그래? 마크는\n견습 군사구나.");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait1->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"알았어.\n둘이서 가자!");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait1->SetFadeOut(0.5f);
		OpeningEvent->Dialogue->SetFadeOut(0.5f);
		}
	, false, 1.0f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait1->Off();
		OpeningEvent->Dialogue->Off();
		}
	, false, 0.5f);

	OpeningEvent->SkipFunction = [this] {
		OpeningEvent->Portrait1->Off();
		OpeningEvent->Portrait2->Off();
		OpeningEvent->Dialogue->Off();
		Unit_Lyn->SetMapPos({ 13, 2 });
		Unit_Lyn->IsEventMove = false;
		Unit_Lyn->SetMoveSpeed(15.0f);
	};
}

void Stage0::ClearEventInit()
{

	ClearEvent->PushEvent([this] {
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::Play("Win.mp3");
		}, false, 0.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait2->SetPortrait(UnitIdentityCode::Lyn);
		ClearEvent->Portrait2->On();
		ClearEvent->Portrait2->SetFadeIn(0.5f);
	}, false, 1.0f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetSize({ 17, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Portrait2->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"수고했어, 마크!\n그럼 집으로 돌아가자.");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -32, 164 });
		}
	, true, 0.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Foreground->On();
		ClearEvent->SetFadeOut(0.5f);
	}, false, 1.0f);

	ClearEvent->PushEvent([this] {
		GameEngineCore::ChangeLevel("Stage1");
		}, false, .6f);

	ClearEvent->SkipFunction = [this] {
		GameEngineCore::ChangeLevel("Stage1");
	};
}

