#pragma once
#include <string>

// ���� : map�� ���� key���� ����.
class GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineNameObject();
	~GameEngineNameObject();

	// delete Function
	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;

	inline void SetName(std::string _Name)
	{
		Name_ = _Name;
	}

	std::string GetNameCopy()
	{
		return Name_;
	}

	// ��ȯ�Ҷ� string�� ������� �ʵ��� �Ҷ�.
	const std::string& GetNameConstRef()
	{
		return Name_;
	}

	const char* GetNameConstPtr()
	{
		return Name_.c_str();
	}

protected:

private:
	std::string Name_;
};

