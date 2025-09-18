#include "MusicSelect.h"

#include"BackGroundPlayer.h"
#include"Play.h"
#include"MusicalScoreManager.h"

#include"GameObjectManager.h"

#include"TextWrite.h"
#include"Fade.h"

#include<fstream>
#include<filesystem>
#include "ScoreManger.h"

void MusicSelect::LoadMusicData()
{
    for (const auto& dirEntry : std::filesystem::directory_iterator("Humen/"))
    {
        const std::wstring path = dirEntry.path().wstring();
        //if (path.find(L".musn") == std::string::npos)continue;


        // 曲名読み込み
        std::wstring musicName;
        LoadName(path, L"", musicName, false);
        musicNames[musicCount] = musicName;
        musicCount++;

        // アーティスト名読み込み
        std::wstring artistName;
        LoadName(path + L"/", L".artn", artistNames[musicName], true);

        // BPM読み込み
        LoadBPM(path + L"/", bpms[musicName]);
    }
}

void MusicSelect::LoadBPM(const std::wstring& musicFolderPath, float& bpm)
{
    // 読み込み
    std::ifstream bpmFile;
    bpmFile.open(musicFolderPath + L"BPM.txt");
    std::string bpmString;
    for (int i = 0;; i++)
    {
        bpmString.push_back(' ');
        bpmFile.read(&bpmString[i], 1);

        // 読み込み終わったらbreak
        if (bpmFile.eof()) break;
    }
    bpmFile.close();

    // 文字列からintに変換
    bpm = atof(bpmString.data());
}

void MusicSelect::LoadName(const std::wstring& musicFolderPath, const std::wstring& format, std::wstring& refStr, const bool file)
{
    std::wstring name = musicFolderPath;
    if (file)
    {

        for (const auto& dirEntry : std::filesystem::directory_iterator(musicFolderPath))
        {
            name = dirEntry.path().wstring();
            if (name.find(format) == std::string::npos)continue;
            refStr = name;
            break;
        }
    }
    else refStr = name;

    // 拡張子を外す
    refStr.erase(refStr.end() - format.size(), refStr.end());
    // パスを外す
    for (int i = refStr.size() - 1;; i--)
    {
        if (refStr[i] == '/' || refStr[i] == '\\')
        {
            refStr.erase(refStr.begin(), refStr.begin() + i + 1);
            break;
        }
    }
}

MusicSelect::MusicSelect()
{
}

MusicSelect::~MusicSelect()
{
}

void MusicSelect::Initialize()
{
    Fade::GetInstance()->Initializ();
    arrow.Create(MelLib::Texture::Get("Arrow"));
    arrow2.Create(MelLib::Texture::Get("Arrow"));
    arrow.SetPosition({ 1400,360 });
    arrow2.SetPosition({ 510,680 });
    arrow2.SetAngle(180);

    LoadMusicData();


    MelLib::Camera::Get()->SetRotatePoint(MelLib::Camera::RotatePoint::ROTATE_POINT_TARGET_POSITION);
    MelLib::Camera::Get()->SetRotateCriteriaPosition(MelLib::Vector3(0, 0, 0));
    MelLib::Camera::Get()->SetAngle(MelLib::Vector3(0, 0, 0));
    MelLib::Camera::Get()->SetCameraToTargetDistance(40.0f);


    addTimer.SetMaxTime(60 * 0.75f);
    addTimer.SetStartFlag(true);

    MelLib::Sound::PlayLoadSound(MelLib::SoundData::Get("title"), MelLib::Sound::LOOP_INFINITY, { 80 }, "title");
}

