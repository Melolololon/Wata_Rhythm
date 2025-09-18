#pragma once
#include "Player.h"
#include <array>

/// <summary>
/// �v���C���[�Ǘ��N���X
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

	// �ړ��J�n
	void MoveStart() 
	{
		isMove = true; 
		currentMoveVec = 0.0f;
	}

	// �ړ����I��������ǂ������m�F����֐�
	bool MoveEndFrame() { return !isMove && preIsMove; }

	bool GetPrePlayerDropMove() { return prePlayerDropMove; }

	void SetPlayerClearAnimation();
private:
	const int LIFE_MAX = 15;
	// �c�@��
	int life = LIFE_MAX;

	std::vector<std::shared_ptr<Player>> players{};

	// �擪�v���C���[�̔ԍ�
	unsigned int currentTopPlayer = 0;

	// 1�t���[���̈ړ���
	float frameMoveVec = 0.0f;
	// ���̈ړ���
	float oneMoveVec = 0.0f;
	// �ړ������ǂ���
	bool isMove = false;
	bool preIsMove = false;
	// ���݂̈ړ���
	float currentMoveVec = 0.0f;

	// �O�̃v���C���[�����������Ƃɂ�蓮���Ă��邩�ǂ���
	bool prePlayerDropMove = false;


public:
	PlayerManager() = default;
	PlayerManager(const PlayerManager&) = delete;
	~PlayerManager() = default;
	PlayerManager operator=(const PlayerManager&) = delete;
};