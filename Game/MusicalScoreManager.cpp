#include "MusicalScoreManager.h"
#include<fstream>
#include<filesystem>

#include<TextWrite.h>
#include<LibMath.h>

#include"CheckPushKey.h"








void MusicalScoreManager::LoadHumen(const std::wstring& musicFolderPath)
{
    nextBlockIndex = 0;
    pNextBlock = nullptr;
    changeNextBlockEnd = false;
    lastBlockPush = false;
    notPushMiss = false;
    humen.clear();
    blockIndex.clear();
    moveEndBlock.clear();
    currentHumenIndex = 0;

    std::ifstream humenFile;
    humenFile.open(musicFolderPath + L"Humen.txt");

    // ���g���擾
    size_t frameNum = 0;
    humenFile.seekg(0, std::ios_base::end);
    frameNum = humenFile.tellg();
    humenFile.seekg(0, std::ios_base::beg);

    // ���T�C�Y
    const int frameHarf = frameNum / 2;
    humen.resize(frameHarf);
    
    int addNum = 1;
    // �ǂݍ���
    for (unsigned int y = 0;; y++)
    {
        // easy��������16���𔲂�
        // 8���𔲂��Ă���������
        // easy normal hard�ł������H
        // ��U16���𔲂�
        if (easy && y % 2 == 1)
        {
            continue;
        }

        for (unsigned int x = 0; x < 2; x++)
        {
            char num = 0;
            humenFile.read(&num, 1);


            // �u���b�N�ǉ�
            if (num == '1')
            {
                bool left = !static_cast<bool>(x);
                float sPos = Block::GetStartSidePos();
                if (left)sPos = -sPos;

                // �m�[�c����
                humen[y][x] = std::make_unique<Block>(MelLib::Vector3(sPos, 0, -addNum), left);
                // �m�[�c�̃C���f�b�N�X�ǉ�
                blockIndex.push_back({ y,x });

                addNum++;
            }
        }
        if (humenFile.eof())break;
    }
    humenFile.close();

    moveEndBlock.clear();
    moveEndBlock.resize(blockIndex.size(), nullptr);
}

std::vector<DWORD>p;
int x = 0;
void MusicalScoreManager::CheckBlockMoveStart()
{

    // �`�F�b�N���I�������return
    if (currentHumenIndex == humen.size())return;

    // �O��̎��Ԃ��i�[
    preTime = nowTime;

    // ���݂�Windows���N�����Ă���̎���(�~���b)���擾
    nowTime = timeGetTime();

    // �������v�Z
    const DWORD getTimeSabun = nowTime - preTime;

    // �ŏI�m�[�c�ǉ��^�C�~���O�ƌ��݂̎��Ԃ̍������v�Z
     DWORD sabunTime = (nowTime - humenCheckTime);

    sabunTime *= 1000;
    // �������Ԃ��m�[�c���Ԃ𒴂�����ǉ����Asabun�𒴉߂������l�ŏ㏑��
    // ��U������x�߂�������if�ɓ���悤�ɂ���
    //if (sabunTime >= haku16Time)
    x++;
    if (/*MelLib::LibMath::Difference(sabunTime, haku16Time, getTimeSabun * 1000/ 2)
        || */sabunTime >= haku16Time)
    {

        p.push_back(x);
        x = 0;

        //// currentHumenIndex�̔ԍ��Ńu���b�N���Q�Ƃ��A�ړ����J�n����
        //// �u���b�N��empty�łȂ���Έړ��J�n
        if (humen[currentHumenIndex][0])
        {
            humen[currentHumenIndex][0]->MoveStart();

        }
        else if (humen[currentHumenIndex][1])
        {
            humen[currentHumenIndex][1]->MoveStart();
        }

        sabunTime /= 1000;
        // �������v�Z
        DWORD h = haku16Time / 1000;
        DWORD overTime = sabunTime - h;
        // haku�̕����傫������if�ɓ���ƃI�[�o�[�t���[����\�������邽�߁A���̎���0�ɂ���
        if (sabunTime < h)overTime = 0;

        // ���߂������Ԃŏ㏑��
        humenCheckTime = nowTime - overTime;

        // �Y���������Z
        currentHumenIndex++;

    }

}


MusicalScoreManager* MusicalScoreManager::GetInstance()
{
    static MusicalScoreManager i;
    return &i;
}

void MusicalScoreManager::Load()
{
    // �ȓǂݍ���
   // MelLib::SoundData::Load(musicFolderPath + "Music.wav", SOUND_KEY);
   
    // ���ʓǂݍ���
    LoadHumen(L"Humen/" + musicName + L"/");

    changeNextBlockEnd = false;
    lastBlockPush = false;
    // �ŏ��̃m�[�c����
    pNextBlock = humen[blockIndex[0].v1][blockIndex[0].v2].get();

    LoadDelayTime();

    humenCheckTime = 0;
}

void MusicalScoreManager::LoadDelayTime()
{
    std::ifstream file;
    file.open(L"Humen/" + musicName + L"/mDilay.txt");
   
    std::string str;
    for (int i = 0;; i++)
    {
        str.push_back(' ');
        file.read(&str[i], 1);

        // �ǂݍ��ݏI�������break
        if (file.eof()) break;
    }

    file.close();

    int time = std::atoi(str.c_str());
    musicDelayTimer.SetMaxTime(time);



    file.open(L"Humen/" + musicName + L"/hDilay.txt");
    str.clear();
    for (int i = 0;; i++)
    {
        str.push_back(' ');
        file.read(&str[i], 1);

        // �ǂݍ��ݏI�������break
        if (file.eof()) break;
    }

    file.close();

    time = std::atoi(str.c_str());
    humenDelayTimer.SetMaxTime(time);
}

