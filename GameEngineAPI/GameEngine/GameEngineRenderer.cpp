#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)
	, TransColor_(RGB(255, 0, 255))	// ����Ÿ
	, RenderImagePivot_({0, 0})
	, IsCameraEffect_(true)
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
		MsgBoxAssert("This Image is not Exist");
		return;
	}

	ScaleMode_ = RenderScaleMode::Image;
	RenderScale_ = Image_->GetScale();
	RenderImageScale_ = Image_->GetScale();
}

// �̹��� ����
void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);

	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + " Tried to Set a Non-Existent Image on the Renderer");
		return;
	}

	Image_ = FindImage;
	SetImageScale();
}

// �׸���
void GameEngineRenderer::Render()
{
	if (nullptr != CurrentAnimation_)
	{
		CurrentAnimation_->Update();
	}

	if (nullptr == Image_)
	{
		MsgBoxAssert(" Tried to Set a Non-Existent Image on the Renderer");
		return;
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	if (true == IsCameraEffect_)
	{
		RenderPos -= GetActor()->GetLevel()->GetCameraPos();
	}

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	case RenderPivot::BOT:
	{
		float4 Scale = RenderScale_.Half();
		Scale.y *= 2.0f;
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
	}
		break;
	default:
		break;
	}
}


void GameEngineRenderer::SetIndex(size_t _Index, const float4& _Scale)
{
	// �̹����� �߷������� ���� ���� ����
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("�̹����� �κ������� ����Ҽ� �ְ� �߷������� ���� �̹��� �Դϴ�.");
		return;
	}

	// _Scale�� ���������� �������, Cut�Ҷ� ������ �����Ϸ� ���
	if (_Scale.x <= 0 || _Scale.y <= 0)
	{
		RenderScale_ = Image_->GetCutScale(_Index);
	}
	// ������ _Scale�� ���
	else
	{
		RenderScale_ = _Scale;
	}

	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	RenderImageScale_ = Image_->GetCutScale(_Index);
}



/////////////////////////////////////// �ִϸ��̼�


// �ִϸ��̼� ��ȯ
void GameEngineRenderer::ChangeAnimation(const std::string& _Name)
{
	std::map<std::string, FrameAnimation>::iterator FindIter = Animations_.find(_Name);

	if (Animations_.end() == FindIter)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü���� �Ϸ��� �߽��ϴ�.");
		return;
	}

	CurrentAnimation_ = &FindIter->second;
}

// �ִϸ��̼� ����
void GameEngineRenderer::CreateAnimation(
	const std::string& _Image,
	const std::string& _Name,
	int _StartIndex,
	int _EndIndex,
	float _InterTime,
	bool _Loop /*= true*/)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Image);

	if (nullptr == FindImage)
	{
		MsgBoxAssert("�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� �� ������� �߽��ϴ�..");
		return;
	}

	//FrameAnimation Animation;
	FrameAnimation& NewAnimation = Animations_[_Name];

	NewAnimation.SetName(_Name);
	NewAnimation.Renderer_ = this;
	NewAnimation.Image_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;
}


void GameEngineRenderer::CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop /*= true*/)
{
	GameEngineFolderImage* FindImage = GameEngineImageManager::GetInst()->FolderImageFind(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� �� ������� �߽��ϴ�.");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];

	NewAnimation.SetName(_Name);
	NewAnimation.Renderer_ = this;
	NewAnimation.FolderImage_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;

}

void GameEngineRenderer::FrameAnimation::Update()
{
	IsEnd = false;
	CurrentInterTime_ -= GameEngineTime::GetInst()->GetDeltaTime();
	if (0 >= CurrentInterTime_)
	{
		CurrentInterTime_ = InterTime_;
		++CurrentFrame_;

		if (EndFrame_ < CurrentFrame_)
		{
			if (true == Loop_)
			{
				IsEnd = true;
				CurrentFrame_ = StartFrame_;
			}
			else
			{
				IsEnd = true;
				CurrentFrame_ = EndFrame_;
			}
		}
	}

	if (nullptr != Image_)
	{
		// ���������� �ִϸ��̼� ���鶧 �����ߴ� �̹����� ����
		Renderer_->Image_ = Image_;		

		// ���������� ������� �ε��� ����
		Renderer_->SetIndex(CurrentFrame_);	
	}
	else if (nullptr != FolderImage_)
	{
		Renderer_->Image_ = FolderImage_->GetImage(CurrentFrame_);
		Renderer_->SetImageScale();
	}
}

void GameEngineRenderer::SetOrder(int _Order)
{
	if (nullptr == GetActor())
	{
		MsgBoxAssert("���Ͱ� ���õ��� �ʽ��ϴ�.");
	}

	if (nullptr == GetActor()->GetLevel())
	{
		MsgBoxAssert("������ ���õ��� �ʾҽ��ϴ�.");
	}

	if (_Order == GetOrder())
	{
		return;
	}

	GetActor()->GetLevel()->ChangeRenderOrder(this, _Order);
}

bool GameEngineRenderer::IsEndAnimation()
{
	return CurrentAnimation_->IsEnd;
}

bool GameEngineRenderer::IsAnimationName(const std::string& _Name)
{
	return CurrentAnimation_->GetNameConstRef() == _Name;
}