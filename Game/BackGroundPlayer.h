#pragma once
#include"GameObject.h"
class BackGroundPlayer:public MelLib::GameObject
{
	bool rotateLeft = false;
public:
	BackGroundPlayer();

	// çXêV
	void Update()override;
};

