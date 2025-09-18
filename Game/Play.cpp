#include "Play.h"

#include<DirectionalLight.h>
#include<TextWrite.h>
#include<GameObjectManager.h>

#include"PlayerManager.h"
#include"MusicalScoreManager.h"

#include "JudgmentLine.h"

#include"MusicSelect.h"


#include"Fade.h"

#include"ScoreManger.h"


void Play::ComboCount(bool isCombo)
{
    if (isCombo) {
        comboCountNum++;
    }
    else {
        comboCountNum = 0;
    }
}

void Play::PlayUpdate()
{
    PlayerManager::GetInstance()->Update();
    MusicalScoreManager::GetInstance()->Update();

    // �������u�Ԃ��ǂ���
    keyTrrigerFrame = false;
    notPushMissFrame = MusicalScoreManager::GetInstance()->GetNotPushMiss();

    // ����m�F����(�����Ńu���b�N�̐؂�ւ����s���Ă�̂ŁA�����ł��K�v�͂Ȃ�)

    CheckPushKey::JudgmentType handOverJudgmentType = CheckPushKey::JudgmentType::NONE;
    CheckPushKey::GetInstance()->CheckTiming(handOverJudgmentType, keyTrrigerFrame);

    // ����擾����NONE�ł͂Ȃ������画�菑������
    // ���̏��������Ɣ���\�����ɃL�[������NONE�߂��Ă����画������Ă��܂�
    if (handOverJudgmentType != CheckPushKey::JudgmentType::NONE)
    {
        judgmentType = handOverJudgmentType;
    }

    // ����\�����Ԃ̃^�C�}�[��true���A���Ԃ����Z�b�g
    if (judgmentType != CheckPushKey::JudgmentType::NONE && keyTrrigerFrame
        || notPushMissFrame)
    {
        if (notPushMissFrame)judgmentType = CheckPushKey::JudgmentType::MISS;

        judgmentDrawTimer.ResetTimeZero();
        judgmentDrawTimer.SetStartFlag(true);

        PlayerManager::GetInstance()->MoveStart();

        // �ړ��ʉ��Z
        AddCameraMovePos();
    }

    // ����J�E���g
    CountJudgmentNum();


    // �u���b�N�̃t���[����1�̎��Ɉړ�
    //const short leftFrame = MusicalScoreManager::GetInstance()->GetLeftTimingDifferenceFrame();
    //const short rigthFrame = MusicalScoreManager::GetInstance()->GetRigthTimingDifferenceFrame();
    //if (leftFrame == 0
    //    || rigthFrame == 0)
    //{
    //    // �ړ��ʉ��Z
    //    AddCameraMovePos();
    //}
    MoveCamera();

    UpdatePlayer();
}

void Play::CountJudgmentNum()
{
    // �^�C�}�[�����Ă鎞�͔���\��
    if (!judgmentDrawTimer.GetStopFlag() && judgmentDrawTimer.GetNowTime() == 0)
    {
        switch (judgmentType)
        {
        case CheckPushKey::JudgmentType::PERFECT:
            judgmentNum[CheckPushKey::JudgmentType::PERFECT]++;
            break;
        case CheckPushKey::JudgmentType::GREAT:
            judgmentNum[CheckPushKey::JudgmentType::GREAT]++;
            break;
        case CheckPushKey::JudgmentType::GOOD:
            judgmentNum[CheckPushKey::JudgmentType::GOOD]++;
            break;
        case CheckPushKey::JudgmentType::MISS:
            judgmentNum[CheckPushKey::JudgmentType::MISS]++;
            break;
        }
        drawJudgment = judgmentType;
        dropCheck = true;

        if (judgmentType != CheckPushKey::JudgmentType::MISS) {
            ComboCount(true);
        }
        else {
            ComboCount(false);
        }

        judgmentType = CheckPushKey::JudgmentType::NONE;
    }
}

void Play::AddCameraMovePos()
{
    cameraMoveVec -= CAMERA_ONE_MOVE_POS;
}

