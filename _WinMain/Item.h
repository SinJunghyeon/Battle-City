#pragma once

#include "GameObject.h"

class Image;
class Item : public GameObject
{
protected:
	Image* mpImgHelmet = nullptr;		//���
	Image* mpImgWatch = nullptr;		//�ð�
	Image* mpImgShovel = nullptr;		//��
	Image* mpImgStar = nullptr;			//��
	Image* mpImgGrenade = nullptr;		//����ź
	Image* mpImgTank = nullptr;			//��ũ

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