void MusicalScoreManager::PlayMusic()
{
    // �ϊ�
    size_t size = musicName.size();
    char* cName = new char[size + 1];
    wcstombs_s(&size,cName, size + 1, musicName.data(), musicName.size());

    std::string strName = cName;
    MelLib::Sound::PlayLoadSound(MelLib::SoundData::Get(strName), 0, { 70 }, SOUND_KEY);
    delete[] cName;
    
    musicDelayTimer.SetStopFlag(true);
    musicDelayTimer.ResetTimeZero();
}

void MusicalScoreManager::PlayHumen() 
{
    // addTimer�ɋN�����Ԃ���
    humenCheckTime = timeGetTime();

    
    humenDelayTimer.SetStopFlag(true);
    humenDelayTimer.ResetTimeZero();
}

void MusicalScoreManager::Stop()
{
    MelLib::Sound::StopSound(SOUND_KEY);
}


void MusicalScoreManager::Update()
{
    notPushMiss = false;

    // BPM�ɍ��킹�ĕ��ʂ̃u���b�N�m�F�ƈړ��J�n�̑��x��ς���B


    // �m�[�c�𓮂����^�C�~���O�����v�Z���A�^�C�~���O��������ړ��J�n����
    if(humenCheckTime !=0)  CheckBlockMoveStart();

    for (int y = 0; y < humen.size(); y++)
    {
        for (int x = 0; x < humen[y].size(); x++)
        {
            if (humen[y][x])
            {
                humen[y][x]->Update();
            }
        }
    }

    // �ʉ߂����玩���I�ɐ؂�ւ�
    if (pNextBlock->GetFrame() <= -CheckPushKey::GetTimingFrame(CheckPushKey::JudgmentType::MISS) && 
        !changeNextBlockEnd)
    {
        notPushMiss = true;
        pNextBlock->TrueMiss();
        ChangeNextBlock();
    }

    // �f�B���C�^�C��MAX�ōĐ�
    if (musicDelayTimer.GetMaxOverFlag()) 
    {
        PlayMusic();
    }
    if (humenDelayTimer.GetMaxOverFlag())
    {
        PlayHumen();
    }

  
    // �m�[�c���

    constexpr int n = 100;
   
    const int num = static_cast<int>(currentHumenIndex) - n;
    if (num >= 0)
    {
        if (humen[num][0])
        {
            delete humen[num][0].release();
        }
        if (humen[num][1])
        {
            delete humen[num][1].release();
            
        }
    }

}


void MusicalScoreManager::Draw()
{
    for (int y = 0; y < humen.size(); y++) 
    {
        for (int x = 0; x < humen[y].size(); x++)
        {
            if (humen[y][x]) 
            {
                humen[y][x]->Draw();
            }
        }
    }

    //if(p.size() != 0)
    //MelLib::TextWrite::Draw(MelLib::Vector2(280, 800), MelLib::Color(255, 0, 0, 255),
    //    std::to_wstring(p[p.size() - 1]), "Arial");
}


short MusicalScoreManager::GetLeftTimingDifferenceFrame()
{
    // �����ȕ������痬�����߂ɃO���R�X�Ɠ����d�l�ɂ���ƕ��ʐ���c�[�����̂���ςȂ��߁A��߂�
    // �i�s�����ς������Ȃ�A�J�����񂻂�

    // �u���b�N���E���痬��Ă��Ă�����return
    if (!pNextBlock)return 99;
    if (!pNextBlock->GetLeft())return 99;


    // �p�[�t�F�N�g��2�t���[���Ƃ���ꍇ�A�p�[�t�F�N�g�^�C�~���O��12 -1-2�ɂ��āA0���X�L�b�v������O��2�t���ɂł���
    // ���炩���߉��t���[���Œ����ɂ��ǂ蒅�����v�Z���A����ɍ��킹�ď����ʒu��ݒ肷��

    // �����܂ł̃t���[�������^�[��
    return pNextBlock->GetFrame();
}

void MusicalScoreManager::SetMusicData(const std::wstring& musicName, const std::wstring& artistName, const float& bpm, const bool easy)
{
    // �Ȗ�
    this->musicName = musicName;

    // BPM�֘A
    this->bpm = bpm;
    // 16���̎��Ԃ��v�Z�Bf
    haku16Time = static_cast<DWORD>((15.0f / bpm) * 1000000.0f);

    // �A�[�e�B�X�g��
    this->artistName = artistName;

    this->easy = easy;
}

short MusicalScoreManager::GetRigthTimingDifferenceFrame()
{ 
    // �u���b�N�������痬��Ă��Ă�����return
    if (!pNextBlock)return 99;
    if (pNextBlock->GetLeft())return 99;
    // �����܂ł̃t���[�������^�[��
    return pNextBlock->GetFrame();
}

void MusicalScoreManager::ChangeNextBlock()
{
    if (changeNextBlockEnd)
    {
        return;
    }

    // �ړ��I��
    pNextBlock->MoveEnd();
    // �ǉ�
    moveEndBlock[nextBlockIndex] = pNextBlock;

    // ���̃u���b�N�ɕύX
    nextBlockIndex++;
    
    // ��������������I��
    if (nextBlockIndex == blockIndex.size()) 
    {
        changeNextBlockEnd = true;
        // �Ȓ�~
        //MelLib::Sound::StopSound(SOUND_KEY);
        return;
    }
    
    MelLib::Value2<unsigned int> index = blockIndex[nextBlockIndex];


    pNextBlock = humen[index.v1][index.v2].get();
}


void MusicalScoreManager::Finalize()
{
    humen.clear();
}

void MusicalScoreManager::Play()
{
    musicDelayTimer.SetStartFlag(true);
    humenDelayTimer.SetStartFlag(true);
}
