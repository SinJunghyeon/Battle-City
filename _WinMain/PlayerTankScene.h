#pragma once

#include "Config.h"
#include "GameEntity.h"

class Image;
class Tank;
class Item;
class PlayerTankScene : public GameEntity
{
private:
	// ��� �̹���
	Image* backGround;
	//�÷��̾� ��ũ
	Tank* mpPlayerTank;
	//������
	//Item* mpItem;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

