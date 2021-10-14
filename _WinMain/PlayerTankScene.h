#pragma once

#include "Config.h"
#include "GameEntity.h"

class Image;
class Tank;
class Item;
class PlayerTankScene : public GameEntity
{
private:
	// 배경 이미지
	Image* backGround;
	//플레이어 탱크
	Tank* mpPlayerTank;
	//아이템
	//Item* mpItem;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

