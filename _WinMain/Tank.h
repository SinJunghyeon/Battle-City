#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"

class Tank : public GameObject	// 상속관계
{
public:
	int ammoCount;
	Ammo* ammoPack;

	MoveDir moveDir;

	bool isAlive;


public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void Fire();
	void Reload();
	void ProcessInputKey();

	// 실습3. 탱크를 상하좌우(WASD)로 움직여보자.
	void Move(MoveDir dir);

	inline void SetIsAlive(bool alive) { this->isAlive = alive; }

	Tank();
	~Tank();
};

