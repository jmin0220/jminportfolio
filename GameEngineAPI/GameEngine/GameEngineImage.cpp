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
		MsgBoxAssert(DEBUG_MSG_IMAGE_CREATE_ZEROSIZE);
		return false;
	}

	// �̹��� ũ��� ������ ��Ʈ�� ����
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

	// DC����
	// HDC�� HBITMAP(2�����迭 �ڵ�)�� �׻� ����Ǿ�����. nullptr������ HBITMAP(���� ���÷���)�ϳ��� ����Ǿ�����.
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert(DEBUG_MSG_DC_CREATE_FAILURE);
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

void GameEngineImage::TransCopyCenterScale(GameEngineImage* _Other, const float4& _CopyPos, const float4& _RenderScale, unsigned int _TransColor)
{
	TransCopy(_Other, _CopyPos - _RenderScale.Half(), _RenderScale, float4{ 0, 0 }, _Other->GetScale(), _TransColor);
}

void GameEngineImage::TransCopyCenter(GameEngineImage* _Other, const float4& _CopyPos, unsigned int _TransColor)
{
	TransCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 }, _Other->GetScale(), _TransColor);
}