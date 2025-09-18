#pragma once
#include<GameObject.h>
class Block:public MelLib::GameObject
{
private:
	void Move();

private:
	// 1�t���[���œ�����
	static const float FRAME_MOVE_POS;
	// �J�n�t���[���B���̏ꍇ�A�����o���Ă���58�t���[���Ńp�[�t�F�N�g����
	static const short START_FRAME;

	// ������2 1 -1 -2�̊ԂɃL�[��������p�[�t�F�N�g����
	short frame = START_FRAME;

	bool moveStart = false;
	bool left = false;

	bool missBlock = false;

public:
	Block(const MelLib::Vector3& pos,bool left);
	void Update()override;

	short GetFrame()const { return frame; }

public:
	void MoveStart() { moveStart = true; }
	void MoveEnd() { moveStart = false; }

	/// <summary>
	/// �ǂ̂��炢���ꂽ��Ԃ���J�n���邩
	/// </summary>
	/// <returns></returns>
	static float GetStartSidePos() { return FRAME_MOVE_POS * START_FRAME; }

	bool GetMissFlag() { return missBlock; }
	void TrueMiss() { missBlock = true; }
	bool GetLeft()const { return left; }
};

