//#pragma once
//#include <Scene.h>
//#include<FrameTimer.h>
//#include<Sprite2D.h>
//#include<Sprite3D.h>
//#include<ModelObject.h>
//
//#include"CheckPushKey.h"
//
//
//class Play :
//    public MelLib::Scene
//{
//private:
//	enum class GAME_STATE 
//	{
//		BEFORE_PLAY,
//		PLAY,
//		GAMEOVER,
//		CLEAR,
//		TUTORIAL
//	};
//	GAME_STATE gameState = GAME_STATE::BEFORE_PLAY;
//	const bool TUTORIAL = false;
//
//	MelLib::ModelObject startObj;
//	MelLib::ModelObject goalObj;
//	MelLib::Sprite3D waterSprite;
//
//	// 譜面が流れ始めるまでの時間
//	MelLib::FrameTimer startTimer;
//
//	// 判定
//	CheckPushKey::JudgmentType judgmentType = CheckPushKey::JudgmentType::NONE;
//	// 描画する判定　処理の都合上分けてる
//	CheckPushKey::JudgmentType drawJudgment = CheckPushKey::JudgmentType::NONE;
//	// 判定表示時間を測定するタイマー
//	MelLib::FrameTimer judgmentDrawTimer;
//
//	// 判定の記録
//	std::unordered_map<CheckPushKey::JudgmentType, unsigned short>judgmentNum;
//
//	bool dropCheck = false;
//
//	// カメラの移動量
//	float cameraMoveVec = 0.0f;
//	// 一回の移動量分移動したかを確認するための変数
//	float cameraOneMoveCheckCounter = 0.0f;
//
//	const float START_CAMERA_POS_Z = -10.0f;
//	// カメラの一回の移動()
//	const float CAMERA_ONE_MOVE_POS = 1.0f;
//	// 1フレームの移動量
//	const float FRAME_MOVE_POS = 1.0f;
//
//	// 現在確認するブロック プレイヤーを落下させるかどうかに使用
//	unsigned int currentCheckBlock = 0;
//
//	// ブロックが無くてもプレイヤーが落ちていたら落ちずに進むようにするためのフラグ
//	std::vector<bool>dropPlayerFlag;
//  
//	// クリア後にプレイヤーとカメラを名動かす時に使う時間
//	MelLib::FrameTimer clearPlayerMoveTime;
//	bool clearMoveEnd = false;
//
//	// 押したフレームかどうか
//	bool keyTrrigerFrame = false;
//	bool notPushMissFrame = false;
//
//	// 終了後にライフの計算を行うためのタイマー
//	MelLib::FrameTimer lifeCheckTimer;
//
//	float clearCameraMoveVec = 0.0f;
//
//#pragma region コンボ
//	void ComboCount(bool isCombo);
//
//	int comboCountNum = 0;
//
//
//#pragma endregion
//
//	// 判定スプライト
//	std::unordered_map<CheckPushKey::JudgmentType, MelLib::Sprite2D >judgmentSprite;
//	std::unordered_map<CheckPushKey::JudgmentType, MelLib::Sprite2D >judgmentCountSprite;
//
//	std::unordered_map<BYTE, MelLib::Sprite2D >keyNakamiSprite;
//	std::unordered_map<BYTE, MelLib::Sprite2D >keyWakuSprite;
//
//	const float SUB_ALPHA = 5.0f;
//	
//	MelLib::Sprite2D readySprite;
//	float readySubAlpha = 0.0f;
//
//
//	MelLib::FrameTimer clearSpriteDrawTimer;
//	MelLib::Sprite2D clearSprite;
//	float clearSubAlpha = 100.0f;
//
//	MelLib::Sprite2D gameoverSprite;
//	MelLib::FrameTimer gameoverSpriteDrawTimer;
//
//	//何個目のチュートリアルメッセージか
//	int tutorialNum = 0;
//
//	std::unordered_map<int, std::wstring>tutorialText;
//private:
//	/// <summary>
//	/// 音ゲーのプレイに関係してる部分の処理をまとめた関数
//	/// </summary>
//	void PlayUpdate();
//
//	/// <summary>
//	/// 判定カウント
//	/// </summary>
//	void CountJudgmentNum();
//
//	/// <summary>
//	/// カメラの移動量を加算
//	/// </summary>
//	void AddCameraMovePos();
//
//	/// <summary>
//	/// カメラ移動
//	/// </summary>
//	void MoveCamera();
//
//	void UpdatePlayer();
//
//	/// <summary>
//	/// プレイヤー移動
//	/// </summary>
//	void MovePlayer();
//
//
//	void CheckDropPlayer();
//	void GameoverUpdate();
//	void ClearUpdate();
//	void TutorialUpdate();
//public:
//	Play(const bool tutorial);
//	~Play();
//	void Initialize()override;//初期化
//	void Update()override;
//	void Draw()override;
//	void Finalize()override;//終了処理
//	Scene* GetNextScene()override;//次のシーンの指定
//
//};
//
