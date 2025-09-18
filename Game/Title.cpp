#include "Title.h"
#include"MusicSelect.h"

#include"BackGroundPlayer.h"

#include"MusicalScoreManager.h"
#include"GameObjectManager.h"
#include"Play.h"
#include"Fade.h"

#include<Input.h>

Title::Title()
{
}

Title::~Title()
{
}

void Title::Initialize()
{
	Fade::GetInstance()->Initializ();

	title.Create(MelLib::Texture::Get("title"));
	push.Create(MelLib::Texture::Get("push"));
	push.SetPosition(MelLib::Vector2(240,820));

	MelLib::Camera::Get()->SetRotatePoint(MelLib::Camera::RotatePoint::ROTATE_POINT_TARGET_POSITION);
	MelLib::Camera::Get()->SetRotateCriteriaPosition(MelLib::Vector3(0, 0, 0));
	MelLib::Camera::Get()->SetAngle(MelLib::Vector3(0, 0, 0));
	MelLib::Camera::Get()->SetCameraToTargetDistance(40.0f);
	
	addTimer.SetMaxTime(60 * 0.75f);
	addTimer.SetStartFlag(true);

	MelLib::Sound::PlayLoadSound(MelLib::SoundData::Get("title"), MelLib::Sound::LOOP_INFINITY, { 70 }, "title");
}

void Title::Update()
{
	Fade::GetInstance()->Update();
	if (MelLib::Input::KeyTrigger(DIK_SPACE) && !Fade::GetInstance()->GetIsFade())
	{
		Fade::GetInstance()->Start();
		MelLib::Sound::PlayLoadSound(MelLib::SoundData::Get("push"), 0, {70});
	}
	if (Fade::GetInstance()->GetChangeSceneFlag())isEnd = true;

	if (addTimer.GetMaxOverFlag())
	{
		MelLib::GameObjectManager::GetInstance()->AddObject
		(
			std::make_shared<BackGroundPlayer>()
		);
		addTimer.ResetTimeZero();
	}
	MelLib::GameObjectManager::GetInstance()->Update();
}

void Title::Draw()
{
	MelLib::GameObjectManager::GetInstance()->Draw();

	title.Draw();
	push.Draw();
	Fade::GetInstance()->Draw();
}

void Title::Finalize()
{
	addTimer.SetStopFlag(true);
	MelLib::GameObjectManager::GetInstance()->Finalize();


	// ‰¼
	MusicalScoreManager::GetInstance()->SetMusicData
	(
		L"Tutorial",
		L"Kato",
		120,
		false
	);

	//MelLib::Sound::StopSound("title");
}

MelLib::Scene* Title::GetNextScene()
{
	return new Play(true);
}