void Play::MoveCamera()
{
    // ��C�ɓ����ƔF�����ɂ����Ȃ�̂ŁA���������Z���ē�����
    MelLib::Vector3 cameraPos = MelLib::Camera().Get()->GetRotateCriteriaPosition();
    const float cameraZ = cameraPos.z;

    if (cameraMoveVec < cameraZ - START_CAMERA_POS_Z)
    {
        cameraPos.z -= FRAME_MOVE_POS;
        MelLib::Camera().Get()->SetRotateCriteriaPosition(cameraPos);

        //MovePlayer();

        //// 1�񕶈ړ����I�������if���ɓ���
        //if (cameraOneMoveCheckCounter >= CAMERA_ONE_MOVE_POS)
        //{
        //    // ���Z�o���������
        //    if (dropCheck)
        //    {
        //        cameraOneMoveCheckCounter = 0.0f;
        //        CheckDropPlayer();
        //    }
        //}
        //else // �ړ����I����ĂȂ���������Z
        //{
        //    cameraOneMoveCheckCounter += FRAME_MOVE_POS;
        //}
    }

}

void Play::UpdatePlayer()
{
    PlayerManager::GetInstance()->MovePlayer();

    // �ړ����I������^�C�~���O�Ƀ`�F�b�N 
    // �擪�؂�ւ��ɂ��ړ��̏ꍇ�`�F�b�N���Ȃ�
    if (PlayerManager::GetInstance()->MoveEndFrame() && !PlayerManager::GetInstance()->GetPrePlayerDropMove())
    {
        CheckDropPlayer();
        MoveCamera();
    }
}

void Play::MovePlayer()
{

}

void Play::CheckDropPlayer()
{
    // currentCheckBlock�������������Ȃ���킸���Z���邽�߁A�v���C���[��
    // ����ł��邩�ǂ����̃`�F�b�N�͂���Ȃ�
    const std::vector<Block*>& blocks = MusicalScoreManager::GetInstance()->GetMoveEndBlock();


    // true�������痎��
    if (blocks[currentCheckBlock]->GetMissFlag())
    {

        PlayerManager::GetInstance()->DropPlayer();
    }

    currentCheckBlock++;
    dropCheck = false;

    if (PlayerManager::GetInstance()->GetLifeZeto())
    {
        gameState = GAME_STATE::GAMEOVER;
        gameoverSpriteDrawTimer.SetMaxTime(60.0f * 0.75f);
        gameoverSpriteDrawTimer.SetStartFlag(true);
        MusicalScoreManager::GetInstance()->Stop();
    }
}

void Play::GameoverUpdate()
{

    if (gameoverSpriteDrawTimer.GetMaxOverFlag())
    {
        if (clearSubAlpha > 0.0f)
        {
            clearSubAlpha -= SUB_ALPHA;
            gameoverSprite.SetSubColor(MelLib::Color(0, 0, 0, MelLib::Color::ParToUChar(clearSubAlpha)));
        }
        else clearSubAlpha = 0.0f;

        sceneChangeTimer.SetStartFlag(true);
    }

}

