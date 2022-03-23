#include "StardewContents.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>

StardewContents::StardewContents() 
{
}

StardewContents::~StardewContents() 
{
}

void StardewContents::GameInit()
{
	// �������� �ʱ� ũ�� ����
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	// ���� ���丮
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("GameEngineAPI");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Image");
	ResourcesDir.Move("tmp");

	// �����ȿ� ��� �̹��� ������ ã�´�.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}
	// GameEngineImageManager::GetInst()->Load("C:\\Users\\JungminLee\\Documents\\assortrock\\portfolio\\jminportfolio\\GameEngineAPI\\Resources\\Image\\Idle.bmp", "Idle.bmp");
	// GameEngineImageManager::GetInst()->Load("C:\\Users\\JungminLee\\Documents\\assortrock\\portfolio\\jminportfolio\\resource\\textures_bmp\\environment\\Bushes.bmp", "Bushes.bmp");

	// ���� ����
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");

	// ���� ����
	ChangeLevel("Title");
}

void StardewContents::GameLoop()
{

}

void StardewContents::GameEnd()
{

}