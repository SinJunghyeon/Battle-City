#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"

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

	int ptHP = NULL;			//플레이어 HP
	float ptAttackValue = NULL;	//공격력

	int ptLife = NULL;			//플레이어 목숨
	bool bIsAlive = true;		//살아있는지?

	int ptScore = NULL;			//플레이어 탱크 점수

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

	Tank();
	~Tank();
};

