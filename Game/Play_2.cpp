//#include "Play.h"
//
//#include<DirectionalLight.h>
//#include<TextWrite.h>
//#include<GameObjectManager.h>
//
//#include"PlayerManager.h"
//#include"MusicalScoreManager.h"
//
//#include "JudgmentLine.h"
//
//#include"MusicSelect.h"
//
//
//void Play::ComboCount(bool isCombo)
//{
//	if (isCombo) {
//		comboCountNum++;
//	}
//	else {
//		comboCountNum = 0;
//	}
//}
//
//void Play::PlayUpdate()
//{
//    PlayerManager::GetInstance()->Update();
//    MusicalScoreManager::GetInstance()->Update();
//
//    // 押した瞬間かどうか
//    keyTrrigerFrame = false;
//    notPushMissFrame = MusicalScoreManager::GetInstance()->GetNotPushMiss();
//
//    // 判定確認する(内部でブロックの切り替えも行ってるので、ここでやる必要はない)
//    
//    CheckPushKey::JudgmentType handOverJudgmentType = CheckPushKey::JudgmentType::NONE;
//    CheckPushKey::GetInstance()->CheckTiming(handOverJudgmentType, keyTrrigerFrame);
//
//    // 判定取得してNONEではなかったら判定書き換え
//    // この処理無いと判定表示中にキー押してNONE戻ってきたら判定消えてしまう
//    if (handOverJudgmentType != CheckPushKey::JudgmentType::NONE)
//    {
//        judgmentType = handOverJudgmentType;
//    }
//
//    // 判定表示時間のタイマーをtrueし、時間もリセット
//    if (judgmentType != CheckPushKey::JudgmentType::NONE && keyTrrigerFrame
//        || notPushMissFrame)
//    {
//        if (notPushMissFrame)judgmentType = CheckPushKey::JudgmentType::MISS;
//
//        judgmentDrawTimer.ResetTimeZero();
//        judgmentDrawTimer.SetStartFlag(true);
//
//        PlayerManager::GetInstance()->MoveStart();
//
//        // 移動量加算
//        AddCameraMovePos();
//    }
//    
//    // 判定カウント
//    CountJudgmentNum();
//
//
//    // ブロックのフレームが1の時に移動
//    //const short leftFrame = MusicalScoreManager::GetInstance()->GetLeftTimingDifferenceFrame();
//    //const short rigthFrame = MusicalScoreManager::GetInstance()->GetRigthTimingDifferenceFrame();
//    //if (leftFrame == 0
//    //    || rigthFrame == 0)
//    //{
//    //    // 移動量加算
//    //    AddCameraMovePos();
//    //}
//    MoveCamera();
//
//    UpdatePlayer();
//}
//
//void Play::CountJudgmentNum()
//{ 
//    // タイマー動いてる時は判定表示
//    if (!judgmentDrawTimer.GetStopFlag() && judgmentDrawTimer.GetNowTime() == 0)
//    {
//        switch (judgmentType)
//        {
//        case CheckPushKey::JudgmentType::PERFECT:
//            judgmentNum[CheckPushKey::JudgmentType::PERFECT]++;
//            break;
//        case CheckPushKey::JudgmentType::GREAT:
//            judgmentNum[CheckPushKey::JudgmentType::GREAT]++;
//            break;
//        case CheckPushKey::JudgmentType::GOOD:
//            judgmentNum[CheckPushKey::JudgmentType::GOOD]++;
//            break;
//        case CheckPushKey::JudgmentType::MISS:
//            judgmentNum[CheckPushKey::JudgmentType::MISS]++;
//            break;
//        }
//        drawJudgment = judgmentType;
//        dropCheck = true;
//      
//      if (judgmentType != CheckPushKey::JudgmentType::MISS) {
//	    	    ComboCount(true);
//	      }
//    	else {
//		        ComboCount(false);
//	      }
//    
//        judgmentType = CheckPushKey::JudgmentType::NONE;
//    }
//}
//
//void Play::AddCameraMovePos()
//{
//    cameraMoveVec -= CAMERA_ONE_MOVE_POS;
//}
//
//void Play::MoveCamera()
//{
//    // 一気に動くと認識しにくくなるので、少しずつ加算して動かす
//    MelLib::Vector3 cameraPos = MelLib::Camera().Get()->GetRotateCriteriaPosition();
//    const float cameraZ = cameraPos.z;
//
//    if (cameraMoveVec < cameraZ - START_CAMERA_POS_Z)
//    {
//        cameraPos.z -= FRAME_MOVE_POS;
//        MelLib::Camera().Get()->SetRotateCriteriaPosition(cameraPos);
//
//        //MovePlayer();
//
//        //// 1回文移動し終わったらif内に入る
//        //if (cameraOneMoveCheckCounter >= CAMERA_ONE_MOVE_POS)
//        //{
//        //    // 加算出来たら入る
//        //    if (dropCheck)
//        //    {
//        //        cameraOneMoveCheckCounter = 0.0f;
//        //        CheckDropPlayer();
//        //    }
//        //}
//        //else // 移動し終わってなかったら加算
//        //{
//        //    cameraOneMoveCheckCounter += FRAME_MOVE_POS;
//        //}
//    }
//
//}
//
//void Play::UpdatePlayer()
//{
//    PlayerManager::GetInstance()->MovePlayer();
//
//    // 移動が終わったタイミングにチェック 
//    // 先頭切り替えによる移動の場合チェックしない
//    if (PlayerManager::GetInstance()->MoveEndFrame() && !PlayerManager::GetInstance()->GetPrePlayerDropMove())
//    {
//        CheckDropPlayer();
//        MoveCamera();
//    }
//}
//
//void Play::MovePlayer()
//{
//
//}
//
//void Play::CheckDropPlayer()
//{
//    // currentCheckBlockが落ちた落ちない問わず加算するため、プレイヤーが
//    // 沈んでいるかどうかのチェックはいらない
//    const std::vector<Block*>& blocks = MusicalScoreManager::GetInstance()->GetMoveEndBlock();
//
//
//    // trueだったら落下
//    if (blocks[currentCheckBlock]->GetMissFlag())
//    {
//
//        PlayerManager::GetInstance()->DropPlayer();
//    }
//
//    currentCheckBlock++;
//    dropCheck = false;
//
//    if (PlayerManager::GetInstance()->GetLifeZeto())
//    {
//        gameState = GAME_STATE::GAMEOVER;
//        gameoverSpriteDrawTimer.SetMaxTime(60.0f * 0.75f);
//        gameoverSpriteDrawTimer.SetStartFlag(true);
//    }
//}
//
//void Play::GameoverUpdate()
//{
//
//    if (gameoverSpriteDrawTimer.GetMaxOverFlag()) 
//    {
//        if (clearSubAlpha > 0.0f)
//        {
//            clearSubAlpha -= SUB_ALPHA;
//            gameoverSprite.SetSubColor(MelLib::Color(0, 0, 0, MelLib::Color::ParToUChar(clearSubAlpha)));
//        }
//        else clearSubAlpha = 0.0f;
//    }
//
//}
//
//void Play::ClearUpdate()
//{
//    if (clearPlayerMoveTime.GetMaxOverFlag())
//    {
//        clearPlayerMoveTime.SetStopFlag(true);
//        clearPlayerMoveTime.ResetTimeZero();
//        clearMoveEnd = true;
//
//        PlayerManager::GetInstance()->SetPlayerClearAnimation();
// 
//        clearSpriteDrawTimer.SetMaxTime(60 * 2);
//        clearSpriteDrawTimer.SetStartFlag(true);
//
//    }
//
//    if (clearSpriteDrawTimer.GetMaxOverFlag())
//    {
//        if (clearSubAlpha > 0.0f)
//        {
//            clearSubAlpha -= SUB_ALPHA;
//            clearSprite.SetSubColor(MelLib::Color(0, 0, 0, MelLib::Color::ParToUChar(clearSubAlpha)));
//        }
//        else clearSubAlpha = 0.0f;
//    }
//
//    if (!clearMoveEnd)
//    {
//        PlayerManager::GetInstance()->MoveStart();
//        // プレイヤー移動
//        PlayerManager::GetInstance()->MovePlayer();
//        MelLib::Vector3 cameraPos = MelLib::Camera::Get()->GetRotateCriteriaPosition();
//        cameraPos.z -= FRAME_MOVE_POS;
//        MelLib::Camera().Get()->SetRotateCriteriaPosition(cameraPos);
//
//        return;
//    }
//
//    // クリアアニメーションやカメラ移動
//    constexpr float minDis = 7.0f;
//    constexpr float frameDis = 0.5f;
//    const float dis = MelLib::Camera::Get()->GetCameraToTargetDistance();
//    if (minDis <= dis)
//    {
//        // 距離セット
//        MelLib::Camera::Get()->SetCameraToTargetDistance(dis - frameDis);
//    }
//
//    // 角度取得
//    MelLib::Vector3 angle = MelLib::Camera::Get()->GetAngle();
//    constexpr float frameAngleX = 2.0f;
//    constexpr float frameAngleY = 2.0f;
//    constexpr float minAngleX = 30.0f;
//    constexpr float minAngleY = -50.0f;
//    if (angle.x >= minAngleX)
//    {
//        angle.x -= frameAngleX;
//    }
//    if (angle.y >= minAngleY)
//    {
//        angle.y -= frameAngleY;
//    }
//    MelLib::Camera::Get()->SetAngle(angle);
//
//    // カメラ移動
//    MelLib::Vector3 camerPos = MelLib::Camera::Get()->GetRotateCriteriaPosition();
//    constexpr float framePosZ = 0.5f;
//    constexpr float subPosZ = 10.0f;
//
//    constexpr float moveEndY = 2.0f;
//    constexpr float frameMoveEndY = 0.2f;
//    if (camerPos.y < moveEndY)camerPos.y += frameMoveEndY;
//
//    if (clearCameraMoveVec < subPosZ) 
//    {
//        clearCameraMoveVec += framePosZ;
//        camerPos.z += framePosZ;
//    }
//
//    MelLib::Camera::Get()->SetRotateCriteriaPosition(camerPos);
//}
//
//void Play::TutorialUpdate()
//{
//    // 説明が終ったら実際にプレイ
//    if(tutorialNum == 8)
//    {
//        gameState = GAME_STATE::BEFORE_PLAY;
//    }
//    if (MelLib::Input::KeyTrigger(DIK_SPACE))tutorialNum++;
//}
//
//Play::Play(const bool tutorial):TUTORIAL(tutorial)
//{
//}
//
//Play::~Play()
//{
//}
//
//void Play::Initialize()
//{
//
//    // チュートリアルじゃなかったら時間で表示
//    if (!TUTORIAL) 
//    {
//        startTimer.SetMaxTime(60 * 5);
//        startTimer.SetStartFlag(true);
//    }
//    else
//    {
//        gameState = GAME_STATE::TUTORIAL;
//
//        tutorialText[0] = L"チュートリアル";
//        tutorialText[1] = L"ブロックを渡ってゴールを目指そう！";
//        tutorialText[2] = L"ブロックはF、D、J、Kキーで止められるよ！";
//        tutorialText[3] = L"左からくるブロックはFもしくはDで止めれるよ！";
//        tutorialText[4] = L"右からくるブロックはJもしくはKで止めれるよ！";
//        tutorialText[5] = L"プレイヤーは水に落ちると落ちたキャラクターを足場にして進むよ！";
//        tutorialText[6] = L"キャラが全員水に落ちちゃうとゲームオーバーになるよ！";
//        tutorialText[7] = L"実際にやってみよう！";
//    }
//#pragma region 判定スプライト
//
//
//    judgmentSprite[CheckPushKey::JudgmentType::PERFECT].Create(MelLib::Texture::Get("Perfect"));
//    judgmentSprite[CheckPushKey::JudgmentType::PERFECT].SetPosition(MelLib::Vector2(860,260));
//    judgmentSprite[CheckPushKey::JudgmentType::GREAT].Create(MelLib::Texture::Get("Great"));
//    judgmentSprite[CheckPushKey::JudgmentType::GREAT].SetPosition(MelLib::Vector2(860, 260));
//    judgmentSprite[CheckPushKey::JudgmentType::GOOD].Create(MelLib::Texture::Get("Good"));
//    judgmentSprite[CheckPushKey::JudgmentType::GOOD].SetPosition(MelLib::Vector2(850, 260));
//    judgmentSprite[CheckPushKey::JudgmentType::MISS].Create(MelLib::Texture::Get("Miss"));
//    judgmentSprite[CheckPushKey::JudgmentType::MISS].SetPosition(MelLib::Vector2(850, 260));
//
//    constexpr float judgeY = 80.0f;
//    constexpr float judgeYAdd = 10.0f;
//    judgmentCountSprite[CheckPushKey::JudgmentType::PERFECT].Create(MelLib::Texture::Get("Perfect"));
//    judgmentCountSprite[CheckPushKey::JudgmentType::PERFECT].SetPosition(MelLib::Vector2(0, 0 + judgeYAdd));
//    judgmentCountSprite[CheckPushKey::JudgmentType::GREAT].Create(MelLib::Texture::Get("Great"));
//    judgmentCountSprite[CheckPushKey::JudgmentType::GREAT].SetPosition(MelLib::Vector2(0, judgeY * 1 + judgeYAdd));
//    judgmentCountSprite[CheckPushKey::JudgmentType::GOOD].Create(MelLib::Texture::Get("Good"));
//    judgmentCountSprite[CheckPushKey::JudgmentType::GOOD].SetPosition(MelLib::Vector2(0, judgeY * 2 + judgeYAdd));
//    judgmentCountSprite[CheckPushKey::JudgmentType::MISS].Create(MelLib::Texture::Get("Miss"));
//    judgmentCountSprite[CheckPushKey::JudgmentType::MISS].SetPosition(MelLib::Vector2(0, judgeY * 3 + judgeYAdd));
//
//#pragma endregion
//
//    waterSprite.Create(MelLib::Texture::Get("water"));
//    waterSprite.SetScale(400);
//    waterSprite.SetPosition(MelLib::Vector3(0,0.25f,0));
//    waterSprite.SetAngle(MelLib::Vector3(90, 0, 0));
//
//    // 選曲で選んだ曲と譜面をロード
//    MusicalScoreManager::GetInstance()->Load();
//
//    // カメラ設定
//    MelLib::Camera::Get()->SetRotatePoint(MelLib::Camera::RotatePoint::ROTATE_POINT_TARGET_POSITION);
//    MelLib::Camera::Get()->SetRotateCriteriaPosition(MelLib::Vector3(0, 0, START_CAMERA_POS_Z));
//    MelLib::Camera::Get()->SetAngle(MelLib::Vector3(70, 0, 0));
//    MelLib::Camera::Get()->SetCameraToTargetDistance(40.0f);
//
//    // ライト設定
//    MelLib::DirectionalLight::Get().SetDirection(MelLib::Vector3(0, -1, 1).Normalize());
//
//
//	// 判定表示時間を設定
//	judgmentDrawTimer.SetMaxTime(60 * 0.5f);
//
//
//    // Initializeより先にセット
//    PlayerManager::GetInstance()->SetPlayerMoveVec(CAMERA_ONE_MOVE_POS, FRAME_MOVE_POS);
//    PlayerManager::GetInstance()->PlayerInitialize();
//    Player::SetFrameMoveVec(FRAME_MOVE_POS);
//
//    dropPlayerFlag.resize(MusicalScoreManager::GetInstance()->GetBlockIndexNum());
//
//
//    startObj.Create(MelLib::ModelData::Get("Start"), "Start", nullptr);
//    startObj.SetPosition({ 0,1.2f,-0.5f });
//    startObj.SetAngle({ 0,90,0 });
//
//    // ゴール地点準備
//  // 総コンボ数を参照して座標を指定
//    goalObj.Create(MelLib::ModelData::Get("Start"), "Start", nullptr);
//    const float comboMax = static_cast<float>(MusicalScoreManager::GetInstance()->GetBlockIndexNum());
//    goalObj.SetPosition({ 0,1.2f,-comboMax - 1 });
//    goalObj.SetAngle({ 0,-90,0 });
//
//    // 判定ライン生成
//    MelLib::GameObjectManager::GetInstance()->AddObject(std::make_shared<JudgmentLine>());
//
//    // 開始とか
//    readySprite.Create(MelLib::Texture::Get("Ready"));
//    readySprite.SetPosition(MelLib::Vector2(510, 400));
//    clearSprite.Create(MelLib::Texture::Get("Clear"));
//    clearSprite.SetSubColor(MelLib::Color(0, 0, 0, 255));
//    clearSprite.SetScale(0.7f);
//    clearSprite.SetPosition(MelLib::Vector2(480, 400));
//    gameoverSprite.Create(MelLib::Texture::Get("Gameover"));
//    gameoverSprite.SetSubColor(MelLib::Color(0, 0, 0, 255));
//    gameoverSprite.SetPosition(MelLib::Vector2(500, 400));
//
//    // キー
//    keyNakamiSprite[DIK_D].Create(MelLib::Texture::Get("D_nakami"));
//    keyNakamiSprite[DIK_F].Create(MelLib::Texture::Get("F_nakami"));
//    keyNakamiSprite[DIK_J].Create(MelLib::Texture::Get("J_nakami"));
//    keyNakamiSprite[DIK_K].Create(MelLib::Texture::Get("K_nakami"));
//    keyWakuSprite[DIK_D].Create(MelLib::Texture::Get("D_waku"));
//    keyWakuSprite[DIK_F].Create(MelLib::Texture::Get("F_waku"));
//    keyWakuSprite[DIK_J].Create(MelLib::Texture::Get("J_waku"));
//    keyWakuSprite[DIK_K].Create(MelLib::Texture::Get("K_waku"));
//
//    constexpr float sousaY = 200.0f;
//    constexpr float lX = 450.0f;
//    constexpr float rX = 550.0f;
//    constexpr float sukimaL = 120.0f;
//    constexpr float sukimaR =90.0f;
//    keyNakamiSprite[DIK_D].SetPosition(MelLib::Vector2(lX, sousaY));
//    keyWakuSprite[DIK_D].SetPosition(MelLib::Vector2(lX, sousaY));
//
//    keyNakamiSprite[DIK_F].SetPosition(MelLib::Vector2(lX + sukimaL, sousaY));
//    keyWakuSprite[DIK_F].SetPosition(MelLib::Vector2(lX + sukimaL, sousaY));
//
//    keyNakamiSprite[DIK_J].SetPosition(MelLib::Vector2(1920 - rX - sukimaR, sousaY));
//    keyWakuSprite[DIK_J].SetPosition(MelLib::Vector2(1920 - rX - sukimaR, sousaY));
//
//    keyWakuSprite[DIK_K].SetPosition(MelLib::Vector2(1920 - rX, sousaY));
//    keyNakamiSprite[DIK_K].SetPosition(MelLib::Vector2(1920 - rX, sousaY));
//
//    for(auto& k : keyNakamiSprite)
//    {
//        k.second.SetScale(0.5f);
//    }
//    for (auto& k : keyWakuSprite)
//    {
//        k.second.SetScale(0.5f);
//    }
//}
//
//void Play::Update()
//{
//    for (auto& keyNakami : keyNakamiSprite)
//    {
//        if (MelLib::Input::KeyState(keyNakami.first))
//        {
//            keyNakami.second.SetMulColor(MelLib::Color(255,100,0,255));
//        }
//        else
//        {
//            keyNakami.second.SetMulColor(MelLib::Color(255, 255, 255, 255));
//        }
//    }
//
//    if (gameState == Play::GAME_STATE::BEFORE_PLAY && startTimer.GetMaxOverFlag())
//    {
//        gameState = Play::GAME_STATE::PLAY;
//        startTimer.SetStopFlag(true);
//
//
//        MusicalScoreManager::GetInstance()->PlayMusic();
//        MusicalScoreManager::GetInstance()->PlayHumen();
//    }
//
//    if (gameState != GAME_STATE::BEFORE_PLAY)
//    {
//        if (readySubAlpha < 100.0f)
//        {
//            readySubAlpha += SUB_ALPHA;
//            readySprite.SetSubColor(MelLib::Color(0, 0, 0, MelLib::Color::ParToUChar(readySubAlpha)));
//        }
//        else readySubAlpha = 100.0f;
//    }
//
//
//    // 時間経過したらタイマー停止し、判定を表示しないようにする
//    if (judgmentDrawTimer.GetMaxOverFlag())
//    {
//        judgmentDrawTimer.SetStopFlag(true);
//    }
//
//    switch (gameState)
//    {
//    case Play::GAME_STATE::PLAY:
//        PlayUpdate();
//        break;
//    case Play::GAME_STATE::GAMEOVER:
//        GameoverUpdate();
//        break;
//    case Play::GAME_STATE::CLEAR:
//        ClearUpdate();
//        break;
//    case Play::GAME_STATE::TUTORIAL:
//        TutorialUpdate();
//        break;
//    default:
//        break;
//    }
//
//    MelLib::GameObjectManager::GetInstance()->Update();
//
//    if (MusicalScoreManager::GetInstance()->GetHumenEnd()
//        && (keyTrrigerFrame || notPushMissFrame))
//    {
//        lifeCheckTimer.SetStartFlag(true);
//        lifeCheckTimer.SetMaxTime(6);
//    }
//
//    if (!PlayerManager::GetInstance()->GetLifeZeto() && lifeCheckTimer.GetMaxOverFlag())
//    {
//        lifeCheckTimer.SetStopFlag(true);
//        gameState = GAME_STATE::CLEAR;
//        clearPlayerMoveTime.SetMaxTime(60 * 0.5f);
//        clearPlayerMoveTime.SetStartFlag(true);
//    }
//
//    //if (MelLib::Input::KeyTrigger(DIK_1)) isEnd = true;
//}
//
//void Play::Draw()
//{
//    MelLib::GameObjectManager::GetInstance()->Draw();
//    MusicalScoreManager::GetInstance()->Draw();
//    startObj.Draw();
//    goalObj.Draw();
//    waterSprite.Draw();
//
//
// 
//    
//
//    // カウント表示
//    constexpr float judgmentCountDrawPosY = 80;
//    MelLib::TextWrite::Draw(MelLib::Vector2(280, 0), MelLib::Color(255, 255),
//        std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::PERFECT]), "Arial");
//    MelLib::TextWrite::Draw(MelLib::Vector2(280, judgmentCountDrawPosY * 1), MelLib::Color(255, 255),
//         std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::GREAT]), "Arial");
//    MelLib::TextWrite::Draw(MelLib::Vector2(280, judgmentCountDrawPosY * 2), MelLib::Color(255, 255),
//         std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::GOOD]), "Arial");
//    MelLib::TextWrite::Draw(MelLib::Vector2(280, judgmentCountDrawPosY * 3), MelLib::Color(255, 255),
//         std::to_wstring(judgmentNum[CheckPushKey::JudgmentType::MISS]), "Arial");
//
//    // タイマー動いてる時は判定表示
//    if (!judgmentDrawTimer.GetStopFlag())
//    {
//        judgmentSprite.at(drawJudgment).Draw();
//        if (comboCountNum != 0)
//        {
//            std::wstring wstr1 = std::to_wstring(comboCountNum);
//            MelLib::TextWrite::Draw({ 900,180 }, MelLib::Color(0, 255), wstr1, "Arial");
//        }
//    }
//    for (auto& sprite : judgmentCountSprite)sprite.second.Draw();
//
//
//    // キー
//    for (auto& keyWaku : keyWakuSprite) 
//    {
//        keyWaku.second.Draw();
//    }
//    for (auto& keyNakami : keyNakamiSprite)
//    {
//        keyNakami.second.Draw();
//    }
//
//    if (readySubAlpha != 100.0f && !TUTORIAL)readySprite.Draw();
//    if (clearSpriteDrawTimer.GetMaxOverFlag()) clearSprite.Draw();
//    if (gameoverSpriteDrawTimer.GetMaxOverFlag()) gameoverSprite.Draw();
//
//   
//    if(gameState == GAME_STATE::TUTORIAL)
//    {
//        const MelLib::Vector2 tutorialTextPos = MelLib::Vector2(50, 600);
//        MelLib::TextWrite::Draw(tutorialTextPos, MelLib::Color(255, 255),tutorialText[tutorialNum], "Arial");
//    }
//}
//
//void Play::Finalize()
//{
//    MelLib::GameObjectManager::GetInstance()->Finalize();
//    PlayerManager::GetInstance()->Finalize();
//}
//
//MelLib::Scene* Play::GetNextScene()
//{
//	return new MusicSelect();
//}
