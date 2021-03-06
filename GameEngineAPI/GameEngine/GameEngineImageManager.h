#pragma once
#include "GameEngineImage.h"
#include "GameEngineFolderImage.h"
#include <GameEngineBase/GameEngineMath.h>
#include <map>

// 설명 :
class GameEngineImageManager
{
private:
	static GameEngineImageManager* Inst_;

public:
	static GameEngineImageManager* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr == Inst_)
		{
			return;
		}

		delete Inst_;
		Inst_ = nullptr;
	}

	// AllRes에서 이미지 찾기
	GameEngineImage* Find(const std::string& _Name);

	// 비어있는 이미지를 생성
	GameEngineImage* Create(const std::string& _Name, const float4 _Scale);
	GameEngineImage* Create(const std::string& _Name, HDC _DC);

	// 이미지 로드
	GameEngineImage* Load(const std::string& _Path);
	GameEngineImage* Load(const std::string& _Path, const std::string& _Name);

private:
	// 생성된 이미지를 모두 저장하는 map
	std::map<std::string, GameEngineImage*> AllRes;

// 폴더 이미지
public:
	GameEngineFolderImage* FolderImageFind(const std::string& _Name);
	GameEngineFolderImage* FolderImageLoad(const std::string& _Path);
	GameEngineFolderImage* FolderImageLoad(const std::string& _Path, const std::string& _Name);


private:
	std::map<std::string, GameEngineFolderImage*> AllFolderRes;

private:
	// constrcuter destructer
	GameEngineImageManager();
	~GameEngineImageManager();

	// delete Function
	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;

};

