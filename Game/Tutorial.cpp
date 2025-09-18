#include "Tutorial.h"
#include"MusicSelect.h"
#include<TextWrite.h>
#include<Input.h>

void Tutorial::PlayUpdate()
{
	//�`���[�g���A����i�߂�
	if (MelLib::Input::KeyTrigger(DIK_SPACE)) tutorialNum++;
	if (tutorialNum > 7) {
		tutorialState = Tutorial::Tutorial_State::CLEAR;
	}
}

void Tutorial::ClearUpdate()
{
	if (MelLib::Input::KeyTrigger(DIK_SPACE))isEnd = true;
}

Tutorial::Tutorial()
{
}

Tutorial::~Tutorial()
{
}

void Tutorial::Initialize()
{
	MelLib::Camera::Get()->SetRotatePoint(MelLib::Camera::RotatePoint::ROTATE_POINT_TARGET_POSITION);
	MelLib::Camera::Get()->SetRotateCriteriaPosition(MelLib::Vector3(0, 0, START_CAMERA_POS_Z));
	MelLib::Camera::Get()->SetAngle(MelLib::Vector3(70, 0, 0));
	MelLib::Camera::Get()->SetCameraToTargetDistance(40.0f);

	waterSprite.Create(MelLib::Texture::Get("water"));
	waterSprite.SetScale(400);
	waterSprite.SetPosition(MelLib::Vector3(0, 0.25f, 0));
	waterSprite.SetAngle(MelLib::Vector3(90, 0, 0));

	startObj.Create(MelLib::ModelData::Get("Start"), "Start", nullptr);
	startObj.SetPosition({ 0,1.2f,-0.5f });
	startObj.SetAngle({ 0,90,0 });

	goalObj.Create(MelLib::ModelData::Get("Start"), "Start", nullptr);
	goalObj.SetAngle({ 0,-90,0 });
}

void Tutorial::Update()
{
	switch (tutorialState)
	{
	case Tutorial::Tutorial_State::PLAY:
		PlayUpdate();
		break;
	case Tutorial::Tutorial_State::CLEAR:
		ClearUpdate();
		break;
	default:
		break;
	}

}

void Tutorial::Draw()
{
	startObj.Draw();
	goalObj.Draw();
	waterSprite.Draw();
	switch (tutorialNum)
	{
	case 0:
		MelLib::TextWrite::Draw({ 50,600 }, MelLib::Color(255, 255), L"�`���[�g���A��", "Arial");

		break;
	case 1:
		MelLib::TextWrite::Draw({ 50,600 }, MelLib::Color(255, 255), L"�u���b�N��n���ăS�[����ڎw�����I", "Arial");

		break;
	case 2:
		MelLib::TextWrite::Draw({ 50,600 }, MelLib::Color(255, 255), L"�u���b�N��F�AD�AJ�AK�L�[�Ŏ~�߂����I", "Arial");

		break;
	case 3:
		MelLib::TextWrite::Draw({ 50,600 }, MelLib::Color(255, 255), L"�����炭��u���b�N��F��������D�Ŏ~�߂���I", "Arial");

		break;
	case 4:
		MelLib::TextWrite::Draw({ 50,600 }, MelLib::Color(255, 255), L"�E���炭��u���b�N��J��������K�Ŏ~�߂���I", "Arial");

		break;
	case 5:
		MelLib::TextWrite::Draw({ 50,600 }, MelLib::Color(255, 255), L"�v���C���[�͐��ɗ����Ă����ɍT����������Q�[���I�[�o�[�ɂȂ�Ȃ���I", "Arial");

		break;
	case 6:
		MelLib::TextWrite::Draw({ 50,600 }, MelLib::Color(255, 255), L"�L�������S�����ɗ������Ⴄ�ƃQ�[���I�[�o�[�ɂȂ��I", "Arial");

		break;
	case 7:
		MelLib::TextWrite::Draw({ 50,600 }, MelLib::Color(255, 255), L"���ۂɂ���Ă݂悤�I", "Arial");

		break;
	default:
		MelLib::TextWrite::Draw({ 50,600 }, MelLib::Color(255, 255), L"�X�y�[�X�ŋȑI���ɖ߂��I", "Arial");

		break;
	}

}

void Tutorial::Finalize()
{
}

MelLib::Scene* Tutorial::GetNextScene()
{
	return new MusicSelect();
}
