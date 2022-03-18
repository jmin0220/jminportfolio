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

	// �̹��� ũ��� ������ ��Ʈ�� ����
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

	// DC����
	// DC�� HBITMAP�� ������ �� �ִ� ����
	// HDC�� HBITMAP(2�����迭 �ڵ�)�� �׻� ����Ǿ�����. nullptr������ HBITMAP�ϳ��� ����Ǿ�����.
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("Make ImageDC failure");
	}

	// ������ DC�� ����Ǿ��ִ� HBITMAP�� �ٸ� HBITMAP�� �����ϰ� ����HBITMAP�� ��ȯ
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}


void GameEngineImage::ImageScaleCheck()
{
	// BitMap_�� ������ Info_�� ����
	GetObject(BitMap_, sizeof(BITMAP), &Info_);
}