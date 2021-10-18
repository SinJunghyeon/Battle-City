#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"
#include "Image.h"

enum class ecTankState { IDLE, MOVE, FIRE, DAMAGED, DIE };

class Item;
class Tank : public GameObject
{
private:
	int ammoCount;
	Ammo* ammoPack;
	//bool bObtainItem = false;

	ecTankState tanckState = ecTankState::IDLE;
	int elapsedCount = NULL;
	bool isAlive = true;

	////¾ÆÀÌÅÛ
	//Item* mpItem = nullptr;
	//RECT itemShape;
	
	float ptAttackValue = NULL;		//공격력
	int ptLife = NULL;				//플레이어 목숨
	int ptScore = NULL;				//플레이어 탱크 점수

	Image* effectImg;
	bool isInvincible = true;		//무적상태
	int elapsedInvincible = NULL;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void Fire();
	void ProcessInputKey();

	void Move(MoveDir dir);
	//void CollisionItem();
	//void FunctionItem();

	inline void SetIsAlive(bool alive) { this->isAlive = alive; }
	inline void SetAmmoCount(int ammoCount) { this->ammoCount = ammoCount; } 

	inline void SetptAttackValue(float ptAttackValue) { this->ptAttackValue = ptAttackValue; }
	inline float GetptAttackValue() { return ptAttackValue; }

	inline void SetptLife(int ptLife) { this->ptLife = ptLife; }
	inline int GetptLife() { return ptLife; }

	inline void SetImgFrameY(int frameY) { this->img->SetCurrFrameY(frameY); }
	inline int GetImgFrameY() { return img->GetCurrFrameY(); }

	inline void SetElapsedInvincible(int elapsedInvincible) { this->elapsedInvincible = elapsedInvincible; }

	inline void SetInvincible(bool isInvincible) { this->isInvincible = isInvincible; }

	Tank();
	~Tank();
};

