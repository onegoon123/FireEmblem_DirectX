#include "PrecompileHeader.h"
#include "Stage10.h"
#include "FEData.h"
Stage10::Stage10()
{
	StartPos.push_back({ 4, 15 });
	StartPos.push_back({ 5, 14 });
	StartPos.push_back({ 4, 14 });
	StartPos.push_back({ 5, 16 });
	StartPos.push_back({ 3, 15 });
	StartPos.push_back({ 2, 16 });
	StartPos.push_back({ 6, 15 });
	StartPos.push_back({ 2, 15 });
	StartPos.push_back({ 4, 16 });
	StartPos.push_back({ 5, 13 });
	StartPos.push_back({ 5, 17 });
	StartPos.push_back({ 5, 15 });
}

Stage10::~Stage10()
{
}

void Stage10::StageSetting()
{
	SetStage(10);
	ClearTarget = BattleClearTarget::Conquer;
	ConquerPos = { 2, 1 };
	ClearTargetText = "목표:성문 제압";

	OpeningEventInit();
	ClearEventInit();
	NewPlayerUnit(UnitIdentityCode::Lyn, 10, { 4, 15 }, { ItemCode::ManiKatti, ItemCode::Vulnerary, ItemCode::MasterSeal });
	NewPlayerUnit(UnitIdentityCode::Kent, 8, { 5, 14 }, { ItemCode::IronLance, ItemCode::IronSword, ItemCode::Vulnerary });
	NewPlayerUnit(UnitIdentityCode::Florina, 8, { 4, 14 }, { ItemCode::SlimLance});
	NewPlayerUnit(UnitIdentityCode::Serra, 8, { 5, 16 }, { ItemCode::Heal });
	NewPlayerUnit(UnitIdentityCode::Erk, 8, { 3, 15 }, { ItemCode::Fire, ItemCode::Flux });
	NewPlayerUnit(UnitIdentityCode::Wil, 8, { 2, 16 }, { ItemCode::IronBow });
	NewPlayerUnit(UnitIdentityCode::Wallace, 1, { 6, 15 }, { ItemCode::IronLance, ItemCode::IronAxe, ItemCode::MasterSeal });

	NewEnemyUnit(UnitIdentityCode::Soldier, 5, { 14, 14 }, { ItemCode::IronLance });
	NewEnemyUnit(UnitIdentityCode::Mage, 1, { 15, 15 }, { ItemCode::Fire });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 13, 16 }, { ItemCode::IronAxe })->SetDetectionRange(6);
	NewEnemyUnit(UnitIdentityCode::Archer, 3, { 16, 13 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Archer, 3, { 14, 9 }, { ItemCode::IronBow })->SetDetectionRange(8);
	NewEnemyUnit(UnitIdentityCode::DarkMage, 3, { 15, 3 }, { ItemCode::Flux });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 3, { 9, 7 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 3, { 8, 8 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Archer, 3, { 7, 4 }, { ItemCode::IronBow })->SetDetectionRange(8);
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 7, 6 }, { ItemCode::IronAxe })->SetDetectionRange(7);
	NewEnemyUnit(UnitIdentityCode::Knight, 3, { 2, 0 }, { ItemCode::IronLance })->SetDetectionRange(3);
	NewEnemyUnit(UnitIdentityCode::PegasusKnight, 3, { 1, 7 }, { ItemCode::IronLance });
	NewEnemyUnit(UnitIdentityCode::PegasusKnight, 3, { 13, 0 }, { ItemCode::IronLance })->SetDetectionRange(10);
	NewEnemyUnit(UnitIdentityCode::PegasusKnight, 3, { 15, 0 }, { ItemCode::IronLance })->SetDetectionRange(10);
	NewEnemyUnit(UnitIdentityCode::Lundgren, 1, { 2, 1 }, { ItemCode::SilverLance })->SetDetectionRange(1);
}

