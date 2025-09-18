#include "PlayerManager.h"
#include "GameObjectManager.h"

PlayerManager* PlayerManager::GetInstance()
{
	static PlayerManager* instance = new PlayerManager();
	return instance;
}

void PlayerManager::PlayerInitialize()
{
	currentMoveVec = 0.0f;
	prePlayerDropMove = false;
	isMove = false;
	preIsMove = false;
	life = LIFE_MAX;
	currentTopPlayer = 0;

	// オブジェクトを生成
	for (int i = 0; i < LIFE_MAX; i++)
	{
		std::shared_ptr<Player> p = std::make_shared<Player>();

		players.push_back(p);

		MelLib::Vector3 pos = players[i]->GetPosition();

		if (i >= 0) players[i]->AddPosition(MelLib::Vector3(0, 1.15f, oneMoveVec * i));

		MelLib::GameObjectManager::GetInstance()->AddObject(players[i]);
		
		
	}
}

void PlayerManager::Update()
{
	if (preIsMove && !isMove)
	{
		prePlayerDropMove = false;
	}

	preIsMove = isMove;
	if (currentMoveVec >= oneMoveVec)
	{
		isMove = false;
		return;
	}
}

void PlayerManager::Finalize()
{
	players.clear();
}

void PlayerManager::MovePlayer()
{
	if (!isMove)return;
	for (int i = currentTopPlayer; i < players.size(); i++)
	{
		players[i]->Move();
	}
	currentMoveVec += frameMoveVec;
}

void PlayerManager::DropPlayer()
{
	// 前が落ちたことにより動いていたら落下処理を無視する
	if (prePlayerDropMove)return;

	if (currentTopPlayer >= LIFE_MAX)return;
	players[currentTopPlayer]->Drop();
	currentTopPlayer++;

	// 強制的に動かす
	prePlayerDropMove = true;
	MoveStart();

	life--;
}

void PlayerManager::SetPlayerClearAnimation()
{
	for (auto& p : players)p->SetClearAnimation();
}



