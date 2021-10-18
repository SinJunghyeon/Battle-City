#pragma once
#include "Config.h"
#include "GameEntity.h"

class Image;
class StageScene : public GameEntity
{
private:
	Image* stageImage = nullptr;
	Image* stageNum = nullptr;
	Image* background = nullptr;
	//Image* background2 = nullptr;
		

	int stageImageSizeX = 37 * 5;
	int stageImageSizeY = 7 * 5;

	int downFrameY = WIN_SIZE_Y + WIN_SIZE_Y / 2;
	int upFrameY = WIN_SIZE_Y - WIN_SIZE_Y / 2;

	bool isAnimation = true;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	int stageN = 1;
};

