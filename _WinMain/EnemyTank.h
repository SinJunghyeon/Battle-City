#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class EnemyTank : public GameObject
{
protected:
	Image* mpEImg;

	int etHP = NULL;
	float etAttackValue = NULL;
	
	bool bIsAlive = true;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetETHP(int etHP) { this->etHP = etHP; }

	EnemyTank();
	~EnemyTank();
};

