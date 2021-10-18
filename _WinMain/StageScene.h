#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "TitleScene.h"

class Image;
class StageScene : public GameEntity
{
private:
	Image* pStageImage = nullptr;
	Image* pStageNum = nullptr;
	Image* pBackground = nullptr;

	

	int stageImageSizeX = 37 * 5;
	int stageImageSizeY = 7 * 5;

	int downFrameY = WIN_SIZE_Y + WIN_SIZE_Y / 2;
	int upFrameY = WIN_SIZE_Y - WIN_SIZE_Y / 2;

	TitleScene* test;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

};

