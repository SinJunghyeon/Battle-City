#pragma once

#include "Config.h"
#include "GameEntity.h"

//폐기예정

class Image;
class Tank;
class Item;
class EnemyTank;
class PlayerTankScene : public GameEntity
{
private:
	// 배경 이미지
	Image* backGround;
	//플레이어 탱크
	Tank* mpPlayerTank;
	RECT playerTankRect;
	//적
	int enemyCount;
	EnemyTank* mpEnemy;
	Image* mpImgEnemy;
	//아이템
	Item* mpItem;
	RECT itemRect;


public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void EnemyTankState();
	void CollisionItem();
	void FunctionItem();
};

