#include "GameEngineMath.h"

GameEngineMath::GameEngineMath() 
{
}

GameEngineMath::~GameEngineMath() 
{
}

// 이동속도 설정
float4 float4::LEFT = { -MATH_VERTICAL_SPD, 0.0f, 0.0f, 1.0f };
float4 float4::RIGHT = { MATH_VERTICAL_SPD, 0.0f, 0.0f, 1.0f };
float4 float4::UP = { 0.0f, -MATH_HORIZON_SPD, 0.0f, MATH_HORIZON_SPD };
float4 float4::DOWN = { 0.0f, MATH_HORIZON_SPD, 0.0f, MATH_HORIZON_SPD };