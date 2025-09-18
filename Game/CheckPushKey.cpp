#include "CheckPushKey.h"

#include"MusicalScoreManager.h"


#include<TextWrite.h>

const std::unordered_map<CheckPushKey::JudgmentType, short>CheckPushKey::TIMING_FRAME =
{
    {JudgmentType::PERFECT,2},
    {JudgmentType::GREAT,4},
    {JudgmentType::GOOD,6},
    {JudgmentType::MISS,8},// 8�t���[����藣��Ă����牟���Ă��~�X�����ɂȂ�Ȃ� 7�A8�̓~�X 9���������~�X
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
    // ����m�F
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
    // ���ʂ��I����Ă�����return
    if (MusicalScoreManager::GetInstance()->GetHumenEnd())return;


    // �������ꍇ�����̃u���b�N�ɂ��Ȃ��Ƃ����Ȃ����߁A���Ԃ�NextBlock�ς���
//    if (judgmentType != JudgmentType::NONE)MusicalScoreManager::GetInstance()->ChangeNextBlock();

    if (MelLib::Input::KeyTrigger(DIK_F) || MelLib::Input::KeyTrigger(DIK_D))
    {
        // �����^�C�~���O�Ƃ̍����擾
        const unsigned int frame = MusicalScoreManager::GetInstance()->GetLeftTimingDifferenceFrame();
        timing = PushProcess(frame);
        keyTrrigerFrame = true;
    }
    else if (MelLib::Input::KeyTrigger(DIK_J) || MelLib::Input::KeyTrigger(DIK_K))
    {
        // �����^�C�~���O�Ƃ̍����擾
        const unsigned int frame = MusicalScoreManager::GetInstance()->GetRigthTimingDifferenceFrame();
        timing = PushProcess(frame);
        keyTrrigerFrame = true;
    }

    // �u���b�N���~�X��(�v���C���[�̗��������ɕK�v)
    if (timing == JudgmentType::MISS)
    {
        MusicalScoreManager::GetInstance()->TrueBlockMissFlag();
    }


    // �؂�ւ�
    if (timing != JudgmentType::NONE)MusicalScoreManager::GetInstance()->ChangeNextBlock();
}
