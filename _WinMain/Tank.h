#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"

enum class ecTankState { IDLE, MOVE, FIRE, DAMAGED, DIE };

class Tank : public GameObject
{
public:
	int ammoCount;
	Ammo* ammoPack;

	ecTankState tanckState = ecTankState::IDLE;
	int elapsedCount = NULL;
	bool isAlive = true;


public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void Fire();
	void ProcessInputKey();

	void Move(MoveDir dir);

	inline void SetIsAlive(bool alive) { this->isAlive = alive; }

	Tank();
	~Tank();
};

