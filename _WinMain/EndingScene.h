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
	Image* textTotal = nullptr;
	Image* totalKillText = nullptr;
	Image* scoreText[4];


	StageScene* stageTextSize = nullptr;;
	
	POINT hiscoreTextPos;

	int killEnemyPosX = WIN_SIZE_X * 4 / 5;
	int killEnemyPosY[4] = { WIN_SIZE_Y * 4 / 10, WIN_SIZE_Y * 5 / 10 ,WIN_SIZE_Y * 6 / 10 ,WIN_SIZE_Y * 7 / 10 };
	
	int scoreTextPosX = killEnemyPosX - 100;

	int killEnemyNumber[4] = { 5,20,7,1 };	//나중에 에너미 죽인거 가져오기
	int killEnemyNumber5[4];
	int killEnemyNumber10[4];
	int totalKillEnemy = 0;

	int test;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