void Play::ClearUpdate()
{

    if (clearPlayerMoveTime.GetMaxOverFlag())
    {
        clearPlayerMoveTime.SetStopFlag(true);
        clearPlayerMoveTime.ResetTimeZero();
        clearMoveEnd = true;

        MusicalScoreManager::GetInstance()->Stop();

        PlayerManager::GetInstance()->SetPlayerClearAnimation();

        clearSpriteDrawTimer.SetMaxTime(60 * 4);
        clearSpriteDrawTimer.SetStartFlag(true);

    }

    if (clearSpriteDrawTimer.GetMaxOverFlag())
    {

        if (clearSubAlpha > 0.0f)
        {
            clearSubAlpha -= SUB_ALPHA;
            clearSprite.SetSubColor(MelLib::Color(0, 0, 0, MelLib::Color::ParToUChar(clearSubAlpha)));

        }
        else
        {
            clearSubAlpha = 0.0f;
        }
        sceneChangeTimer.SetStartFlag(true);
    }

    if (!clearMoveEnd)
    {
        PlayerManager::GetInstance()->MoveStart();
        // �v���C���[�ړ�
        PlayerManager::GetInstance()->MovePlayer();
        MelLib::Vector3 cameraPos = MelLib::Camera::Get()->GetRotateCriteriaPosition();
        cameraPos.z -= FRAME_MOVE_POS;
        MelLib::Camera().Get()->SetRotateCriteriaPosition(cameraPos);

        return;
    }

    // �N���A�A�j���[�V������J�����ړ�
    constexpr float minDis = 7.0f;
    constexpr float frameDis = 0.5f;
    const float dis = MelLib::Camera::Get()->GetCameraToTargetDistance();
    if (minDis <= dis)
    {
        // �����Z�b�g
        MelLib::Camera::Get()->SetCameraToTargetDistance(dis - frameDis);
    }

    // �p�x�擾
    MelLib::Vector3 angle = MelLib::Camera::Get()->GetAngle();
    constexpr float frameAngleX = 2.0f;
    constexpr float frameAngleY = 2.0f;
    constexpr float minAngleX = 30.0f;
    constexpr float minAngleY = -50.0f;
    if (angle.x >= minAngleX)
    {
        angle.x -= frameAngleX;
    }
    if (angle.y >= minAngleY)
    {
        angle.y -= frameAngleY;
    }
    MelLib::Camera::Get()->SetAngle(angle);

    // �J�����ړ�
    MelLib::Vector3 camerPos = MelLib::Camera::Get()->GetRotateCriteriaPosition();
    constexpr float framePosZ = 0.5f;
    constexpr float subPosZ = 10.0f;

    constexpr float moveEndY = 2.0f;
    constexpr float frameMoveEndY = 0.2f;
    if (camerPos.y < moveEndY)camerPos.y += frameMoveEndY;

    if (clearCameraMoveVec < subPosZ)
    {
        clearCameraMoveVec += framePosZ;
        camerPos.z += framePosZ;
    }

    MelLib::Camera::Get()->SetRotateCriteriaPosition(camerPos);
}

void Play::TutorialUpdate()
{
    // �������I��������ۂɃv���C
    if (tutorialNum == 8)
    {
        MelLib::Sound::StopSound("title");
        gameState = GAME_STATE::BEFORE_PLAY;

        startTimer.SetMaxTime(60 * 3);
        startTimer.SetStartFlag(true);
    }
    if (MelLib::Input::KeyTrigger(DIK_SPACE) && !Fade::GetInstance()->GetIsFade())tutorialNum++;
}

Play::Play(const bool tutorial) :TUTORIAL(tutorial)
{
}

Play::~Play()
{
}

