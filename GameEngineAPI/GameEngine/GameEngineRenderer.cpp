#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEngineDebug.h>

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)
	, TransColor_(RGB(255, 0, 255))	// 마젠타
	, RenderImagePivot_({0, 0})
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
	RenderImageScale_ = Image_->GetScale();
}

// 이미지 설정
void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);

	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + DEBUG_MSG_IMAGE_NOT_EXIST_SET_RENDERER);
		return;
	}

	Image_ = FindImage;
	SetImageScale();
}

// 그리기
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


void GameEngineRenderer::SetIndex(size_t _Index, float4 _Scale)
{
	// 이미지가 잘려져있지 않은 원본 상태
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("이미지를 부분적으로 사용할수 있게 잘려지있지 않은 이미지 입니다.");
		return;
	}

	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	RenderScale_ = Image_->GetCutScale(_Index);
	RenderImageScale_ = Image_->GetCutScale(_Index);

	// _Scale가 없을 경우 이미지 크기대로 출력
	if (-1.0f == _Scale.x ||
		-1.0f == _Scale.y)
	{
		RenderScale_ = Image_->GetCutScale(_Index);
	}
	else
	{
		RenderScale_ = _Scale;
	}
}