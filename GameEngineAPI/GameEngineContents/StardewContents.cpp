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
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_TMP);

	// �����ȿ� ��� �̹��� ������ ã�´�.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile(IMAGE_EXT_BMP);

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}
	// GameEngineImageManager::GetInst()->Load("C:\\Users\\JungminLee\\Documents\\assortrock\\portfolio\\jminportfolio\\GameEngineAPI\\Resources\\Image\\Idle.bmp", "Idle.bmp");
	// GameEngineImageManager::GetInst()->Load("C:\\Users\\JungminLee\\Documents\\assortrock\\portfolio\\jminportfolio\\resource\\textures_bmp\\environment\\Bushes.bmp", "Bushes.bmp");

	// ���� ����
	CreateLevel<TitleLevel>(LEVEL_TITLE);
	CreateLevel<PlayLevel>(LEVEL_PLAY);
	CreateLevel<EndingLevel>(LEVEL_ENDING);

	// ���۷���
	ChangeLevel(LEVEL_TITLE);
}

void StardewContents::GameLoop()
{

}

void StardewContents::GameEnd()
{

}