void Play::Initialize()
{
    sceneChangeTimer.SetMaxTime(60 * 4);

    // �`���[�g���A������Ȃ������玞�Ԃŕ\��
    if (!TUTORIAL)
    {
        startTimer.SetMaxTime(60 * 5);
        startTimer.SetStartFlag(true);
    }
    else
    {
        gameState = GAME_STATE::TUTORIAL;

        tutorialText[0] = L"�`���[�g���A��";
        tutorialText[1] = L"�u���b�N��n���ăS�[����ڎw�����I";
        tutorialText[2] = L"�u���b�N��F�AD�AJ�AK�L�[�Ŏ~�߂����I";
        tutorialText[3] = L"�����炭��u���b�N��F��������D�Ŏ~�߂���I";
        tutorialText[4] = L"�E���炭��u���b�N��J��������K�Ŏ~�߂���I";
        tutorialText[5] = L"�v���C���[�͐��ɗ�����Ɨ������L�����N�^�[�𑫏�ɂ��Đi�ނ�I";
        tutorialText[6] = L"�L�������S�����ɗ������Ⴄ�ƃQ�[���I�[�o�[�ɂȂ��I";
        tutorialText[7] = L"���ۂɂ���Ă݂悤�I";
    }
#pragma region ����X�v���C�g


    judgmentSprite[CheckPushKey::JudgmentType::PERFECT].Create(MelLib::Texture::Get("Perfect"));
    judgmentSprite[CheckPushKey::JudgmentType::PERFECT].SetPosition(MelLib::Vector2(860, 260));
    judgmentSprite[CheckPushKey::JudgmentType::GREAT].Create(MelLib::Texture::Get("Great"));
    judgmentSprite[CheckPushKey::JudgmentType::GREAT].SetPosition(MelLib::Vector2(860, 260));
    judgmentSprite[CheckPushKey::JudgmentType::GOOD].Create(MelLib::Texture::Get("Good"));
    judgmentSprite[CheckPushKey::JudgmentType::GOOD].SetPosition(MelLib::Vector2(850, 260));
    judgmentSprite[CheckPushKey::JudgmentType::MISS].Create(MelLib::Texture::Get("Miss"));
    judgmentSprite[CheckPushKey::JudgmentType::MISS].SetPosition(MelLib::Vector2(850, 260));

    constexpr float judgeY = 80.0f;
    constexpr float judgeYAdd = 10.0f;
    judgmentCountSprite[CheckPushKey::JudgmentType::PERFECT].Create(MelLib::Texture::Get("Perfect"));
    judgmentCountSprite[CheckPushKey::JudgmentType::PERFECT].SetPosition(MelLib::Vector2(0, 0 + judgeYAdd));
    judgmentCountSprite[CheckPushKey::JudgmentType::GREAT].Create(MelLib::Texture::Get("Great"));
    judgmentCountSprite[CheckPushKey::JudgmentType::GREAT].SetPosition(MelLib::Vector2(0, judgeY * 1 + judgeYAdd));
    judgmentCountSprite[CheckPushKey::JudgmentType::GOOD].Create(MelLib::Texture::Get("Good"));
    judgmentCountSprite[CheckPushKey::JudgmentType::GOOD].SetPosition(MelLib::Vector2(0, judgeY * 2 + judgeYAdd));
    judgmentCountSprite[CheckPushKey::JudgmentType::MISS].Create(MelLib::Texture::Get("Miss"));
    judgmentCountSprite[CheckPushKey::JudgmentType::MISS].SetPosition(MelLib::Vector2(0, judgeY * 3 + judgeYAdd));

#pragma endregion

    waterSprite.Create(MelLib::Texture::Get("water"));
    waterSprite.SetScale(400);
    waterSprite.SetPosition(MelLib::Vector3(0, 0.25f, 0));
    waterSprite.SetAngle(MelLib::Vector3(90, 0, 0));

    const std::wstring name = MusicalScoreManager::GetInstance()->GetMusicName();
    if (name.find(L"Very") != std::string::npos)
    {
        waterSprite.SetMulColor(MelLib::Color(255, 30, 30, 255));
        waterSprite.SetAddColor(MelLib::Color(100, 0, 0, 255));
    }

    // �I�ȂőI�񂾋Ȃƕ��ʂ����[�h
    MusicalScoreManager::GetInstance()->Load();

    // �J�����ݒ�
    MelLib::Camera::Get()->SetRotatePoint(MelLib::Camera::RotatePoint::ROTATE_POINT_TARGET_POSITION);
    MelLib::Camera::Get()->SetRotateCriteriaPosition(MelLib::Vector3(0, 0, START_CAMERA_POS_Z));
    MelLib::Camera::Get()->SetAngle(MelLib::Vector3(70, 0, 0));
    MelLib::Camera::Get()->SetCameraToTargetDistance(40.0f);

    // ���C�g�ݒ�
    MelLib::DirectionalLight::Get().SetDirection(MelLib::Vector3(0, -1, 1).Normalize());


    // ����\�����Ԃ�ݒ�
    judgmentDrawTimer.SetMaxTime(60 * 0.5f);


    // Initialize����ɃZ�b�g
    PlayerManager::GetInstance()->SetPlayerMoveVec(CAMERA_ONE_MOVE_POS, FRAME_MOVE_POS);
    PlayerManager::GetInstance()->PlayerInitialize();
    Player::SetFrameMoveVec(FRAME_MOVE_POS);

    dropPlayerFlag.resize(MusicalScoreManager::GetInstance()->GetBlockIndexNum());


    startObj.Create(MelLib::ModelData::Get("Start"), "Start", nullptr);
    startObj.SetPosition({ 0,1.2f,-0.5f });
    startObj.SetAngle({ 0,90,0 });

    // �S�[���n�_����
  // ���R���{�����Q�Ƃ��č��W���w��
    goalObj.Create(MelLib::ModelData::Get("Start"), "Start", nullptr);
    const float comboMax = static_cast<float>(MusicalScoreManager::GetInstance()->GetBlockIndexNum());
    goalObj.SetPosition({ 0,1.2f,-comboMax - 1 });
    goalObj.SetAngle({ 0,-90,0 });

    // ���胉�C������
    MelLib::GameObjectManager::GetInstance()->AddObject(std::make_shared<JudgmentLine>());

    // �J�n�Ƃ�
    readySprite.Create(MelLib::Texture::Get("Ready"));
    readySprite.SetPosition(MelLib::Vector2(510, 400));
    clearSprite.Create(MelLib::Texture::Get("Clear"));
    clearSprite.SetSubColor(MelLib::Color(0, 0, 0, 255));
    clearSprite.SetScale(0.7f);
    clearSprite.SetPosition(MelLib::Vector2(480, 400));
    gameoverSprite.Create(MelLib::Texture::Get("Gameover"));
    gameoverSprite.SetSubColor(MelLib::Color(0, 0, 0, 255));
    gameoverSprite.SetPosition(MelLib::Vector2(500, 400));

    // �L�[
    keyNakamiSprite[DIK_D].Create(MelLib::Texture::Get("D_nakami"));
    keyNakamiSprite[DIK_F].Create(MelLib::Texture::Get("F_nakami"));
    keyNakamiSprite[DIK_J].Create(MelLib::Texture::Get("J_nakami"));
    keyNakamiSprite[DIK_K].Create(MelLib::Texture::Get("K_nakami"));
    keyWakuSprite[DIK_D].Create(MelLib::Texture::Get("D_waku"));
    keyWakuSprite[DIK_F].Create(MelLib::Texture::Get("F_waku"));
    keyWakuSprite[DIK_J].Create(MelLib::Texture::Get("J_waku"));
    keyWakuSprite[DIK_K].Create(MelLib::Texture::Get("K_waku"));

    constexpr float sousaY = 200.0f;
    constexpr float lX = 450.0f;
    constexpr float rX = 550.0f;
    constexpr float sukimaL = 120.0f;
    constexpr float sukimaR = 90.0f;
    keyNakamiSprite[DIK_D].SetPosition(MelLib::Vector2(lX, sousaY));
    keyWakuSprite[DIK_D].SetPosition(MelLib::Vector2(lX, sousaY));

    keyNakamiSprite[DIK_F].SetPosition(MelLib::Vector2(lX + sukimaL, sousaY));
    keyWakuSprite[DIK_F].SetPosition(MelLib::Vector2(lX + sukimaL, sousaY));

    keyNakamiSprite[DIK_J].SetPosition(MelLib::Vector2(1920 - rX - sukimaR, sousaY));
    keyWakuSprite[DIK_J].SetPosition(MelLib::Vector2(1920 - rX - sukimaR, sousaY));

    keyWakuSprite[DIK_K].SetPosition(MelLib::Vector2(1920 - rX, sousaY));
    keyNakamiSprite[DIK_K].SetPosition(MelLib::Vector2(1920 - rX, sousaY));

    for (auto& k : keyNakamiSprite)
    {
        k.second.SetScale(0.5f);
    }
    for (auto& k : keyWakuSprite)
    {
        k.second.SetScale(0.5f);
    }
}

