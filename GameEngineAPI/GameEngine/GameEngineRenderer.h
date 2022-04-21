#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include "GameEngineFolderImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <map>

// 설명 :
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

	// 이미지의 크기대로 출력
	void SetImageScale();

	inline float4 GetImageScale()
	{
		return RenderImageScale_;
	}

	// 유저가 설정한 크기대로 출력
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

	// 알파값
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

	// 렌더러가 생성된 후의 Order설정
	void SetOrder(int _Order) override;

protected:
	void Render();

private:
	friend class FrameAnimation;

	// 카메라 효과 사용유무
	bool IsCameraEffect_;
	bool Pause_;

	// 출력할 이미지
	GameEngineImage* Image_;
	// 출력할 이미지의 기준점(Pivot)
	RenderPivot PivotType_;
	// 이미지크기대로 또는 사용자가 설정한 크기로
	RenderScaleMode ScaleMode_;

	// 화면에 렌더링할 이미지의 위치
	float4 RenderPivot_;
	// 렌더링할 이미지의 크기
	float4 RenderScale_;

	// 복사하려는 대상의 크기
	float4 RenderImageScale_;
	// 복사하려는 대상의 기준점
	float4 RenderImagePivot_;

	unsigned int TransColor_;
	unsigned int Alpha_;

	/// ////////////////////////////////////////////// 회전용 트랜스 이미지

	float RotZ_;
	GameEngineImage* RotationFilterImage_;

public:
	void SetRotationFilter(const std::string& _ImageName);

	void SetRotationZ(float _RotZ)
	{
		RotZ_ = _RotZ;
		Alpha_ = 255;
	}


/////////////////////////////// 애니메이션 클래스
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