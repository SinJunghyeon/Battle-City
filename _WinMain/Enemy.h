#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"
#include "Config.h"
#include "AmmoManager.h"

enum class EnemyType { NORMAL, SPEED, RPD, SUPER };

class Enemy : public GameObject
{
private:
	int elapsedCount;
	int fireDelay;
	int fireTimer;

	ecTankState tankState = ecTankState::IDLE;
	EnemyType tankType = EnemyType::NORMAL;

	bool isAlive = false;
	bool isCollision  = false;
	bool isItem = false;

	AmmoManager ammoMgr;

	RECT tempRect;

	Image* spawnImg;
	int elapsedSpawn = NULL;
	int spawnCount = NULL;

	int hp = 1;
	int elapsedTurn = 0;
	int elapsedSpeed = 0;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	
	void MoveFrame();
	void Move(MoveDir dir);

	void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }

	void SetTileMap(TILE_INFO* tile) { this->tile = tile; }

	ecTankState GetTankState() { return tankState; }
	void SetTankState(ecTankState tankState) { this->tankState = tankState; }

	bool GetIsAilve() { return this->isAlive; }
	void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }

	inline AmmoManager GetAmmoManager() { return this->ammoMgr; }
	inline bool GetIsCollision() { return this->isCollision; }
	inline void SetIsCollision(bool isCollision) { this->isCollision = isCollision; }

	inline int GetHP() { return this->hp; }
	inline void SetHP(int hp) { this->hp = hp; }

	inline EnemyType GetEnemyType() { return this->tankType; }
	void SetEnemyType(EnemyType type);

	virtual ~Enemy() = default;
};