void Play::Update()
{
    Fade::GetInstance()->Update();
    for (auto& keyNakami : keyNakamiSprite)
    {
        if (MelLib::Input::KeyState(keyNakami.first))
        {
            keyNakami.second.SetMulColor(MelLib::Color(255, 100, 0, 255));
        }
        else
        {
            keyNakami.second.SetMulColor(MelLib::Color(255, 255, 255, 255));
        }
    }

    if (gameState == Play::GAME_STATE::BEFORE_PLAY && startTimer.GetMaxOverFlag())
    {
        gameState = Play::GAME_STATE::PLAY;
        startTimer.SetStopFlag(true);

        /*MusicalScoreManager::GetInstance()->PlayMusic();
        MusicalScoreManager::GetInstance()->PlayHumen();*/
        MusicalScoreManager::GetInstance()->Play();
    }

    if (gameState != GAME_STATE::BEFORE_PLAY)
    {
        if (readySubAlpha < 100.0f)
        {
            readySubAlpha += SUB_ALPHA;
            readySprite.SetSubColor(MelLib::Color(0, 0, 0, MelLib::Color::ParToUChar(readySubAlpha)));
        }
        else readySubAlpha = 100.0f;
    }


    // ���Ԍo�߂�����^�C�}�[��~���A�����\�����Ȃ��悤�ɂ���
    if (judgmentDrawTimer.GetMaxOverFlag())
    {
        judgmentDrawTimer.SetStopFlag(true);
    }

    switch (gameState)
    {
    case Play::GAME_STATE::PLAY:
        PlayUpdate();
        break;
    case Play::GAME_STATE::GAMEOVER:
        GameoverUpdate();
        break;
    case Play::GAME_STATE::CLEAR:
        ClearUpdate();
        break;
    case Play::GAME_STATE::TUTORIAL:
        TutorialUpdate();
        break;
    default:
        break;
    }

    MelLib::GameObjectManager::GetInstance()->Update();

    if (MusicalScoreManager::GetInstance()->GetHumenEnd()
        && (keyTrrigerFrame || notPushMissFrame))
    {
        lifeCheckTimer.SetStartFlag(true);
        lifeCheckTimer.SetMaxTime(6);
    }

    if (!PlayerManager::GetInstance()->GetLifeZeto() && lifeCheckTimer.GetMaxOverFlag())
    {
        lifeCheckTimer.SetStopFlag(true);
        gameState = GAME_STATE::CLEAR;
        clearPlayerMoveTime.SetMaxTime(60 * 0.5f);
        clearPlayerMoveTime.SetStartFlag(true);
    }

    //if (MelLib::Input::KeyTrigger(DIK_1)) isEnd = true;

    if (sceneChangeTimer.GetMaxOverFlag())Fade::GetInstance()->Start();
    if (Fade::GetInstance()->GetChangeSceneFlag())isEnd = true;
}

