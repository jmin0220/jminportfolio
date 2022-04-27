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

	inline float4 GetPivot()
	{
		return RenderPivot_;
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

	inline float4 GetImageScale()
	{
		return RenderImageScale_;
	}

	// ������ ������ ũ���� ���
	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	inline float4 GetScale()
	{
		return RenderScale_;
	}

	inline GameEngineImage* GetImage()
	{
		return Image_;
	}

	inline float4 GetImagePivot()
	{
		return RenderImagePivot_;
	}

	inline float4 GetSortingPivot()
	{
		return GetActor()->GetPosition() + RenderPivot_ + SortingPivot;
	}

	// ���İ�
	inline void SetAlpha(unsigned int _Alpha)
	{
		Alpha_ = _Alpha;

		if (Alpha_ >= 255)
		{
			Alpha_ = 255;
		}
	}

	inline void CameraEffectOff()
	{
		IsCameraEffect_ = false;
	}

	inline void CameraEffectOn()
	{
		IsCameraEffect_ = true;
	}

	void SetPause(bool _Value)
	{
		Pause_ = _Value;
	}

	void PauseOn()
	{
		Pause_ = true;
	}

	void PauseOff()
	{
		Pause_ = false;
	}

	void PauseSwitch()
	{
		Pause_ = !Pause_;
	}

	void SetImage(const std::string& _Name);

	void SetIndex(size_t _Index, const float4& _Scale = { -1.0f, -1.0f });

	void SetImageAnimationReset(const std::string& _Name);

	// �������� ������ ���� Order����
	void SetOrder(int _Order) override;

protected:
	void Render();

private:
	friend class FrameAnimation;

	// ī�޶� ȿ�� �������
	bool IsCameraEffect_;
	bool Pause_;

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

	float4 SortingPivot;	// ����������� �̹��� ��ĭ�� ũ��

	unsigned int TransColor_;
	unsigned int Alpha_;

	/// ////////////////////////////////////////////// ȸ���� Ʈ���� �̹���

	float RotZ_;
	GameEngineImage* RotationFilterImage_;

public:
	void SetRotationFilter(const std::string& _ImageName);

	void SetRotationZ(float _RotZ)
	{
		RotZ_ = _RotZ;
		Alpha_ = 255;
	}


/////////////////////////////// �ִϸ��̼� Ŭ����
private:
	class FrameAnimation : public GameEngineNameObject
	{
	private:
		friend GameEngineRenderer;
		//friend std::map<std::string, FrameAnimation>;
		//friend std::pair<std::string, FrameAnimation>;

	public:
		GameEngineRenderer* Renderer_;
		GameEngineImage* Image_;
		GameEngineFolderImage* FolderImage_;
		int TimeKey;
		int CurrentFrame_;
		int StartFrame_;
		int EndFrame_;
		float CurrentInterTime_;
		float InterTime_;
		bool Loop_ = false;
		bool IsEnd;

	public:
		inline int WorldCurrentFrame() const
		{
			return CurrentFrame_;
		}

		inline int WorldStartFrame() const
		{
			return StartFrame_;
		}

		inline int WorldEndFrame() const
		{
			return EndFrame_;
		}

		inline int LocalCurrentFrame() const
		{
			return StartFrame_ - CurrentFrame_;
		}

	public:
		FrameAnimation()
			: Image_(nullptr),
			Renderer_(nullptr),
			FolderImage_(nullptr),
			TimeKey(0),
			CurrentFrame_(-1),
			StartFrame_(-1),
			EndFrame_(-1),
			CurrentInterTime_(0.1f),
			InterTime_(0.1f),
			Loop_(true),
			IsEnd(false)
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

	void CreateFolderAnimationTimeKey(const std::string& _Image, const std::string& _Name, int _TimeScaleKey, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	void ChangeAnimation(const std::string& _Name);

	bool IsEndAnimation();

	bool IsAnimationName(const std::string& _Name);

	const FrameAnimation* FindAnimation(const std::string& _Name);

	inline const FrameAnimation* CurrentAnimation()
	{
		return CurrentAnimation_;
	}

private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;
};