#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>
#include <vector>

// 설명 :
class GameEngineImage : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineImage();
	~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

	bool Create(float4 _Scale);
	bool Create(HDC _DC);

	bool Load(const std::string& _Path);

	inline float4 GetScale()
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}

	inline HDC ImageDC()
	{
		return ImageDC_;
	}

	// BitBlt
	void BitCopy(GameEngineImage* _Other);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot);

	void TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
                   const float4& _CopyScale, const float4& _OtherPivot,
                   const float4& _OtherScale, unsigned int _TransColor);

	// 투명도 출력
	void AlphaCopy(GameEngineImage* _Other, const float4& _CopyPos,
		const float4& _CopyScale,
		const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor);

	void PlgCopy(GameEngineImage* _Other, GameEngineImage* _Filter);

	void Cut(const float4& _CutSize);

	void CutCount(int _x, int _y);

	// 잘려져있는 이미지인가를 판별
	inline bool IsCut()
	{
		return 0 != CutPivot_.size();
	}

	// 몇장의 이미지로 잘려져있는가 취득
	inline size_t GetCutCount()
	{
		return CutPivot_.size();
	}

	// 잘려진 기준점 취득
	inline float4 GetCutPivot(size_t _Index)
	{
		return CutPivot_[_Index];
	}

	// 잘려진 기준의 스케일취득
	inline float4 GetCutScale(size_t _Index)
	{
		return CutScale_[_Index];
	}

	// 자르기
	void Cut(const float4& _CutScale, const float4& _CutPos)
	{
		CutScale_.push_back(_CutScale);
		CutPivot_.push_back(_CutPos);
	}

	// DC에서 범위의 픽셀을 취득
	inline int GetImagePixel(const float4& _Pos)
	{
		return GetImagePixel(_Pos.ix(), _Pos.iy());
	}

	int GetImagePixel(int _x, int _y);

protected:

private:
	HDC ImageDC_;
	BITMAP Info_;
	// 비트맵의 핸들
	HBITMAP BitMap_;
	HBITMAP OldBitMap_;

	std::vector<float4> CutPivot_;
	std::vector<float4> CutScale_;

	void ImageScaleCheck();
};

