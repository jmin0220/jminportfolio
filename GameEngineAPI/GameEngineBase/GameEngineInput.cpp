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

// 사전에 설정한 키인지 체크
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
		MsgBoxAssert(DEBUG_MSG_KEY_EXIST);
		return;
	}

	// _Key를 대문자로 변환
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
		MsgBoxAssert(DEBUG_MSG_KEY_NOT_EXIST);
		return false;
	}

	return AllInputKey_[_Name].Down_;
}

bool GameEngineInput::IsUp(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert(DEBUG_MSG_KEY_NOT_EXIST);
		return false;
	}

	return AllInputKey_[_Name].Up_;
}

bool GameEngineInput::IsPress(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert(DEBUG_MSG_KEY_NOT_EXIST);
		return false;
	}

	return AllInputKey_[_Name].Press_;
}

bool GameEngineInput::IsFree(std::string _Name)
{
	if (AllInputKey_.end() == AllInputKey_.find(_Name))
	{
		MsgBoxAssert(DEBUG_MSG_KEY_NOT_EXIST);
		return false;
	}

	return AllInputKey_[_Name].Free_;
}