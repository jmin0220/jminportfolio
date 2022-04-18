#include "GameEngineDebug.h"

GameEngineDebug::GameEngineDebug() 
{
}

GameEngineDebug::~GameEngineDebug() 
{
}

void GameEngineDebug::LeakCheckOn()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	// 메모리릭이 발생하는 위치에 브레이크 포인트
	// _crtBreakAlloc = 13906;
}