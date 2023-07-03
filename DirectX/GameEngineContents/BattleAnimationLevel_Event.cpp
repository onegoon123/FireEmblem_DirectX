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
		NewEvent->Dialogue->GetTransform()->SetLocalPosition({ -396, -160 });
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
		NewEvent->Portrait2->Off();
		NewEvent->Dialogue->Off();
		UI->On();
		}
	, false, 0.0f);
	DeathEvent.insert(std::pair<UnitIdentityCode, std::shared_ptr<EventSystem>>(_Code, NewEvent));
}

void BattleAnimationLevel::NewEncounterEvent(UnitIdentityCode _Code, std::string _Name, std::vector<std::wstring_view> _Script)
{
	std::shared_ptr<EventSystem> NewEvent = CreateActor<EventSystem>();
	NewEvent->PushEvent([=] {
		UI->Off();
		NewEvent->Portrait2->SetTexture("Portrait_" + _Name + ".png");
		NewEvent->Portrait2->On();
		NewEvent->Dialogue->SetSize({ 20, 5 });
		NewEvent->Dialogue->SetFadeIn(0.5f);
		NewEvent->Dialogue->GetTransform()->SetLocalPosition({ -396, -160 });
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
		NewEvent->Portrait2->Off();
		NewEvent->Dialogue->Off();
		UI->On();
		PlayAttack();
		}
	, false, 0.0f);
	EncounterEvent.insert(std::pair<UnitIdentityCode, std::shared_ptr<EventSystem>>(_Code, NewEvent));
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

	NewEncounterEvent(UnitIdentityCode::Batta, "Batta", { L"이 바타님을 이길 수 있을거라\n생각하는거냐?"});
	NewEnemyDeathEvent(UnitIdentityCode::Batta, "Batta", { L"말도 안 돼...\n내가 지다니..."});
	NewEncounterEvent(UnitIdentityCode::Zugu, "Zugu", { L"젠자앙, 기사 놈들\n쓸데없이 방해하기는...!"});
	NewEnemyDeathEvent(UnitIdentityCode::Zugu, "Zugu", { L"제, 젠자앙", L"계집 한 명이라고...\n했었잖아아..."});
	NewEncounterEvent(UnitIdentityCode::Glass, "Glass", { L"너가 나에게 대항할 가능성이\n얼마나 된다고 생각하는거야?"});
	NewEnemyDeathEvent(UnitIdentityCode::Glass, "Glass", { L"너... 넌... 으윽"});
	NewEncounterEvent(UnitIdentityCode::Migal, "Migal", { L"덤벼라!", L"이제 와서 사과해도\n용서 못해!"});
	NewEnemyDeathEvent(UnitIdentityCode::Migal, "Migal", { L"으... 후회하게 해주마...", L"내 형제들... 가늘롱 산적단이\n복수할 것이다."});
	NewEncounterEvent(UnitIdentityCode::Carjiga, "Carjiga", { L"이녀석 강하다..\n당장 병력을 불러와!"});
	NewEnemyDeathEvent(UnitIdentityCode::Carjiga, "Carjiga", { L"으악..."});
	NewEncounterEvent(UnitIdentityCode::Bool, "Bool", { L"이녀석들 어느새 여기까지...", L"내가 처리하겠다!"});
	NewEnemyDeathEvent(UnitIdentityCode::Bool, "Bool", { L"이럴수가... 랑그렌님..."});
	NewEncounterEvent(UnitIdentityCode::Yogi, "Yogi", { L"뭐 하는가!\n어서 계집애를 잡아라!"});
	NewEnemyDeathEvent(UnitIdentityCode::Yogi, "Yogi", { L"이럴수가... 랑그렌님..."});
	NewEncounterEvent(UnitIdentityCode::Eagler, "Eagler", { L"공녀를 사칭하는 녀석들\n이 이글러가 처리한다!"});
	NewEnemyDeathEvent(UnitIdentityCode::Eagler, "Eagler", { L"어서 가라...", L"후작님을...\n키아란을 부탁한다..."});
	NewEncounterEvent(UnitIdentityCode::Lundgren, "Lundgren", { L"내 영지에\n무단으로 들어와서는...", L"살아서 여기서\n도망갈 생각은 마라!"});
	NewEnemyDeathEvent(UnitIdentityCode::Lundgren, "Lundgren", { L"야만인 따위에 내가...\n왕자는 나의 것인데..."});

}

