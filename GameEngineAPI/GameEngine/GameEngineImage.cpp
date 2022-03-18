#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage()
	: ImageDC_(nullptr)
{
}

GameEngineImage::~GameEngineImage() 
{
	// window���� �Ҵ��ؿ� �������� ������ üũ�� �ȵ����� �������ٰ�.
	// �翬�� �����쿡�� �Ҵ��ؿ����Ƿ� �������� �Լ��� �̿��ؼ� ��������.
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
	// DC ���ο� ���ǰ��ִ� ���� ��Ʈ���� ���
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);

	// BitMap_�� ������ Info_�� ����
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, { 0, 0 }, _Other->GetScale());
}

// �ٸ� �̹����� ���ͼ�
void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
	// DC -> DC���� �Լ�
	BitBlt(
		ImageDC_,              // �ٿ��ֱ� �� ����
		_CopyPos.ix(),         // �ٿ��ֱ��� �̹����� ��ġ x
		_CopyPos.iy(),	       // �ٿ��ֱ��� �̹����� ��ġ y
		_OtherPivotScale.ix(), // �� �̹����� �� ũ�⸸ŭ x
		_OtherPivotScale.iy(), // �� �̹����� �� ũ�⸸ŭ y
		_Other->ImageDC_,      // ������ ����
		_OtherPivot.ix(),      // ������ �̹����� ������X
		_OtherPivot.iy(),      // ������ �̹����� ������Y
		SRCCOPY                // �����϶�� ��ɾ�
	);
}