#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include "FERandom.h"
void BattleLevel::TimeStone_Rewind()
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
		static std::vector<UnitCommand>::reverse_iterator NewRIter;
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
		static std::vector<UnitCommand>::reverse_iterator NewRIter;
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

void BattleLevel::TimeStone_Play()
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

void BattleLevel::TimeStone_Select()
{
	for (int i = 0; i < RewindNum; i++)
	{
		UnitCommand::PopCommandList();
	}
	ChangeState(BattleState::Select);
	return;
}

void BattleLevel::TimeStone_Cancel()
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
