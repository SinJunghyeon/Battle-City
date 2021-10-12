#pragma once

#include "Config.h"
#include "GameEntity.h"

class Tank;
class Image;
class PlayerTankScene : public GameEntity
{
private:
	Tank* mpPlayerTank;
	// ��� �̹���
	Image* backGround;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

