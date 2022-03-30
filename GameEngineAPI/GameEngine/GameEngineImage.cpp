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
		MsgBoxAssert(DEBUG_MSG_IMAGE_CREATE_ZEROSIZE);
		return false;
	}

	// 이미지 크기와 동일한 비트맵 생성
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

	// DC생성
	// HDC는 HBITMAP(2차원배열 핸들)과 항상 연결되어있음. nullptr이지만 HBITMAP(현재 디스플레이)하나와 연결되어있음.
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert(DEBUG_MSG_DC_CREATE_FAILURE);
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
		MsgBoxAssertString(_Path + DEBUG_MSG_IMAGE_LOAD_FAILURE);
	}

	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert(DEBUG_MSG_DC_CREATE_FAILURE);
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


/// BitCopy
void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{
	// DC -> DC복사 함수
	BitBlt(
		ImageDC_,              // 붙여넣기 할 변수
		_CopyPos.ix(),         // 붙여넣기할 이미지의 위치 x
		_CopyPos.iy(),	       // 붙여넣기할 이미지의 위치 y
		_CopyScale.ix(), // 내 이미지의 이 크기만큼 x
		_CopyScale.iy(), // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_,      // 복사할 변수
		_OtherPivot.ix(),      // 복사할 이미지의 시작점X
		_OtherPivot.iy(),      // 복사할 이미지의 시작점Y
		SRCCOPY                // 복사하라는 명령어
	);
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, _Other->GetScale(), { 0, 0 });
}




/// TranseCopy
void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
	const float4& _CopyScale,
	const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
	// DC -> DC복사 함수
	TransparentBlt(
		ImageDC_,              // 붙여넣기 할 변수
		_CopyPos.ix(),         // 붙여넣기할 이미지의 위치 x
		_CopyPos.iy(),	       // 붙여넣기할 이미지의 위치 y
		_CopyScale.ix(),       // 내 이미지의 이 크기만큼 x
		_CopyScale.iy(),       // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_,      // 복사할 변수
		_OtherPivot.ix(),      // 복사할 이미지의 시작점X
		_OtherPivot.iy(),      // 복사할 이미지의 시작점Y
		_OtherScale.ix(),      // 복사하려는 대상의 시작점X
		_OtherScale.iy(),      // 복사하려는 대상의 시작점Y
		_TransColor                // 복사하라는 명령어
	);
}

void GameEngineImage::CutCount(int _x, int _y)
{
	float4 Scale = { GetScale().x / _x, GetScale().y / _y };
	Cut(Scale);
}

void GameEngineImage::Cut(const float4& _CutSize)
{
	// 크기가 나누어 떨어지지 않는 경우 에러
	if (0 != (GetScale().ix() % _CutSize.ix()))
	{
		MsgBoxAssert(DEBUG_MSG_IMAGE_NOT_DIVISIBLE_SCALE);
	}

	if (0 != (GetScale().iy() % _CutSize.iy()))
	{
		MsgBoxAssert(DEBUG_MSG_IMAGE_NOT_DIVISIBLE_SCALE);
	}

	int XCount = GetScale().ix() / _CutSize.ix();
	int YCount = GetScale().iy() / _CutSize.iy();

	for (int y = 0; y < YCount; y++)
	{
		for (int x = 0; x < XCount; x++)
		{
			CutPivot_.push_back({ static_cast<float>(x * _CutSize.ix()), static_cast<float>(y * _CutSize.iy()) });
			CutScale_.push_back(_CutSize);
		}
	}
}

// DC에서 범위의 픽셀을 취득
int GameEngineImage::GetImagePixel(int _x, int _y)
{
	return GetPixel(ImageDC_, _x, _y);
}