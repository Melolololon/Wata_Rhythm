#include "Player.h"
#include"TestObject.h"
#include<Input.h>
#include<LibMath.h>

float Player::frameMoveVec;

void Player::Move()
{
	if (isDrop)return;
	AddPosition(MelLib::Vector3(0, 0, -frameMoveVec));
}

void Player::Drop()
{
	isDrop = true;
	AddPosition({0.0f,-1.5f,0.0f});
	modelObjects["main"].SetAnimation("fall");
	modelObjects["main"].SetAnimationPlayFlag(true);
	animLoopStartPoint = 16;
}

void Player::SetClearAnimation() 
{
	// 落ちて浮いてる時に落下アニメーション再生してバタバタさせる

	if(!isDrop)modelObjects["main"].SetAnimation("Clear");
	modelObjects["main"].SetAnimationPlayFlag(true);
}

void Player::LoadRes()
{

}


Player::Player()
	:GameObject("Player")
{
	
	modelObjects["main"].Create(MelLib::ModelData::Get("Player"), GetObjectName());
	modelObjects["main"].SetPosition(GetPosition());
	modelObjects["main"].SetScale(0.35f);
	modelObjects["main"].SetAngle(MelLib::Vector3(0,90,0));
	modelObjects["main"].SetAnimation("Normal");
}

void Player::Update()
{
	if (modelObjects["main"].GetCurrentAnimationName() == "fall"
		&& modelObjects["main"].GetAnimationEndFlag())
	{
		modelObjects["main"].SetAnimationFrame(animLoopStartPoint);
	}

	modelObjects["main"].Update();

}

void Player::Draw()
{
	AllDraw();
}

void Player::Hit
(
	const GameObject& object, 
	const MelLib::ShapeType3D shapeType, 
	const std::string& shapeName, 
	const MelLib::ShapeType3D hitObjShapeType,
	const std::string& hitShapeName
)
{


}

std::shared_ptr<MelLib::GameObject> Player::GetNewPtr()
{
	return std::make_shared<Player>();
}
