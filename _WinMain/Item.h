#pragma once

#include "GameObject.h"

class Image;
class Item : public GameObject
{
protected:
	int selectItem = NULL;				//æ∆¿Ã≈€ º±≈√

	Image* mpImgHelmet = nullptr;		//«Ô∏‰
	Image* mpImgWatch = nullptr;		//Ω√∞Ë
	Image* mpImgShovel = nullptr;		//ª
	Image* mpImgStar = nullptr;			//∫∞
	Image* mpImgGrenade = nullptr;		//ºˆ∑˘≈∫
	Image* mpImgTank = nullptr;			//≈ ≈©

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

