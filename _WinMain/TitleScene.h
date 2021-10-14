#pragma once
#include "Config.h"
#include "GameEntity.h"

class ButtonFunction;
class Button;
class Image;
class TitleScene : public GameEntity
{
private:
	Image* backGround;
	//Image* pSelectIcon = nullptr;

	LPARGUMENT_PTR arg;

	int countFrameY = WIN_SIZE_Y + WIN_SIZE_Y/2;
	//int selectIcon = 7;		//frameX°ª


public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};