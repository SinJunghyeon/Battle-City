#pragma once

#include "GameObject.h"

class Image;
class Item : public GameObject
{
protected:
	Image* mpImgHelmet = nullptr;		//Çï¸ä
	Image* mpImgWatch = nullptr;		//½Ã°è
	Image* mpImgShovel = nullptr;		//»ð
	Image* mpImgStar = nullptr;			//º°
	Image* mpImgGrenade = nullptr;		//¼ö·ùÅº
	Image* mpImgTank = nullptr;			//ÅÊÅ©

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

