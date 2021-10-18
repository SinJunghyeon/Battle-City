#pragma once
#include "Config.h"
#include "GameObject.h"

enum eTankState { IDLE, MOVE, FIRE, DAMAGED, DIE };

class Image;
class EnemyTank : public GameObject
{
protected:
	int mChangeDir = NULL;							//�̵����� ����
	int mChangeObState = NULL;						//���� ����

	eTankState tanckState;
	int mDelayCount = 0;

	Image* mpEImg;

	int etHP = NULL;
	float etAttackValue = NULL;
	
	bool bIsAlive = true;

	int elapsedCount = NULL;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetETHP(int etHP) { this->etHP = etHP; }
	inline void SeteTankState(eTankState state) { this->tanckState = state; }
	inline void SetElapsedCount(int elapsedCount) { this->elapsedCount = elapsedCount; }
	inline int GetElapsedCount() { return this->elapsedCount; }
	inline eTankState GetTankState() { return this->tanckState; }

	EnemyTank();
	~EnemyTank();
};