void Stage10::OpeningEventInit()
{
	OpeningEvent->PushEvent([this] {
		BgmPlayer = GameEngineSound::Play("Companions.mp3");
		OpeningEvent->SetFadeIn(0.5f);
		}
	, false, 1.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeOut(0.5f);
		}
	, false, 0.8f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->SetTexture("EventBackground_Plains.png");
		OpeningEvent->Background->On();
		OpeningEvent->Portrait2->SetPortrait(UnitIdentityCode::Lyn);
		OpeningEvent->Portrait2->On();
		OpeningEvent->Portrait3->SetPortrait(UnitIdentityCode::Sain);
		OpeningEvent->Portrait3->On();
		OpeningEvent->Portrait4->SetPortrait(UnitIdentityCode::Kent);
		OpeningEvent->Portrait4->On();
		OpeningEvent->SetFadeIn(0.5f);
		}
	, false, 0.8f);


	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetSize({ 20, 5 });
		OpeningEvent->Portrait4->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"린디스님, 산을 우회하면\n키아란성이 보일 겁니다.");
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Dialogue->ArrowRender->SetFlipX();
		OpeningEvent->Dialogue->SetFadeIn(.5f);
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ -324, 164 });
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.3f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetSize({ 13, 5 });
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Dialogue->ArrowRender->SetFlipX();
		OpeningEvent->Dialogue->SetFadeIn(.2f);
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"할아버님...");
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ -32, 164 });
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"...이제 곧\n만날 수 있어요...");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.3f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeIn(.2f);
		OpeningEvent->Dialogue->SetSize({ 20, 5 });
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Dialogue->ArrowRender->SetFlipX();
		OpeningEvent->Portrait3->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"모든 것은\n이 전투에 달려 있습니다.");
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ -432, 164 });
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait3->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"믿고 있던 인근 영지로부터\n지원도 나오지 않게 된 지금...");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait3->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"랑그렌 공도 사력을 다해\n덤벼 올 테니까요!");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.3f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetSize({ 17, 5 });
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Dialogue->ArrowRender->SetFlipX();
		OpeningEvent->Dialogue->SetFadeIn(.2f);
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"얼마나 많은 수를 쓰든\n난 지지 않아!");
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ 0, 164 });
		}
	, true, 0.5f);
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"할아버님을\n만나 뵙기 위해서...");
		}
	, true, 0.5f);
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"그것만을 위해서\n여기까지 온 거니까!");
		}
	, true, 0.5f);
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"모두들!\n부디 내게 힘을 빌려줘!!");
		}
	, true, 0.5f);
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(.2f);
		OpeningEvent->SetFadeOut(0.5f);
		BgmPlayer.SoundFadeOut(1.0f);
		}
	, false, 0.6f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->Off();
		OpeningEvent->Portrait2->Off();
		OpeningEvent->Portrait3->Off();
		OpeningEvent->Portrait4->Off();
		OpeningEvent->SetFadeIn(.5f);
		}
	, false, 0.5f);

	OpeningEvent->SkipFunction = [this] {
		BgmPlayer.SoundFadeOut(0.3f);
	};
}

