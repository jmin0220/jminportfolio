#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage() 
{
}

GameEngineImage::~GameEngineImage() 
{
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
	// DC는 HBITMAP을 수정할 수 있는 권한
	// HDC는 HBITMAP(2차원배열 핸들)과 항상 연결되어있음. nullptr이지만 HBITMAP하나와 연결되어있음.
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("Make ImageDC failure");
	}

	// 이전에 DC에 연결되어있던 HBITMAP을 다른 HBITMAP에 연결하고 이전HBITMAP을 반환
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}


void GameEngineImage::ImageScaleCheck()
{
	// BitMap_의 정보를 Info_에 저장
	GetObject(BitMap_, sizeof(BITMAP), &Info_);
}