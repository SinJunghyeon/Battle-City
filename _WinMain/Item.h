#pragma once

#include "GameObject.h"

enum class ecFunctionItem { NOTHING, HELMET, WATCH, SHOVEL, STAR, GRENADE, TANK };

class Image;
class Item : public GameObject
{
protected:
	int selectItem = NULL;				//������ ����
	bool bExistItem = true;				//������ ���翩��

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

	inline void SetExistItem(bool bExistItem) { this->bExistItem = bExistItem; }
	inline bool GetExistItem() { return bExistItem; }

	inline ecFunctionItem GetItemState() { return functionItem;	}
};

