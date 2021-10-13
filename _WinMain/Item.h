#pragma once

#include "GameObject.h"

enum class ecFunctionItem { NOTHING, HELMET, WATCH, SHOVEL, STAR, GRENADE, TANK };

class Image;
class Item : public GameObject
{
protected:
	int selectItem = NULL;				//������ ����
	bool bIsFunction = false;			//������ ���

	Image* mpImgHelmet = nullptr;		//���
	Image* mpImgWatch = nullptr;		//�ð�
	Image* mpImgShovel = nullptr;		//��
	Image* mpImgStar = nullptr;			//��
	Image* mpImgGrenade = nullptr;		//����ź
	Image* mpImgTank = nullptr;			//��ũ

	ecFunctionItem functionItem = ecFunctionItem::NOTHING;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void FunctionItem();

	inline void SetFunctionItem(bool bIsFunction) { this->bIsFunction = bIsFunction; }
};

