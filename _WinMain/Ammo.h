#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Tank;
class Enemy;
class Ammo : public GameObject
{
private:
	Tank* pPlayerTank;
	Enemy* pEnemyTank;
	bool isFire;

	Image* img;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetIsFire(bool fire);
	inline bool GetIsFire() { return this->isFire; }

	Ammo();
	~Ammo();
};

