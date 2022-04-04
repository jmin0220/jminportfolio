#include "GameEngineFolderImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include "GameEngineImageManager.h"

GameEngineFolderImage::GameEngineFolderImage() 
{
}

GameEngineFolderImage::~GameEngineFolderImage() 
{
}

bool GameEngineFolderImage::Load(const std::string& _Path)
{
	GameEngineDirectory ResourcesDir = GameEngineDirectory(_Path);

	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImage* Image = new GameEngineImage();

		// Image->Load();
		//Images_.push_back();
	}

	return true;
}
