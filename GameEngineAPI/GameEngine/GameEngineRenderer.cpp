#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEngineDebug.h>

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)
	, TransColor_(RGB(255, 0, 255))	// ����Ÿ
	, RenderImagePivot_({0, 0})
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

// �̹����� ���� ũ��� ���
void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert(DEBUG_MSG_IMAGE_NOT_EXIST);
		return;
	}

	ScaleMode_ = RenderScaleMode::Image;
	RenderScale_ = Image_->GetScale();
	RenderImageScale_ = Image_->GetScale();
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);

	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + DEBUG_MSG_IMAGE_NOT_EXIST_SET_RENDERER);
		return;
	}

	Image_ = FindImage;
}

void GameEngineRenderer::Render()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert(DEBUG_MSG_IMAGE_NOT_SET_RENDERER);
		return;
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	case RenderPivot::BOT:
		break;
	default:
		break;
	}
}


void GameEngineRenderer::SetIndex(size_t _Index)
{
	// �̹����� �߷������� ���� ���� ����
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("�̹����� �κ������� ����Ҽ� �ְ� �߷������� ���� �̹��� �Դϴ�.");
		return;
	}

	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	RenderScale_ = Image_->GetCutScale(_Index);
	RenderImageScale_ = Image_->GetCutScale(_Index);
}