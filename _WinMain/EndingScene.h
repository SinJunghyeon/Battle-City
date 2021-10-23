#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "StageScene.h"
#include "BattleTest2.h"

class Image;
class EndingScene : public GameEntity
{
private:
	Image* hiscoreText;
	Image* stageText;
	Image* stageNumText;
	Image* player1Text;
	Image* textPTS;
	Image* killEnemy;
	Image* killEnemyArrow;
	Image* textTotal;
	Image* totalKillText;
	Image* scoreText[4];

	BattleTest2 destroyEnemy;

	StageScene stageScene;
	
	POINT hiscoreTextPos;

	int killEnemyPosX = WIN_SIZE_X * 4 / 5;
	int killEnemyPosY[4] = { WIN_SIZE_Y * 4 / 10, WIN_SIZE_Y * 5 / 10 ,WIN_SIZE_Y * 6 / 10 ,WIN_SIZE_Y * 7 / 10 };
	
	int scoreTextPosX = killEnemyPosX - 100;

	int killEnemyNumber[4] = { destroyEnemy.GetDestroyedEnemy(0),destroyEnemy.GetDestroyedEnemy(1),destroyEnemy.GetDestroyedEnemy(2),destroyEnemy.GetDestroyedEnemy(3) };
	int killEnemyNumber5[4];
	int killEnemyNumber10[4];
	int totalKillEnemy = killEnemyNumber[0]+ killEnemyNumber[1]+ killEnemyNumber[2]+ killEnemyNumber[3];
	int totalKillEnemy5 = 0;
	int totalKillEnemy10 = 0;

	int countKillEnemy[4] = { 0,0,0,0 };
	int arrNum = 0;

	bool isAnimetion = true;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

