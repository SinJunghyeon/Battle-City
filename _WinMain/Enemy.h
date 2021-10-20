#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"
#include "Config.h"

class AmmoManager;
class Enemy : public GameObject
{
private:
	int elapsedCount1;
	int elapsedCount2;
	int fireDelay;
	int fireTimer;

	ecTankState tankState = ecTankState::IDLE;

	bool isAlive = false;
	bool isCollision;

	AmmoManager* ammoMgr;

	// 충돌처리용 RECT
	RECT tempRect;

	Image* spawnImg;
	int elapsedSpawn = NULL;
	int spawnCount = NULL;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	
	void AutoMove();
	void Move(MoveDir dir);

	bool Collider();

	void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
	inline void SetTileMap(TILE_INFO* tile) { this->tile = tile; }

	inline ecTankState GetTankState() { return tankState; }
	inline void SetTankState(ecTankState tankState) { this->tankState = tankState; }

	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
};

