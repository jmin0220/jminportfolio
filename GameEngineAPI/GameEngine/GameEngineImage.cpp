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
	// HDC�� HBITMAP(2�����迭 �ڵ�)�� �׻� ����Ǿ�����. nullptr������ HBITMAP(���� ���÷���)�ϳ��� ����Ǿ�����.
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("Make ImageDC failure");
	}

	// ������ DC�� ����Ǿ��ִ� HBITMAP(OldBitMap_)�� �ٸ� HBITMAP(BitMap_)�� �����ϰ� ����HBITMAP�� ��ȯ
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

bool GameEngineImage::Load(const std::string& _Path)
{
	// _Path�κ��� �̹����� �ε�
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
		MsgBoxAssertString(_Path + " �̹��� �ε忡 �����߽��ϴ�.");
	}

	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDc ������ �����߽��ϴ�.");
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

void GameEngineImage::ImageScaleCheck()
{
	// DC ���ο� ���ǰ��ִ� ���� ��Ʈ���� ���
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);

	// CurrentBitMap�� ������ Info_�� ����
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}


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