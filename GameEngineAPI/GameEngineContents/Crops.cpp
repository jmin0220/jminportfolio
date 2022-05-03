#include "Crops.h"

Crops::Crops() 
	: VibrateFlg(false)
{
	RandomItem_ = new GameEngineRandom();
	VibratePivot_ = new GameEngineRandom();
}

Crops::~Crops() 
{
	delete RandomItem_;
	RandomItem_ = nullptr;

	delete VibratePivot_;
	VibratePivot_ = nullptr;
}

void Crops::Destroy()
{
	this->Death();
}


void Crops::SetVibrate(bool _Flg)
{
	ReSetAccTime();

	VibrateFlg = _Flg;
}

void Crops::UpdateVibrate()
{
	// Áøµ¿ÇßÀ¸¸é ¸ØÃã
	if (GetAccTime() >= 0.3f)
	{
		VibrateFlg = false;
		this->GetRenderer()->SetPivot({ 0.0f, 0.0f });

		return;
	}
	if (true == VibrateFlg)
	{
		// ÇÇº¿À» Áøµ¿½ÃÅ°±â
		this->GetRenderer()->SetPivot({ VibratePivot_->RandomFloat(-2.0f, 2.0f)
									, VibratePivot_->RandomFloat(-2.0f, 2.0f) });
	}
	
}