void MusicSelect::Update()
{
    Fade::GetInstance()->Update();
    if (MelLib::Input::KeyTrigger(DIK_SPACE) && !Fade::GetInstance()->GetIsFade())
    {
        Fade::GetInstance()->Start();

        MelLib::Sound::PlayLoadSound(MelLib::SoundData::Get("push"), 0, { 70 });
    }
    if (Fade::GetInstance()->GetChangeSceneFlag())isEnd = true;

    if (MelLib::Input::KeyTrigger(DIK_LEFT))
    {
        selectMusicNum++;
    }
    if (MelLib::Input::KeyTrigger(DIK_RIGHT))
    {
        selectMusicNum--;
    }
    if (selectMusicNum < 0)selectMusicNum = musicNames.size() - 1;
    else if (selectMusicNum == musicNames.size())selectMusicNum = 0;

    MelLib::GameObjectManager::GetInstance()->Update();


    if (addTimer.GetMaxOverFlag())
    {
        MelLib::GameObjectManager::GetInstance()->AddObject
        (
            std::make_shared<BackGroundPlayer>()
        );
        addTimer.ResetTimeZero();
    }
}

void MusicSelect::Draw()
{
    MelLib::TextWrite::Draw(MelLib::Vector2(680, 350), MelLib::Color(255, 255),
        musicNames[selectMusicNum], "Arial");

    MelLib::TextWrite::Draw(MelLib::Vector2(680, 440), MelLib::Color(255, 255),
        artistNames[musicNames[selectMusicNum]], "Arial");

    MelLib::TextWrite::Draw(MelLib::Vector2(680, 530), MelLib::Color(255, 255),
        L"BPM " + std::to_wstring(static_cast<int>(bpms[musicNames[selectMusicNum]])), "Arial");

    //現スコアの表示
    std::unordered_map<CheckPushKey::JudgmentType, unsigned short> judgmentNum = ScoreManger::GetInstance()->Get(musicNames[selectMusicNum]);
    constexpr float judgmentCountDrawPosY = 40;
    MelLib::TextWrite::Draw(MelLib::Vector2(720, 620), MelLib::Color(255, 255),
        L"PERFECT", "ArialMini");
    MelLib::TextWrite::Draw(MelLib::Vector2(720, 620+judgmentCountDrawPosY * 1), MelLib::Color(255, 255),
        L"GREAT", "ArialMini");
    MelLib::TextWrite::Draw(MelLib::Vector2(720, 620 + judgmentCountDrawPosY * 2), MelLib::Color(255, 255),
        L"GOOD", "ArialMini");
    MelLib::TextWrite::Draw(MelLib::Vector2(720, 620 + judgmentCountDrawPosY * 3), MelLib::Color(255, 255),
        L"MISS", "ArialMini");
    MelLib::TextWrite::Draw(MelLib::Vector2(1080, 620 ), MelLib::Color(255, 255),
        std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::PERFECT]), "ArialMini");
    MelLib::TextWrite::Draw(MelLib::Vector2(1080, 620 + judgmentCountDrawPosY * 1), MelLib::Color(255, 255),
        std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::GREAT]), "ArialMini");
    MelLib::TextWrite::Draw(MelLib::Vector2(1080, 620 + judgmentCountDrawPosY * 2), MelLib::Color(255, 255),
        std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::GOOD]), "ArialMini");
    MelLib::TextWrite::Draw(MelLib::Vector2(1080, 620 + judgmentCountDrawPosY * 3), MelLib::Color(255, 255),
        std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::MISS]), "ArialMini");

    MelLib::GameObjectManager::GetInstance()->Draw();
    Fade::GetInstance()->Draw();
    MelLib::TextWrite::Draw(MelLib::Vector2(720, 880), MelLib::Color(255, 255), L"←→で曲選択", "Arial");
    MelLib::TextWrite::Draw(MelLib::Vector2(720, 950), MelLib::Color(255, 255), L"スペースで決定", "Arial");

    arrow.Draw();
    arrow2.Draw();
}

void MusicSelect::Finalize()
{
    MusicalScoreManager::GetInstance()->SetMusicData
    (
        musicNames[selectMusicNum],
        artistNames[musicNames[selectMusicNum]],
        bpms[musicNames[selectMusicNum]],
        easy
    );

    MelLib::GameObjectManager::GetInstance()->Finalize();


    MelLib::Sound::StopSound("title");
}

MelLib::Scene* MusicSelect::GetNextScene()
{
    return new Play(false);
}
