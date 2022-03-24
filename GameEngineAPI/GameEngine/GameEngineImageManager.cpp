#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEnginePath.h>

GameEngineImageManager* GameEngineImageManager::Inst_ = new GameEngineImageManager();

GameEngineImageManager::GameEngineImageManager() 
{
}

GameEngineImageManager::~GameEngineImageManager() 
{
	std::map<std::string, GameEngineImage*>::iterator StartIter = AllRes.begin();
	std::map<std::string, GameEngineImage*>::iterator EndIter = AllRes.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}
}

GameEngineImage* GameEngineImageManager::Find(const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineImage*>::iterator FindIter = AllRes.find(EngineName);

	if (AllRes.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, HDC _DC)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	if (AllRes.end() != AllRes.find(EngineName))
	{
		MsgBoxAssert(DEBUG_MSG_IMAGE_ALREADY_EXIST);
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	if (false == NewImage->Create(_DC))
	{
		delete NewImage;
		MsgBoxAssert((EngineName + DEBUG_MSG_IMAGE_CREATE_FAILURE).c_str());
		return nullptr;
	}

	AllRes.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, const float4 _Scale)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	if (AllRes.end() != AllRes.find(EngineName))
	{
		MsgBoxAssert(DEBUG_MSG_IMAGE_ALREADY_EXIST);
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((EngineName + DEBUG_MSG_IMAGE_CREATE_FAILURE).c_str());
		return nullptr;
	}

	AllRes.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path)
{
	GameEnginePath NewPath = GameEnginePath(_Path);
	return Load(_Path, NewPath.GetFileName());
}

GameEngineImage* GameEngineImageManager::Load(const std::string& _Path, const std::string& _Name)
{
	std::string EngineName = GameEngineString::ToUpperReturn(_Name);

	if (AllRes.end() != AllRes.find(EngineName))
	{
		MsgBoxAssert(DEBUG_MSG_IMAGE_ALREADY_EXIST);
		return nullptr;
	}

	GameEngineImage* NewImage = new GameEngineImage();
	NewImage->SetName(EngineName);

	if (false == NewImage->Load(_Path))
	{
		delete NewImage;
		MsgBoxAssert((EngineName + DEBUG_MSG_IMAGE_CREATE_FAILURE).c_str());
		return nullptr;
	}

	AllRes.insert(std::make_pair(EngineName, NewImage));

	return NewImage;
}