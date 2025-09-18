#pragma once
#include "Player.h"
#include <array>

/// <summary>
/// プレイヤー管理クラス
/// </summary>
class PlayerManager
{
private:

public:

	static PlayerManager* GetInstance();

public:
	void PlayerInitialize();
	void Update();
	void Finalize();

	void MovePlayer();
	void DropPlayer();


	bool GetLifeZeto() { return life <= 0; }

	void SetPlayerMoveVec(float oneVec, float frameVec)
	{
		oneMoveVec = oneVec; 
		frameMoveVec = frameVec;
	}

	// 移動開始
	void MoveStart() 
	{
		isMove = true; 
		currentMoveVec = 0.0f;
	}

	// 移動が終わったかどうかを確認する関数
	bool MoveEndFrame() { return !isMove && preIsMove; }

	bool GetPrePlayerDropMove() { return prePlayerDropMove; }

	void SetPlayerClearAnimation();
private:
	const int LIFE_MAX = 15;
	// 残機数
	int life = LIFE_MAX;

	std::vector<std::shared_ptr<Player>> players{};

	// 先頭プレイヤーの番号
	unsigned int currentTopPlayer = 0;

	// 1フレームの移動量
	float frameMoveVec = 0.0f;
	// 一回の移動量
	float oneMoveVec = 0.0f;
	// 移動中かどうか
	bool isMove = false;
	bool preIsMove = false;
	// 現在の移動量
	float currentMoveVec = 0.0f;

	// 前のプレイヤーが落ちたことにより動いているかどうか
	bool prePlayerDropMove = false;


public:
	PlayerManager() = default;
	PlayerManager(const PlayerManager&) = delete;
	~PlayerManager() = default;
	PlayerManager operator=(const PlayerManager&) = delete;
};