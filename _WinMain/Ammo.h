#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Tank;
class Ammo : public GameObject
{
private:
	Tank* mpPlayerTank;

	bool isFire;

	Image* img;

	MoveDir moveDir = MoveDir::UP;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetIsFire(bool fire);
	inline bool GetIsFire() { return this->isFire; }

	inline void SetMoveDir(MoveDir moveDir) { this->moveDir = moveDir; }

	Ammo();
	~Ammo();
};

