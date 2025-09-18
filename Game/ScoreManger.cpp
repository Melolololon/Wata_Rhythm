#include "ScoreManger.h"

ScoreManger* ScoreManger::GetInstance()
{
    static ScoreManger instance;
    return &instance;
}

void ScoreManger::Initialize()
{
}

void ScoreManger::Update()
{
}

void ScoreManger::Finalize()
{
    scores.clear();
}

void ScoreManger::Save(std::wstring musicName, std::unordered_map<CheckPushKey::JudgmentType, unsigned short> score)
{
    scores[musicName] = score;
}

std::unordered_map<CheckPushKey::JudgmentType, unsigned short> ScoreManger::Get(std::wstring musicName)
{
    return scores[musicName];
}
