#include "JudgmentLine.h"

JudgmentLine::JudgmentLine():GameObject("Line")
{
	modelObjects["main"].Create(MelLib::ModelData::Get(MelLib::ShapeType3D::BOX), GetObjectName());
	modelObjects["main"].SetMulColor(MelLib::Color(255, 0, 0, 120));
	modelObjects["main"].SetScale(MelLib::Vector3(1,0.05f,5000));
	modelObjects["main"].SetPosition(MelLib::Vector3(0, 0.70f, 0));
}

void JudgmentLine::Update()
{
}
