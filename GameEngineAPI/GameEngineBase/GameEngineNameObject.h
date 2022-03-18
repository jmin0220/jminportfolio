#pragma once
#include <string>

// 설명 : map에 사용될 key값을 생성.
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

	// 반환할때 string이 복사되지 않도록 할때.
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

