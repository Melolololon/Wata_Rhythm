#pragma once
#include <array>
#include <unordered_map>
#include <string>
#include "CheckPushKey.h"

class ScoreManger
{
private:

public:

	static ScoreManger* GetInstance();

public:
	void Initialize();
	void Update();
	void Finalize();
	std::unordered_map<std::wstring, std::unordered_map<CheckPushKey::JudgmentType, unsigned short>> scores;

	void Save(std::wstring musicName, std::unordered_map<CheckPushKey::JudgmentType, unsigned short> score);

	std::unordered_map<CheckPushKey::JudgmentType, unsigned short> Get(std::wstring musicName);

public:
	ScoreManger() = default;
	ScoreManger(const ScoreManger&) = delete;
	~ScoreManger() = default;
	ScoreManger operator=(const ScoreManger&) = delete;
};