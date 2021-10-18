#pragma once
#include "Config.h"
#include "GameObject.h"

enum eTankState { IDLE, MOVE, FIRE, DAMAGED, DIE };

class Image;
class EnemyTank : public GameObject
{
protected:
	int mChangeDir = NULL;							//이동방향 설정
	int mChangeObState = NULL;						//상태 설정

	eTankState tanckState;
	int mDelayCount = 0;

	Image* mpEImg;

	int etHP = NULL;
	float etAttackValue = NULL;
	
	bool bIsAlive = true;

	int elapsedCount = NULL;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void SetMoveDir();
	void SetObState();
	void SetEnemyTankState();
	void AutoMove();

	void SetMoveDir();
	void SetObState();
	void SetEnemyTankState();
	void AutoMove();

	inline void SetETHP(int etHP) { this->etHP = etHP; }
	inline void SeteTankState(eTankState state) { this->tanckState = state; }
	inline void SetElapsedCount(int elapsedCount) { this->elapsedCount = elapsedCount; }
	inline int GetElapsedCount() { return this->elapsedCount; }
	inline eTankState GetTankState() { return this->tanckState; }

	EnemyTank();
	~EnemyTank();
};

