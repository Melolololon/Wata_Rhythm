#include "Block.h"

#ifdef _DEBUG
#include"TextWrite.h"
#endif // _DEBUG


const float Block::FRAME_MOVE_POS = 1;
const short Block::START_FRAME = 60;

void Block::Move()
{
	MelLib::Vector3 addPos;

	if (left)addPos = MelLib::Vector3(FRAME_MOVE_POS, 0, 0);
	else addPos = MelLib::Vector3(-FRAME_MOVE_POS, 0, 0);

	AddPosition(addPos);
}

Block::Block(const MelLib::Vector3& pos, bool left) :GameObject("Block")
,left(left)
{
	//modelObjects["main"].Create(MelLib::ModelData::Get(MelLib::ShapeType3D::BOX), GetObjectName());
	modelObjects["main"].Create(MelLib::ModelData::Get("Block"), GetObjectName());
	modelObjects["main"].SetScale(MelLib::Vector3(1.10f, 1, 1));
	modelObjects["main"].SetAngle(MelLib::Vector3(0,180,0));
	SetPosition(pos);
}

void Block::Update()
{
	// à⁄ìÆíÜ
	if (moveStart)
	{
		Move();
		// ÉfÉNÉäÉÅÉìÉg
		frame--;
	}


	//MelLib::TextWrite::Draw(0, MelLib::Color(255, 255), std::to_wstring(frame), "Arial");
}
