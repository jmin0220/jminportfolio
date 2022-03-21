#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage()
	: ImageDC_(nullptr)
{
}

GameEngineImage::~GameEngineImage() 
{
	// window에서 할당해온 변수들은 릭으로 체크가 안되지만 삭제해줄것.
	// 당연히 윈도우에게 할당해왔으므로 윈도우의 함수를 이용해서 지워야함.
	if (nullptr != BitMap_)
	{
		DeleteObject(BitMap_);
		BitMap_ = nullptr;
	}

	if (nullptr != OldBitMap_)
	{
		DeleteObject(OldBitMap_);
		OldBitMap_ = nullptr;
	}

	if (nullptr != ImageDC_)
	{
		DeleteDC(ImageDC_);
		ImageDC_ = nullptr;
	}
}

bool GameEngineImage::Create(HDC _DC)
{
	ImageDC_ = _DC;

	ImageScaleCheck();

	return true;
}

bool GameEngineImage::Create(float4 _Scale)
{
	if (true == _Scale.IsZero2D())
	{
		MsgBoxAssert("You tried maked 0 Size Image");
		return false;
	}

	// 이미지 크기와 동일한 비트맵 생성
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

	// DC생성
	// HDC는 HBITMAP(2차원배열 핸들)과 항상 연결되어있음. nullptr이지만 HBITMAP(현재 디스플레이)하나와 연결되어있음.
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("Make ImageDC failure");
	}

	// 이전에 DC에 연결되어있던 HBITMAP(OldBitMap_)을 다른 HBITMAP(BitMap_)에 연결하고 이전HBITMAP을 반환
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

bool GameEngineImage::Load(const std::string& _Path)
{
	// _Path로부터 이미지를 로딩
	BitMap_ = static_cast<HBITMAP>(LoadImageA(
		nullptr,
		_Path.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
	));

	if (nullptr == BitMap_)
	{
		MsgBoxAssertString(_Path + " 이미지 로드에 실패했습니다.");
	}

	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDc 생성에 실패했습니다.");
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

void GameEngineImage::ImageScaleCheck()
{
	// DC 내부에 사용되고있는 현재 비트맵을 취득
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);

	// CurrentBitMap의 정보를 Info_에 저장
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}


void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
	// DC -> DC복사 함수
	BitBlt(
		ImageDC_,              // 붙여넣기 할 변수
		_CopyPos.ix(),         // 붙여넣기할 이미지의 위치 x
		_CopyPos.iy(),	       // 붙여넣기할 이미지의 위치 y
		_OtherPivotScale.ix(), // 내 이미지의 이 크기만큼 x
		_OtherPivotScale.iy(), // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_,      // 복사할 변수
		_OtherPivot.ix(),      // 복사할 이미지의 시작점X
		_OtherPivot.iy(),      // 복사할 이미지의 시작점Y
		SRCCOPY                // 복사하라는 명령어
	);
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, { 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, float4{ 0, 0 }, _Other->GetScale());
}