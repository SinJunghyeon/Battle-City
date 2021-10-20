#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"
#include "Image.h"

class Item;
class Tank : public GameObject
{
public:
	int ammoCount;
	Ammo* ammoPack;

	ecTankState tanckState = ecTankState::IDLE;
	int elapsedCount = NULL;
	bool isAlive = false;

	float ptAttackValue = NULL;		//공격력
	int ptLife = NULL;				//플레이어 목숨
	int ptScore = NULL;				//플레이어 탱크 점수

	Image* effectImg = nullptr;
	bool isInvincible = true;		//무적상태
	int elapsedInvincible = NULL;

	// 충돌처리용 RECT
	RECT tempRect;

	Image* spawnImg = nullptr;
	int elapsedSpawn = NULL;
	int spawnCount = NULL;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void Fire();
	void ProcessInputKey();

	void Move(MoveDir dir);

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
	// 타일 정보를 받아오는 함수
	inline void SetTileMap(TILE_INFO* tile) { this->tile = tile; }

	Tank();
	~Tank();
};

