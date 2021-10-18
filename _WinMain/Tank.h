#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"
#include "MapConfig.h"

enum class ecTankState { IDLE, MOVE, FIRE, DAMAGED, DIE };

class Item;
class Tank : public GameObject
{
public:
	int ammoCount;
	Ammo* ammoPack;
	//bool bObtainItem = false;

	ecTankState tanckState = ecTankState::IDLE;
	int elapsedCount = NULL;
	bool isAlive = true;

	//¾ÆÀÌÅÛ
	Item* mpItem = nullptr;
	RECT itemShape;

	int ptHP = NULL;				//플레이어 HP
	float ptAttackValue = NULL;		//공격력

	int ptLife = NULL;				//플레이어 목숨
	bool bIsAlive = true;			//살아있는지?

	int ptScore = NULL;				//플레이어 탱크 점수

	// 타일 정보
	TILE_INFO* tile;

	// 충돌처리용 RECT
	RECT tempRect;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void Fire();
	void ProcessInputKey();

	void Move(MoveDir dir);
	void CollisionItem();
	void FunctionItem();

	inline void SetIsAlive(bool alive) { this->isAlive = alive; }
	inline void SetAmmoCount(int ammoCount) { this->ammoCount = ammoCount; }

	// 타일 정보를 받아오는 함수
	inline void SetTileMap(TILE_INFO* tile) { this->tile = tile; }

	Tank();
	~Tank();
};

