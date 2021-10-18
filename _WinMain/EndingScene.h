#pragma once
#include "Config.h"
#include "GameEntity.h"

class StageScene;
class Image;
class EndingScene : public GameEntity
{
private:
	Image* hiscoreText = nullptr;
	Image* stageText = nullptr;
	Image* stageNumText = nullptr;

	POINT hiscoreTextPos;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

