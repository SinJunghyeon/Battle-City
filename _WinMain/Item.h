#pragma once

#include "GameObject.h"

enum class ecFunctionItem { NOTHING, HELMET, WATCH, SHOVEL, STAR, GRENADE, TANK };

class Image;
class Item : public GameObject
{
protected:
	int selectItem = NULL;				//¾ÆÀÌÅÛ ¼±ÅÃ
	bool bIsFunction = false;			//¾ÆÀÌÅÛ ±â´É

	Image* mpImgHelmet = nullptr;		//Çï¸ä
	Image* mpImgWatch = nullptr;		//½Ã°è
	Image* mpImgShovel = nullptr;		//»ð
	Image* mpImgStar = nullptr;			//º°
	Image* mpImgGrenade = nullptr;		//¼ö·ùÅº
	Image* mpImgTank = nullptr;			//ÅÊÅ©

	ecFunctionItem functionItem = ecFunctionItem::NOTHING;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void FunctionItem();

	inline void SetFunctionItem(bool bIsFunction) { this->bIsFunction = bIsFunction; }
};

