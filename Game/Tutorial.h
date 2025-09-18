#pragma once
#include <Scene.h>
#include<Sprite3D.h>
#include<ModelObject.h>
#include"Sprite2D.h"
class Tutorial :
	public MelLib::Scene
{
private:

	enum class Tutorial_State
	{
		PLAY,
		CLEAR
	};

	Tutorial_State tutorialState = Tutorial_State::PLAY;

	void PlayUpdate();

	void ClearUpdate();

private:
	//���ڂ̃`���[�g���A�����b�Z�[�W��
	int tutorialNum = 0;

	MelLib::ModelObject startObj;
	MelLib::ModelObject goalObj;
	MelLib::Sprite3D waterSprite;
	const float START_CAMERA_POS_Z = -10.0f;
public:
	Tutorial();
	~Tutorial();
	void Initialize()override;//������
	void Update()override;
	void Draw()override;
	void Finalize()override;//�I������
	Scene* GetNextScene()override;//���̃V�[���̎w��
};

