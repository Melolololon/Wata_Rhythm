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

    // 総枠数取得
    size_t frameNum = 0;
    humenFile.seekg(0, std::ios_base::end);
    frameNum = humenFile.tellg();
    humenFile.seekg(0, std::ios_base::beg);

    // リサイズ
    const int frameHarf = frameNum / 2;
    humen.resize(frameHarf);
    
    int addNum = 1;
    // 読み込み
    for (unsigned int y = 0;; y++)
    {
        // easyだったら16分を抜く
        // 8分を抜いてもいいかも
        // easy normal hardでもいい？
        // 一旦16分を抜く
        if (easy && y % 2 == 1)
        {
            continue;
        }

        for (unsigned int x = 0; x < 2; x++)
        {
            char num = 0;
            humenFile.read(&num, 1);


            // ブロック追加
            if (num == '1')
            {
                bool left = !static_cast<bool>(x);
                float sPos = Block::GetStartSidePos();
                if (left)sPos = -sPos;

                // ノーツ生成
                humen[y][x] = std::make_unique<Block>(MelLib::Vector3(sPos, 0, -addNum), left);
                // ノーツのインデックス追加
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

    // チェックし終わったらreturn
    if (currentHumenIndex == humen.size())return;

    // 前回の時間を格納
    preTime = nowTime;

    // 現在のWindowsが起動してからの時間(ミリ秒)を取得
    nowTime = timeGetTime();

    // 差分を計算
    const DWORD getTimeSabun = nowTime - preTime;

    // 最終ノーツ追加タイミングと現在の時間の差分を計算
     DWORD sabunTime = (nowTime - humenCheckTime);

    sabunTime *= 1000;
    // 差分時間がノーツ時間を超えたら追加し、sabunを超過した数値で上書き
    // 一旦ある程度近かったらifに入るようにする
    //if (sabunTime >= haku16Time)
    x++;
    if (/*MelLib::LibMath::Difference(sabunTime, haku16Time, getTimeSabun * 1000/ 2)
        || */sabunTime >= haku16Time)
    {

        p.push_back(x);
        x = 0;

        //// currentHumenIndexの番号でブロックを参照し、移動を開始する
        //// ブロックがemptyでなければ移動開始
        if (humen[currentHumenIndex][0])
        {
            humen[currentHumenIndex][0]->MoveStart();

        }
        else if (humen[currentHumenIndex][1])
        {
            humen[currentHumenIndex][1]->MoveStart();
        }

        sabunTime /= 1000;
        // 差分を計算
        DWORD h = haku16Time / 1000;
        DWORD overTime = sabunTime - h;
        // hakuの方が大きい時にifに入るとオーバーフローする可能性があるため、その時は0にする
        if (sabunTime < h)overTime = 0;

        // 超過した時間で上書き
        humenCheckTime = nowTime - overTime;

        // 添え字を加算
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
    // 曲読み込み
   // MelLib::SoundData::Load(musicFolderPath + "Music.wav", SOUND_KEY);
   
    // 譜面読み込み
    LoadHumen(L"Humen/" + musicName + L"/");

    changeNextBlockEnd = false;
    lastBlockPush = false;
    // 最初のノーツを代入
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

        // 読み込み終わったらbreak
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

        // 読み込み終わったらbreak
        if (file.eof()) break;
    }

    file.close();

    time = std::atoi(str.c_str());
    humenDelayTimer.SetMaxTime(time);
}

void MusicalScoreManager::PlayMusic()
{
    // 変換
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
    // addTimerに起動時間を代入
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

    // BPMに合わせて譜面のブロック確認と移動開始の速度を変える。


    // ノーツを動かすタイミングかを計算し、タイミングだったら移動開始する
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

    // 通過したら自動的に切り替え
    if (pNextBlock->GetFrame() <= -CheckPushKey::GetTimingFrame(CheckPushKey::JudgmentType::MISS) && 
        !changeNextBlockEnd)
    {
        notPushMiss = true;
        pNextBlock->TrueMiss();
        ChangeNextBlock();
    }

    // ディレイタイムMAXで再生
    if (musicDelayTimer.GetMaxOverFlag()) 
    {
        PlayMusic();
    }
    if (humenDelayTimer.GetMaxOverFlag())
    {
        PlayHumen();
    }

  
    // ノーツ解放

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
    // いろんな方向から流すためにグルコスと同じ仕様にすると譜面製作ツール作るのが大変なため、やめる
    // 進行方向変えたいなら、カメラ回そう

    // ブロックが右から流れてきていたらreturn
    if (!pNextBlock)return 99;
    if (!pNextBlock->GetLeft())return 99;


    // パーフェクトを2フレームとする場合、パーフェクトタイミングは12 -1-2にして、0をスキップしたら前後2フレにできる
    // あらかじめ何フレームで中央にたどり着くか計算し、それに合わせて初期位置を設定する

    // 完璧までのフレームをリターン
    return pNextBlock->GetFrame();
}

void MusicalScoreManager::SetMusicData(const std::wstring& musicName, const std::wstring& artistName, const float& bpm, const bool easy)
{
    // 曲名
    this->musicName = musicName;

    // BPM関連
    this->bpm = bpm;
    // 16分の時間を計算。f
    haku16Time = static_cast<DWORD>((15.0f / bpm) * 1000000.0f);

    // アーティスト名
    this->artistName = artistName;

    this->easy = easy;
}

short MusicalScoreManager::GetRigthTimingDifferenceFrame()
{ 
    // ブロックが左から流れてきていたらreturn
    if (!pNextBlock)return 99;
    if (pNextBlock->GetLeft())return 99;
    // 完璧までのフレームをリターン
    return pNextBlock->GetFrame();
}

void MusicalScoreManager::ChangeNextBlock()
{
    if (changeNextBlockEnd)
    {
        return;
    }

    // 移動終了
    pNextBlock->MoveEnd();
    // 追加
    moveEndBlock[nextBlockIndex] = pNextBlock;

    // 次のブロックに変更
    nextBlockIndex++;
    
    // 次が無かったら終了
    if (nextBlockIndex == blockIndex.size()) 
    {
        changeNextBlockEnd = true;
        // 曲停止
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
