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
	Image* player1Text = nullptr;
	Image* textPTS = nullptr;
	Image* killEnemy = nullptr;
	Image* killEnemyArrow = nullptr;
	Image* scoreText = nullptr;

	POINT hiscoreTextPos;

	StageScene* stageTextSize;
	
	int killEnemyPosX = WIN_SIZE_X * 2 / 5;
	int killEnemyPosY[4] = { WIN_SIZE_Y * 4 / 10, WIN_SIZE_Y * 5 / 10 ,WIN_SIZE_Y * 6 / 10 ,WIN_SIZE_Y * 7 / 10 };
	
	int scoreTextPosX = killEnemyPosX - 100;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

