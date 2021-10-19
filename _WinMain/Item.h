#pragma once

#include "GameObject.h"

enum class ecFunctionItem { NOTHING, HELMET, WATCH, SHOVEL, STAR, GRENADE, TANK };

class Image;
class Item : public GameObject
{
protected:
	int selectItem = NULL;				//아이템 선택
	bool bExistItem = true;				//아이템 존재여부

	Image* mpImgHelmet = nullptr;		//헬멧
	Image* mpImgWatch = nullptr;		//시계
	Image* mpImgShovel = nullptr;		//삽
	Image* mpImgStar = nullptr;			//별
	Image* mpImgGrenade = nullptr;		//수류탄
	Image* mpImgTank = nullptr;			//탱크

	ecFunctionItem functionItem = ecFunctionItem::NOTHING;

	int tempElapsedCount = 0;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	inline void SetExistItem(bool bExistItem) { this->bExistItem = bExistItem; }
	inline bool GetExistItem() { return bExistItem; }

	inline ecFunctionItem GetItemState() { return functionItem;	}
};

