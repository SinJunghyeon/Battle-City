#pragma once
#include "Config.h"
#include "GameEntity.h"

class Enemy;
class EnemyManager : public GameEntity
{
private:
	vector<Enemy*> vecEnemys;
	vector<Enemy*>::iterator itEnemys;

	int enemyMaxCount;

	POINTFLOAT enemySpawnPos[3];

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void AddEnemy(POINTFLOAT pos);
};

