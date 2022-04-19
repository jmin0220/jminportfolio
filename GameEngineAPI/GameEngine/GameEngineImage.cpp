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
		MsgBoxAssert("You tried Create 0 Size Image");
		return false;
	}

	// �̹��� ũ��� ������ ��Ʈ�� ����
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

	// DC����
	// HDC�� HBITMAP(2�����迭 �ڵ�)�� �׻� ����Ǿ�����. nullptr������ HBITMAP(���� ���÷���)�ϳ��� ����Ǿ�����.
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("Create ImageDC failure");
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
		MsgBoxAssertString(_Path + " Image Load Failure");
	}

	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("Create ImageDC failure");
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


/// BitCopy
void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{
	// DC -> DC���� �Լ�
	BitBlt(
		ImageDC_,              // �ٿ��ֱ� �� ����
		_CopyPos.ix(),         // �ٿ��ֱ��� �̹����� ��ġ x
		_CopyPos.iy(),	       // �ٿ��ֱ��� �̹����� ��ġ y
		_CopyScale.ix(), // �� �̹����� �� ũ�⸸ŭ x
		_CopyScale.iy(), // �� �̹����� �� ũ�⸸ŭ y
		_Other->ImageDC_,      // ������ ����
		_OtherPivot.ix(),      // ������ �̹����� ������X
		_OtherPivot.iy(),      // ������ �̹����� ������Y
		SRCCOPY                // �����϶�� ��ɾ�
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
	// DC -> DC���� �Լ�
	TransparentBlt(
		ImageDC_,              // �ٿ��ֱ� �� ����
		_CopyPos.ix(),         // �ٿ��ֱ��� �̹����� ��ġ x
		_CopyPos.iy(),	       // �ٿ��ֱ��� �̹����� ��ġ y
		_CopyScale.ix(),       // �� �̹����� �� ũ�⸸ŭ x
		_CopyScale.iy(),       // �� �̹����� �� ũ�⸸ŭ y
		_Other->ImageDC_,      // ������ ����
		_OtherPivot.ix(),      // ������ �̹����� ������X
		_OtherPivot.iy(),      // ������ �̹����� ������Y
		_OtherScale.ix(),      // �����Ϸ��� ����� ������X
		_OtherScale.iy(),      // �����Ϸ��� ����� ������Y
		_TransColor                // �����϶�� ��ɾ�
	);
}


void GameEngineImage::AlphaCopy(GameEngineImage* _Other, const float4& _CopyPos,
	const float4& _CopyScale,
	const float4& _OtherPivot, const float4& _OtherScale, unsigned int _Alpha)
{
	BLENDFUNCTION Func;
	Func.BlendOp = AC_SRC_OVER;
	Func.BlendFlags = 0;
	Func.SourceConstantAlpha = _Alpha;
	Func.AlphaFormat = AC_SRC_ALPHA;


	AlphaBlend(
		ImageDC_, // ���⿡ ����(�츮 �������̹���)
		_CopyPos.ix(), // ������ �̹����� ��ġ x�������� y
		_CopyPos.iy(), // ������ �̹����� ��ġ x�������� y
		_CopyScale.ix(), // �� �̹����� �� ũ�⸸ŭ x
		_CopyScale.iy(), // �� �̹����� �� ũ�⸸ŭ y
		_Other->ImageDC_, // �����Ϸ��� �����(�ű⿡ �׷����� �̹����� ����?Ŀ��)
		_OtherPivot.ix(), // �����Ϸ��� ����� ������X ��ġ
		_OtherPivot.iy(),// �����Ϸ��� ����� ������Y
		_OtherScale.ix(), // �����Ϸ��� ����� ������X ũ��
		_OtherScale.iy(),// �����Ϸ��� ����� ������Y
		Func // �����϶�� ���
	);

}

void GameEngineImage::PlgCopy(GameEngineImage* _Other, GameEngineImage* _Filter)
{
	POINT Test;

	PlgBlt(
		ImageDC_, // ���⿡ ����(�츮 �������̹���)
		&Test,
		_Other->ImageDC_,
		0, // ������ �̹����� ��ġ x�������� y
		0, // ������ �̹����� ��ġ x�������� y
		0, // �� �̹����� �� ũ�⸸ŭ x
		0, // �� �̹����� �� ũ�⸸ŭ y
		_Filter->BitMap_, // �����Ϸ��� �����(�ű⿡ �׷����� �̹����� ����?Ŀ��)
		0, // �����Ϸ��� ����� ������X ��ġ
		0// �����Ϸ��� ����� ������Y
	);
}

void GameEngineImage::CutCount(int _x, int _y)
{
	float4 Scale = { GetScale().x / _x, GetScale().y / _y };
	Cut(Scale);
}

void GameEngineImage::Cut(const float4& _CutSize)
{
	// ũ�Ⱑ ������ �������� �ʴ� ��� ����
	if (0 != (GetScale().ix() % _CutSize.ix()))
	{
		MsgBoxAssert("Scale is Not Divisible Number");
	}

	if (0 != (GetScale().iy() % _CutSize.iy()))
	{
		MsgBoxAssert("Scale is Not Divisible Number");
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

// DC���� ������ �ȼ��� ���
int GameEngineImage::GetImagePixel(int _x, int _y)
{
	// ȭ�� �ٱ��ϰ��
	if (0 > _x)
	{
		return RGB(0, 0, 0);
	}

	if (0 > _y)
	{
		return RGB(0, 0, 0);
	}

	if (GetScale().ix() <= _x)
	{
		return RGB(0, 0, 0);
	}

	if (GetScale().iy() <= _y)
	{
		return RGB(0, 0, 0);
	}

	return GetPixel(ImageDC_, _x, _y);
}