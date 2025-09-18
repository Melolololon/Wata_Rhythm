#pragma once
#include<GameObject.h>
class Block:public MelLib::GameObject
{
private:
	void Move();

private:
	// 1フレームで動く量
	static const float FRAME_MOVE_POS;
	// 開始フレーム。この場合、動き出してから58フレームでパーフェクト判定
	static const short START_FRAME;

	// こいつが2 1 -1 -2の間にキー押したらパーフェクト判定
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
	/// どのくらい離れた状態から開始するか
	/// </summary>
	/// <returns></returns>
	static float GetStartSidePos() { return FRAME_MOVE_POS * START_FRAME; }

	bool GetMissFlag() { return missBlock; }
	void TrueMiss() { missBlock = true; }
	bool GetLeft()const { return left; }
};

