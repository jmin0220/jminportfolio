#include "GameEngineInput.h"
#include "GameEngineDebug.h"

//////////////////////////////////////

void GameEngineInput::GameEngineKey::Update()
{
	if (true == KeyCheck())
	{
		if (true == Free_)
		{
			Down_ = true;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
		else if (true == Press_)
		{
			Down_ = false;
			Press_ = true;
			Up_ = false;
			Free_ = false;
		}
	}
	else
	{
		if (true == Press_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = true;
			Free_ = false;
		}
		else if (true == Up_)
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}
	}
}

//////////////////////////////////////

GameEngineInput* GameEngineInput::Inst_ = new GameEngineInput();

GameEngineInput::GameEngineInput() 
{
}

GameEngineInput::~GameEngineInput() 
{
}

// ������ ������ Ű���� üũ
bool GameEngineInput::IsKey(std::string _Name)
{
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		return true;
	}

	return false;
}

void GameEngineInput::CreateKey(std::string _Name, int _Key)
{
	if (AllInputKey_.end() != AllInputKey_.find(_Name))
	{
		MsgBoxAssert("This Key is Already exist");
		return;
	}

	// _Key�� �빮�ڷ� ��ȯ
	if ('a' <= _Key && _Key <= 'z')
	{
		_Key = std::toupper(_Key);
	}

	AllInputKey_.insert(std::make_pair(_Name, GameEngineKey()));
	AllInputKey_[_Name].Key_ = _Key;
	AllInputKey_[_Name].Reset();
}

void GameEngineInput::Update()
{
	std::map<std::string, GameEngineKey>::iterator KeyUpdateStart = AllInputKey_.begin();
	std::map<std::string, GameEngineKey>::iterator KeyUpdateEnd = AllInputKey_.end();

	for (; KeyUpdateStart != KeyUpdateEnd; ++KeyUpdateStart)
	{
		GameEngineKey& CurrentKey = KeyUpdateStart->second;

		CurrentKey.Update();
	}
}

bool GameEngineInput::IsDown(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("This Key is not Exist");
		return false;
	}

	return AllInputKey_[_Name].Down_;
}

bool GameEngineInput::IsUp(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("This Key is not Exist");
		return false;
	}

	return AllInputKey_[_Name].Up_;
}

bool GameEngineInput::IsPress(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("This Key is not Exist");
		return false;
	}

	return AllInputKey_[_Name].Press_;
}

bool GameEngineInput::IsFree(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert("This Key is not Exist");
		return false;
	}

	return AllInputKey_[_Name].Free_;
}