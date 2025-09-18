#pragma once
#include<GameObject.h>
#include<GuiValue.h>
#include<Sprite2D.h>

class Player :
    public MelLib::GameObject
{

private:
	static float frameMoveVec;
	bool isDrop = false;

	// アニメーションのループ開始地点
	int animLoopStartPoint = 0;
public:
	static void SetFrameMoveVec(const float vec) { frameMoveVec = vec; }

	Player();
	
	// 更新
    void Update()override;
    
	//描画
	void Draw()override;
    
	/// <summary>
	/// 当たった時に呼ばれる関数
	/// </summary>
	/// <param name="object">衝突したオブジェクトの参照</param>
	/// <param name="shapeType">相手と衝突した自分の当たり判定の形状</param>
	/// <param name="shapeName">相手と衝突した自分の当たり判定の名前</param>
	/// <param name="hitObjShapeType">衝突したオブジェクトの当たり判定の形状</param>
	/// <param name="hitShapeName">衝突したオブジェクトの判定の名前</param>
	void Hit
	(
		const GameObject& object,
		const MelLib::ShapeType3D shapeType,
		const std::string& shapeName,
		const MelLib::ShapeType3D hitObjShapeType,
		const std::string& hitShapeName
	)override;

	std::shared_ptr<MelLib::GameObject> GetNewPtr()override;

	void SetParent(std::shared_ptr<Player> player) { parent = player; }

	static void LoadRes();


	void Move();


	/// <summary>
	/// ブロックが無かった時に落ちる処理
	/// </summary>
	void Drop();

	void SetClearAnimation();
private:
	// 
	// 前にいるプレイヤー
	std::shared_ptr<Player> parent = nullptr;
};

