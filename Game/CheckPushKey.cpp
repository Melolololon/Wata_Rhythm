#include "CheckPushKey.h"

#include"MusicalScoreManager.h"


#include<TextWrite.h>

const std::unordered_map<CheckPushKey::JudgmentType, short>CheckPushKey::TIMING_FRAME =
{
    {JudgmentType::PERFECT,2},
    {JudgmentType::GREAT,4},
    {JudgmentType::GOOD,6},
    {JudgmentType::MISS,8},// 8フレームより離れていたら押してもミス扱いにならない 7、8はミス 9が見逃しミス
};
CheckPushKey::JudgmentType CheckPushKey::CheckJudgmentType(short frame)
{
    if (frame <= TIMING_FRAME.at(JudgmentType::PERFECT) && frame >= -TIMING_FRAME.at(JudgmentType::PERFECT)) return JudgmentType::PERFECT;
    if (frame <= TIMING_FRAME.at(JudgmentType::GREAT) && frame >= -TIMING_FRAME.at(JudgmentType::GREAT))return JudgmentType::GREAT;
    if (frame <= TIMING_FRAME.at(JudgmentType::GOOD) && frame >= -TIMING_FRAME.at(JudgmentType::GOOD))return JudgmentType::GOOD;
    if (frame <= TIMING_FRAME.at(JudgmentType::MISS) && frame >= -TIMING_FRAME.at(JudgmentType::MISS))return JudgmentType::MISS;
    return JudgmentType::NONE;
}

CheckPushKey::JudgmentType CheckPushKey::PushProcess(short frame)
{
    // 判定確認
    const JudgmentType judgmentType = CheckJudgmentType(frame);

   return judgmentType;
}

CheckPushKey* CheckPushKey::GetInstance()
{
    static CheckPushKey i;
    return &i;
}

void CheckPushKey::CheckTiming(JudgmentType& timing, bool& keyTrrigerFrame)
{
    // 譜面が終わっていたらreturn
    if (MusicalScoreManager::GetInstance()->GetHumenEnd())return;


    // 逃した場合も次のブロックにしないといけないため、時間でNextBlock変える
//    if (judgmentType != JudgmentType::NONE)MusicalScoreManager::GetInstance()->ChangeNextBlock();

    if (MelLib::Input::KeyTrigger(DIK_F) || MelLib::Input::KeyTrigger(DIK_D))
    {
        // 完璧タイミングとの差を取得
        const unsigned int frame = MusicalScoreManager::GetInstance()->GetLeftTimingDifferenceFrame();
        timing = PushProcess(frame);
        keyTrrigerFrame = true;
    }
    else if (MelLib::Input::KeyTrigger(DIK_J) || MelLib::Input::KeyTrigger(DIK_K))
    {
        // 完璧タイミングとの差を取得
        const unsigned int frame = MusicalScoreManager::GetInstance()->GetRigthTimingDifferenceFrame();
        timing = PushProcess(frame);
        keyTrrigerFrame = true;
    }

    // ブロックをミスに(プレイヤーの落下処理に必要)
    if (timing == JudgmentType::MISS)
    {
        MusicalScoreManager::GetInstance()->TrueBlockMissFlag();
    }


    // 切り替え
    if (timing != JudgmentType::NONE)MusicalScoreManager::GetInstance()->ChangeNextBlock();
}
