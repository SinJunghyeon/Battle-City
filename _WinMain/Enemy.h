#pragma once
#include "Config.h"
#include "GameObject.h"

class AmmoManager;
class Enemy : public GameObject
{
private:
	int elapsedCount;
	AmmoManager* ammoMgr;

	int fireDelay;
	int fireTimer;
	MoveDir moveDir;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	
	void AutoMove();
};

