#include "PrecompileHeader.h"
#include "BattleAnimationLevel.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "EventSystem.h"
#include "BattleAnimationUI.h"

void BattleAnimationLevel::NewPlayerDeathEvent(UnitIdentityCode _Code ,std::string _Name, std::vector<std::wstring_view> _Script)
{
	std::shared_ptr<EventSystem> NewEvent = CreateActor<EventSystem>();
	NewEvent->PushEvent([=] {
		UI->Off();
		BgmPlayer.SoundFadeOut(0.5f);
		BgmPlayer = GameEngineSound::Play("DieBGM.mp3");
		BgmPlayer.SetLoop();
		NewEvent->Portrait1->SetTexture("Portrait_" + _Name + ".png");
		NewEvent->Portrait1->On();
		NewEvent->Dialogue->SetSize({ 20, 5 });
		NewEvent->Dialogue->SetFadeIn(0.5f);
		NewEvent->Dialogue->GetTransform()->SetLocalPosition({ -132, -160 });

		}
	, false, 0.5f);

	for (int i = 0; i < _Script.size(); i++)
	{
		NewEvent->PushEvent([=] {
			NewEvent->Dialogue->Text->SetTextAnim(_Script[i]);
			}
		, true, 0.5f);
	}

	NewEvent->PushEvent([=] {
		TimeEvent.AddEvent(0.1f, std::bind(&BattleAnimationLevel::FadeOut, this, 0.15f));
		TimeEvent.AddEvent(0.4f, std::bind(&BattleAnimationLevel::End, this));
		}
	, false, 0.3f);

	NewEvent->PushEvent([=] {
		NewEvent->Portrait1->Off();
		NewEvent->Dialogue->Off();
		UI->On();
		}
	, false, 0.0f);
	DeathEvent.insert(std::pair<UnitIdentityCode, std::shared_ptr<EventSystem>>(_Code, NewEvent));
}

void BattleAnimationLevel::NewEnemyDeathEvent(UnitIdentityCode _Code, std::string _Name, std::vector<std::wstring_view> _Script)
{
	std::shared_ptr<EventSystem> NewEvent = CreateActor<EventSystem>();
	NewEvent->PushEvent([=] {
		UI->Off();
		NewEvent->Portrait2->SetTexture("Portrait_" + _Name + ".png");
		NewEvent->Portrait2->On();
		NewEvent->Dialogue->SetSize({ 20, 5 });
		NewEvent->Dialogue->SetFadeIn(0.5f);
		NewEvent->Dialogue->GetTransform()->SetLocalPosition({ -344, -160 });
		}
	, false, 0.5f);

	for (int i = 0; i < _Script.size(); i++)
	{
		NewEvent->PushEvent([=] {
			NewEvent->Dialogue->Text->SetTextAnim(_Script[i]);
			}
		, true, 0.5f);
	}

	NewEvent->PushEvent([=] {
		TimeEvent.AddEvent(0.1f, std::bind(&BattleAnimationLevel::FadeOut, this, 0.15f));
		TimeEvent.AddEvent(0.4f, std::bind(&BattleAnimationLevel::End, this));
		}
	, false, 0.3f);

	NewEvent->PushEvent([=] {
		NewEvent->Portrait1->Off();
		NewEvent->Dialogue->Off();
		UI->On();
		}
	, false, 0.0f);
	DeathEvent.insert(std::pair<UnitIdentityCode, std::shared_ptr<EventSystem>>(_Code, NewEvent));
}

void BattleAnimationLevel::EventInit()
{
	NewPlayerDeathEvent(UnitIdentityCode::Lyn, "Lyn", { L"...말도 안 돼\n미안해... 마크...", L"다들... 용서해줘......" });
	NewPlayerDeathEvent(UnitIdentityCode::BladeLordLyn, "Lyn", { L"...말도 안 돼\n미안해... 마크...", L"다들... 용서해줘......" });
	NewPlayerDeathEvent(UnitIdentityCode::Kent, "Kent", { L"아... 내가 지다니..." });
	NewPlayerDeathEvent(UnitIdentityCode::Sain, "Sain", { L"나는 할만큼 했어...\n 뒤는 맡길게" });
	NewPlayerDeathEvent(UnitIdentityCode::Florina, "Florina", { L"으아아아아!!!", L"린 미안해... 나는 후퇴할게"});
	NewPlayerDeathEvent(UnitIdentityCode::Wil, "Wil", { L"아... 끝났어..."});
	NewPlayerDeathEvent(UnitIdentityCode::Dorcas, "Dorcas", { L"큭... 여기까지 인가"});
	NewPlayerDeathEvent(UnitIdentityCode::WarriorDorcas, "Dorcas", { L"큭... 여기까지 인가"});
	NewPlayerDeathEvent(UnitIdentityCode::Serra, "Serra", { L"이런! 어째서 나를 공격하는거야?", L"일단 후퇴할게!"});
	NewPlayerDeathEvent(UnitIdentityCode::Erk, "Erk", { L"린... 용서해주세요..\n잠시 쉬어야겠어요"});
	NewPlayerDeathEvent(UnitIdentityCode::Rath, "Rath", { L"이럴수가..."});
	NewPlayerDeathEvent(UnitIdentityCode::Matthew, "Matthew", { L"젠장... 진건가..."});
	NewPlayerDeathEvent(UnitIdentityCode::AssassinMatthew, "Matthew", { L"젠장... 진건가..."});
	NewPlayerDeathEvent(UnitIdentityCode::Lucius, "Lucius", { L"아아... 신이시여..."});
	NewPlayerDeathEvent(UnitIdentityCode::Ninian, "Ninian", { L"미안해요... 린..."});
	NewPlayerDeathEvent(UnitIdentityCode::Wallace, "Wallace", { L"윽! 갑옷에 너무 의존했나보군", L"린... 미안하다"});

	NewEnemyDeathEvent(UnitIdentityCode::Batta, "Batta", { L"말도 안 돼...\n내가 지다니..."});
	NewEnemyDeathEvent(UnitIdentityCode::Zugu, "Zugu", { L"제, 젠자앙...", L"계집 한명이라고...\n했었잖아... 으윽"});

}
