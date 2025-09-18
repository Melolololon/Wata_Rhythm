#include "Game.h"
#include<Library.h>
#include"SceneManager.h"
#include"SceneEditer.h"
#include"GameObjectManager.h"

#include"Camera.h"
#include"ModelData.h"
#include"TextWrite.h"
#include"Texture.h"
#include"Input.h"
#include"ImguiManager.h"
#include<GuiValueManager.h>

#include"PlayerManager.h"
#include"Player.h"
#include"TestObject.h"

#include"Collision.h"
#include"LibMath.h"
#include"MusicalScoreManager.h"

#include"Player.h"


#include"Play.h"
#include"MusicSelect.h"
#include"Title.h"

#include<filesystem>

Game::Game() {}

Game::~Game() {}
Game* Game::GetInstance()
{
	static Game game;
	return &game;
}

void Game::Run()
{
	MelLib::ImguiManager::GetInstance()->SetReleaseDrawFlag(false);
	
	Initialize();

	while (1)
	{

		MelLib::Library::LoopStartProcess();
		//DWORD start = timeGetTime();

		if (MelLib::Input::KeyTrigger(DIK_ESCAPE))MelLib::Library::EndFlagTrue();
		if (MelLib::Library::GetIsEnd())break;
		
		//ImGui::ShowDemoWindow();

		Update();
		Draw();

		//DWORD end = timeGetTime();
		//DWORD time = end - start;

		//MelLib::TextWrite::Draw(0, MelLib::Color(255, 255), std::to_wstring(time), "ArialMini");
		MelLib::Library::LoopEndProcess();

	}

	MusicalScoreManager::GetInstance()->Finalize();
	Finalize();

}

void Game::Initialize()
{
	MelLib::Library::Initialize(1920, 1080, MelLib::Color(100,170,255,255),L"4023_わたリズム");
	MelLib::Library::SetFramesPerSecond60(true);

	Load();
#pragma region 

	MelLib::GameObjectManager::GetInstance()->SetMouseCollisionFlag(true);
	MelLib::GameObjectManager::GetInstance()->ReserveObjectArray(100);

	MelLib::SceneEditer::GetInstance()->SetEditerFlag(false);
	// iugui関連でバグが出るため、SetStartSceneはEditerの処理の下に書く
	MelLib::SceneManager::GetInstance()->SetStartScene(new Title());
#pragma endregion


	MelLib::TextWrite::CreateFontData(L"Arial", 64.0f, "Arial");
	MelLib::TextWrite::CreateFontData(L"Arial", 32.0f, "ArialMini");

}


void Game::Finalize()
{
	MelLib::Library::Finalize();
}

void Game::Load()
{
	MelLib::ModelData::Load("Resource/Model/Block/Block.obj", false, "Block");
	MelLib::ModelData::Load("Resource/Model/Player/Player.fbx", false, "Player");
	MelLib::ModelData::Load("Resource/Model/BPlayer/BPlayer.obj", false, "BPlayer");
	MelLib::ModelData::Load("Resource/Model/Stage/Start/Start.obj", false, "Start");

	MelLib::Texture::Load("Resource/Texture/water.png","water");
	MelLib::Texture::Load("Resource/Texture/title.png","title");
	MelLib::Texture::Load("Resource/Texture/guide.png","push");


	MelLib::Texture::Load("Resource/Texture/perfect.png", "Perfect");
	MelLib::Texture::Load("Resource/Texture/great.png", "Great");
	MelLib::Texture::Load("Resource/Texture/good.png", "Good");
	MelLib::Texture::Load("Resource/Texture/miss.png", "Miss");

	MelLib::Texture::Load("Resource/Texture/ready.png", "Ready");
	MelLib::Texture::Load("Resource/Texture/clear.png", "Clear");
	MelLib::Texture::Load("Resource/Texture/failed.png", "Gameover");



	MelLib::Texture::Load("Resource/Texture/D_waku.png", "D_waku");
	MelLib::Texture::Load("Resource/Texture/F_waku.png", "F_waku");
	MelLib::Texture::Load("Resource/Texture/J_waku.png", "J_waku");
	MelLib::Texture::Load("Resource/Texture/K_waku.png", "K_waku");
	MelLib::Texture::Load("Resource/Texture/D_nakami.png", "D_nakami");
	MelLib::Texture::Load("Resource/Texture/F_nakami.png", "F_nakami");
	MelLib::Texture::Load("Resource/Texture/J_nakami.png", "J_nakami");
	MelLib::Texture::Load("Resource/Texture/K_nakami.png", "K_nakami");

	MelLib::Texture::Load("Resource/Texture/arrow.png", "Arrow");


	for (const auto& dirEntry : std::filesystem::directory_iterator("Humen/"))
	{
		std::string path = dirEntry.path().string();
		
		std::string name = path;
		name.erase(name.begin(), name.begin() + 6);

		path += "/Music.wav";

		bool res = MelLib::SoundData::Load(path, name);
 		int hwui = 0;
	}



	MelLib::SoundData::Load("Resource/Sound/IKIGAI.wav", "title");
	MelLib::SoundData::Load("Resource/Sound/maou_se_system23.wav", "push");

}

void Game::Update()
{

	MelLib::SceneManager::GetInstance()->Update();

}

void Game::Draw()
{
	MelLib::SceneManager::GetInstance()->Draw();
}