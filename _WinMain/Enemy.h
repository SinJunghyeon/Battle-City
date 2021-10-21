#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"
#include "Config.h"
#include "AmmoManager.h"

class Enemy : public GameObject
{
private:
	int elapsedCount;
	int fireDelay;
	int fireTimer;

	ecTankState tankState = ecTankState::IDLE;

	bool isAlive = false;
	bool isCollision  = false;

	AmmoManager ammoMgr;

	RECT tempRect;

	Image* spawnImg;
	int elapsedSpawn = NULL;
	int spawnCount = NULL;


	int hp = 1;
	int elapsedTurn = 0;
	int elapsedSpeed = 0;


public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	
	void MoveFrame();
	void Move(MoveDir dir);

	void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }

	void SetTileMap(TILE_INFO* tile) { this->tile = tile; }

	ecTankState GetTankState() { return tankState; }
	void SetTankState(ecTankState tankState) { this->tankState = tankState; }

	void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }


	inline AmmoManager GetAmmoManager() { return this->ammoMgr; }
	bool GetIsCollision() { return this->isCollision; }
	void SetIsCollision(bool isCollision) { this->isCollision = isCollision; }
};

