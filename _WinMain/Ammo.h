#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Tank;
class Enemy;
class Ammo : public GameObject
{
private:
	Tank* pPlayerTank = nullptr;
	Enemy* pEnemyTank = nullptr;
	bool isFire = false;

	Image* img = nullptr;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void SetIsFire(bool fire);
	inline bool GetIsFire() { return this->isFire; }

	Ammo();
	virtual ~Ammo() = default;
};

