#include "BackGroundPlayer.h"

#include<Random.h>

BackGroundPlayer::BackGroundPlayer():GameObject("BPlayer")
{
	modelObjects["main"].Create(MelLib::ModelData::Get("BPlayer"), GetObjectName());
	
	MelLib::Vector3 pos;
	pos.x = MelLib::Random::GetRandomFloatNumberRangeSelect(-30, 30, 1);
	pos.y = 40;
	modelObjects["main"].SetPosition(pos);

	MelLib::Vector3 angle;
	angle.x = MelLib::Random::GetRandomFloatNumberRangeSelect(-180, 180, 1);
	angle.y = 90;
	modelObjects["main"].SetAngle(angle);

	modelObjects["main"].SetScale(3);

	rotateLeft = MelLib::Random::GetRandomNumber(2);
}

void BackGroundPlayer::Update()
{
	AddPosition({ 0,-0.4f,0 });
	MelLib::Vector3 angle = GetAngle();
	
	if(rotateLeft)angle.x += 3;
	else angle.x -= 3;
	SetAngle(angle);
	if (GetPosition().y <= -80)eraseManager = true;
}