void Stage10::ClearEventInit()
{
	ClearEvent->PushEvent([this] {
		ClearEvent->SetFadeOut(1.5f);
		BgmPlayer.SoundFadeOut(0.1f);
		}, false, 0.15f);

	ClearEvent->PushEvent([this] {
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::Play("Win.mp3");
		}, false, 1.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Background->SetTexture("EventBackground_Castle.png");
		ClearEvent->Background->On();
		ClearEvent->Portrait2->SetPortrait(UnitIdentityCode::Lyn);
		ClearEvent->Portrait2->On();
		ClearEvent->SetFadeIn(1.5f);
		}, false, 1.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetSize({ 16, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Portrait2->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"이겼어...\n이걸로, 할아버님께...");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -32, 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait1->SetPortrait(UnitIdentityCode::NPC1);
		ClearEvent->Portrait1->SetFadeIn(0.5f);
		ClearEvent->Portrait1->On();
		}
	, false, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->SetSize({ 16, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"린디스님...이시군요?");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -432, 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetSize({ 10, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait2->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"당신은 누구야?");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -32, 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->SetSize({ 22, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"키아란 후작가의 재상을 맡고 있는\n레제만이라고 합니다.");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -432, 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"켄트와 세인으로부터\n보고를 받고 있었지만,");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"랑그렌에게 들켜서\n지금까지 감금되어 있었습니다.");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"무사히 돌아오시길\n...기다리고 있었습니다.");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetSize({ 24, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait2->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"고마워...\n그래서, 할아버님을 만날 수 있을까?");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -128 , 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->SetSize({ 22, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"네, 물론입니다.");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -432, 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"랑그렌이 후작님의 식사에\n여태까지 독을 넣고 있었기에,");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"완전히 몸이 망가지셔서...\n계속 누워 계셨습니다.");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		BgmPlayer.SoundFadeOut(1.0f);
		ClearEvent->SetFadeOut(1.0f);
		}
	, false, 1.3f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->Off();
		ClearEvent->Background->SetTexture("EventBackground_House2.png");
		ClearEvent->Portrait1->SetPortrait(UnitIdentityCode::NPC2);
		ClearEvent->SetFadeIn(1.0f);
		}
	, false, 1.3f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->SetSize({ 22, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"...누구지");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -432, 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"나는 누구도\n만나지 않겠다고 하지 않았느냐.");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetSize({ 10, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Dialogue->Text->SetTextAnim(L"......");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ 32 , 164 });
		ClearEvent->Portrait2->SetTexture("Portrait_LynSad.png");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.5f);
	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->SetSize({ 22, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"뭘 하고 있는게야!\n빨리 나가라고 하지...");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -432, 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		ClearEvent->Portrait2->SetTexture("Portrait_Lyn.png");
		BgmPlayer = GameEngineSound::Play("Lyn's Desire.mp3");
		}
	, false, 0.5f);
	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetSize({ 20, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait2->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"...저기!\n저는...");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -128 , 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait2->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"저는\n린디스...입니다.");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.1f);
	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->SetSize({ 15, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"!? 린디스라고\n...설마");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -344, 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetSize({ 24, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait2->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"아버지의 이름은 하살,\n어머니의 이름은... 마델린");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -128 , 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait2->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"15살까지\n초원에서 자라왔어요.");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.5f);
	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->SetSize({ 15, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"...\n정말인가?");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -344, 164 });
		}
	, true, 0.1f);
	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"이, 이쪽으로\n얼굴을 보여 주게...");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		ClearEvent->Portrait2->SetLerpPos({128, -160}, .5f);
		}
	, false, 1.5f);
	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->SetSize({ 20, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"오오...\n트,틀림없어...");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -344, 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Portrait1->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"마델린을 정말 닮았구나...\n오오,오오...");
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->SetSize({ 15, 5 });
		ClearEvent->Dialogue->ArrowRender->On();
		ClearEvent->Dialogue->SetFadeIn(.2f);
		ClearEvent->Dialogue->ArrowRender->SetFlipX();
		ClearEvent->Portrait2->SetLipAnimation(1.0f);
		ClearEvent->Dialogue->Text->SetTextAnim(L"할아버님!!");
		ClearEvent->Dialogue->GetTransform()->SetLocalPosition({ -128 , 164 });
		}
	, true, 0.1f);

	ClearEvent->PushEvent([this] {
		ClearEvent->SetFadeOut(1.0f);
		}
	, false, 1.2f);

	ClearEvent->PushEvent([this] {
		ClearEvent->Dialogue->Off();
		ClearEvent->Portrait1->Off();
		ClearEvent->Portrait2->Off();
		ClearEvent->SetFadeIn(1.0f);
		ClearEvent->Background->SetTexture("MeetGrandfather.png");
		}
	, true, 1.5f);

	ClearEvent->PushEvent([this] {
		ClearEvent->SetFadeOut(1.0f);
		}
	, false, 1.2f);

	ClearEvent->PushEvent([this] {
		BgmPlayer.SoundFadeOut(0.2f);
		GameEngineCore::ChangeLevel("EndingLevel");
		}, false, .6f);

	ClearEvent->SkipFunction = [this] {
		GameEngineCore::ChangeLevel("EndingLevel");
	};
}