void Play::Draw()
{
    MelLib::GameObjectManager::GetInstance()->Draw();
    MusicalScoreManager::GetInstance()->Draw();
    startObj.Draw();
    goalObj.Draw();
    waterSprite.Draw();

    // �J�E���g�\��
    constexpr float judgmentCountDrawPosY = 80;
    MelLib::TextWrite::Draw(MelLib::Vector2(280, 0), MelLib::Color(255, 255),
        std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::PERFECT]), "Arial");
    MelLib::TextWrite::Draw(MelLib::Vector2(280, judgmentCountDrawPosY * 1), MelLib::Color(255, 255),
        std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::GREAT]), "Arial");
    MelLib::TextWrite::Draw(MelLib::Vector2(280, judgmentCountDrawPosY * 2), MelLib::Color(255, 255),
        std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::GOOD]), "Arial");
    MelLib::TextWrite::Draw(MelLib::Vector2(280, judgmentCountDrawPosY * 3), MelLib::Color(255, 255),
        std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::MISS]), "Arial");

    // �^�C�}�[�����Ă鎞�͔���\��
    if (!judgmentDrawTimer.GetStopFlag())
    {
        judgmentSprite.at(drawJudgment).Draw();
        if (comboCountNum != 0)
        {
            std::wstring wstr1 = std::to_wstring(comboCountNum);
            MelLib::TextWrite::Draw({ 930,180 }, MelLib::Color(0, 255), wstr1, "Arial");
        }
    }
    for (auto& sprite : judgmentCountSprite)sprite.second.Draw();


    // �L�[
    for (auto& keyWaku : keyWakuSprite)
    {
        keyWaku.second.Draw();
    }
    for (auto& keyNakami : keyNakamiSprite)
    {
        keyNakami.second.Draw();
    }

    if (readySubAlpha != 100.0f && !TUTORIAL)readySprite.Draw();
    if (clearSpriteDrawTimer.GetMaxOverFlag()) clearSprite.Draw();
    if (gameoverSpriteDrawTimer.GetMaxOverFlag()) gameoverSprite.Draw();


    if (gameState == GAME_STATE::TUTORIAL)
    {
        const MelLib::Vector2 tutorialTextPos = MelLib::Vector2(50, 600);
        MelLib::TextWrite::Draw(tutorialTextPos, MelLib::Color(255, 255), tutorialText[tutorialNum], "Arial");
        MelLib::TextWrite::Draw({80, 680}, MelLib::Color(255, 255), L"�X�y�[�X�Ői�ނ�", "ArialMini");
    }


    Fade::GetInstance()->Draw();
}

void Play::Finalize()
{
    MelLib::GameObjectManager::GetInstance()->Finalize();
    PlayerManager::GetInstance()->Finalize();

    ScoreManger::GetInstance()->Save(MusicalScoreManager::GetInstance()->GetMusicName(), judgmentNum);
}

MelLib::Scene* Play::GetNextScene()
{
    return new MusicSelect();
}
