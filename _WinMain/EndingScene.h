#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "BattleScene.h"

class StageScene;
class Image;
class EndingScene : public GameEntity
{
private:
	Image* highScoreText = nullptr;
	POINT hiscoreTextPos;

	Image* stageText = nullptr;
	Image* stageNumber = nullptr;

	Image* player1Text = nullptr;

	Image* textPTS = nullptr;
	Image* enemyTankImage = nullptr;
	Image* arrowImage = nullptr;

	Image* scoreNumber[4] = {};


	BattleScene destroyEnemy;

	StageScene stageScene;

	int enemyTankImagePosX = WIN_SIZE_X * 4 / 5;
	int enemyTankImagePosY[4] = { WIN_SIZE_Y * 4 / 10, WIN_SIZE_Y * 5 / 10 ,WIN_SIZE_Y * 6 / 10 ,WIN_SIZE_Y * 7 / 10 };
	
	int scoreNumberPosX = enemyTankImagePosX - 100;

	//싱글톤으로 정보 가져오는 매니저를 하나 제작
	// destroyedEnemy[0] *1, killEnemyNumber[1]*2, killEnemyNumber[2]*3, killEnemyNumber[3]*4 해야함
	int destroyedEnemy[4] = { 10,15,20,3 };

	Image* textTotal = nullptr;
	Image* enemyTotalText = nullptr;
	int enemyTotal = destroyedEnemy[0]+ destroyedEnemy[1]+ destroyedEnemy[2]+ destroyedEnemy[3];

	int enemyCount[4] = { 0, 0, 0, 0 };
	int enemyCountArrNum = 0;

	bool isAnimation = true;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	virtual ~EndingScene() = default;
};

