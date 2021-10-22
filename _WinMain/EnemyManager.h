#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"
#include "Enemy.h"

class EnemyManager : public GameEntity
{
private:
	vector<Enemy*> vecEnemys;
	vector<Enemy*>::iterator itEnemys;

	int enemyMaxCount;
	int enemyCurrCount;
	int enemySpawnDelay;

	vector<POINTFLOAT> enemySpawnPos;
	//POINTFLOAT enemySpawnPos[6];

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void AddEnemy(POINTFLOAT pos);

	void SetTileMapManager(TILE_INFO* tile);
	void TankState(ecTankState state);
	void IsAlive(bool isAlive);

	vector<Enemy*> GetEnemies() { return this->vecEnemys; }

	int GetEnemyMaxCount() { return this->enemyMaxCount; }
};

