#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include "GameEngineFolderImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <map>

// ���� :
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}
	
	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline void SetPivotType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}

	// �̹����� ũ���� ���
	void SetImageScale();

	// ������ ������ ũ���� ���
	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	inline GameEngineImage* GetImage()
	{
		return Image_;
	}

	void SetImage(const std::string& _Name);

	void SetIndex(size_t _Index, const float4& _Scale = {-1.0f, -1.0f });

	inline void CameraEffectOff()
	{
		IsCameraEffect_ = false;
	}

	inline void CameraEffectOn()
	{
		IsCameraEffect_ = true;
	}

	// �������� ������ ���� Order����
	void SetOrder(int _Order) override;

protected:
	void Render();

private:
	friend class FrameAnimation;

	// ī�޶� ȿ�� �������
	bool IsCameraEffect_;

	// ����� �̹���
	GameEngineImage* Image_;
	// ����� �̹����� ������(Pivot)
	RenderPivot PivotType_;
	// �̹���ũ���� �Ǵ� ����ڰ� ������ ũ���
	RenderScaleMode ScaleMode_;

	// ȭ�鿡 �������� �̹����� ��ġ
	float4 RenderPivot_;
	// �������� �̹����� ũ��
	float4 RenderScale_;

	// �����Ϸ��� ����� ũ��
	float4 RenderImageScale_;
	// �����Ϸ��� ����� ������
	float4 RenderImagePivot_;

	unsigned int TransColor_;



/////////////////////////////// �ִϸ��̼� Ŭ����
private:
	class FrameAnimation : public GameEngineNameObject
	{
	public:
		GameEngineRenderer* Renderer_;
		GameEngineImage* Image_;
		GameEngineFolderImage* FolderImage_;
		int CurrentFrame_;
		int StartFrame_;
		int EndFrame_;
		float CurrentInterTime_;
		float InterTime_;
		bool Loop_ = false;
		bool IsEnd;

	public:
		FrameAnimation()
			: Image_(nullptr),
			CurrentFrame_(-1),
			StartFrame_(-1),
			EndFrame_(-1),
			CurrentInterTime_(0.1f),
			InterTime_(0.1f),
			Loop_(true)

		{

		}

	public:
		void Update();

		void Reset()
		{
			IsEnd = false;
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;
		}
	};

public:
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	void CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	void ChangeAnimation(const std::string& _Name);

	bool IsEndAnimation();

	bool IsAnimationName(const std::string& _Name);

private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;
};