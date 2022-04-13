#pragma once

#include <windows.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>
// ���� :
class Mouse : public GameEngineActor
{
public:

	// constrcuter destructer
	Mouse();
	~Mouse();

	// delete Function
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

protected:

public:
	GameEngineRenderer* Renderer() 
	{
		return MousePoint_;
	}

	GameEngineCollision* Collision() {
		return MouseCollision_;
	}

	void MouseOff() 
	{
		this -> Off();
	}

	bool IsMouseDown();
	bool IsMousePress();
	bool IsMouseFree();

	inline void SetHoldingItem(bool b) 
	{
		PressMouse_ = b;
	}

	inline bool GetHoldingItem() const
	{
		return PressMouse_;
	}

private:

	// ���콺 �������� ����
	POINT pt;
	// ���콺 ������ ��ġ
	float4 CursorPos_;
	// ������ ������
	GameEngineRenderer* MousePoint_;
	// ������ �浹ü
	GameEngineCollision* MouseCollision_;
	std::vector<GameEngineCollision*> ColList;

	// �����ִ��� �Ǵ�
	bool PressMouse_;

	void Start() override;
	void Update() override;
	void Render() override;

};

