#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEngineDebug.h>

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)
	, TransColor_(RGB(255, 0, 255))
	//, TransColor_(RGB(255, 0, 255))
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

// 이미지의 원래 크기로 출력
void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert(DEBUG_MSG_IMAGE_NOT_EXIST);
		return;
	}

	ScaleMode_ = RenderScaleMode::Image;
	RenderScale_ = Image_->GetScale();
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
		GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale_, TransColor_);
		break;
	case RenderPivot::BOT:
		break;
	default:
		break;
	}
}