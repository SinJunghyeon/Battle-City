#include "EnemyManager.h"
#include "MapConfig.h"

HRESULT EnemyManager::Init()
{
	enemyMaxCount = 18;
	enemyCurrCount = 3;

	enemySpawnDelay = 0;

	vecEnemys.resize(enemyMaxCount);

	for (int i = 0; i < enemyMaxCount; i++)
	{
		vecEnemys[i] = new Enemy;		
		vecEnemys[i]->Init();
		vecEnemys[i]->SetEnemyType((EnemyType)(rand() % 4));
	}
	vecEnemys[3]->SetHaveItem(true);
	vecEnemys[3]->Init();
	vecEnemys[3]->SetEnemyType((EnemyType)(rand() % 4));
	vecEnemys[10]->SetHaveItem(true);
	vecEnemys[10]->Init();
	vecEnemys[10]->SetEnemyType((EnemyType)(rand() % 4));
	vecEnemys[17]->SetHaveItem(true);
	vecEnemys[17]->Init();
	vecEnemys[17]->SetEnemyType((EnemyType)(rand() % 4));

	return S_OK;
}

void EnemyManager::Update()
{
	enemySpawnDelay++;
	if (enemySpawnDelay >= 500)
	{
		AddEnemy(enemySpawnPos[enemyCurrCount%3]);

		enemySpawnDelay = 0;
	}

	// Fix List
	for (int i = 0; i < enemyCurrCount; i++)
	{
		if (vecEnemys[i]->GetIsAilve() && vecEnemys[i]->GetTankState() != ecTankState::DIE)
		{
			for (int j = 0; j < enemyCurrCount; j++)
			{
				RECT tempCollisionRect;
				RECT enemyTankRect1 = vecEnemys[i]->GetShape();
				RECT enemtTankRect2 = vecEnemys[j]->GetShape();
				if (i == j)
					continue;				
				switch (vecEnemys[i]->GetMoveDir())
				{
				case MoveDir::RIGHT:
					if (IntersectRect(&tempCollisionRect, &enemyTankRect1, &enemtTankRect2))
					{
						vecEnemys[i]->SetIsCollision(true);
					}
					break;
				case MoveDir::LEFT:
					if (IntersectRect(&tempCollisionRect, &enemyTankRect1, &enemtTankRect2))
					{
						vecEnemys[i]->SetIsCollision(true);
					}
					break;
				case MoveDir::UP:
					if (IntersectRect(&tempCollisionRect, &enemyTankRect1, &enemtTankRect2))
					{
						vecEnemys[i]->SetIsCollision(true);
					}
					break;
				case MoveDir::DOWN:
					if (IntersectRect(&tempCollisionRect, &enemyTankRect1, &enemtTankRect2))
					{
						vecEnemys[i]->SetIsCollision(true);
					}
				}
			}
		}
	}

	for (int i = 0; i < enemyCurrCount; i++)
	{
		vecEnemys[i]->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (int i = 0; i < enemyCurrCount; i++)
	{
		vecEnemys[i]->Render(hdc);
	}
}

void EnemyManager::Release()
{
	for (itEnemys = vecEnemys.begin();
		itEnemys != vecEnemys.end(); itEnemys++)
	{
		SAFE_RELEASE((*itEnemys));
	}
	vecEnemys.clear();
}

void EnemyManager::AddEnemy(POINTFLOAT pos)
{
	enemyCurrCount++;
	if (enemyCurrCount > enemyMaxCount)
	{
		enemyCurrCount = enemyMaxCount;
	}
}

void EnemyManager::SetTileMapManager(TILE_INFO* tile)
{
	enemySpawnPos = GetSpawnPos(tile, ObjectType::ENEMY);

	for (int i = 0; i < enemyMaxCount; i++)
	{
		vecEnemys[i]->SetTileMap(tile);
		vecEnemys[i]->SetPos(enemySpawnPos[i % 3]);
	}
}

void EnemyManager::TankState(ecTankState state)
{
	for (int i = 0; i < enemyCurrCount; i++)
	{
		vecEnemys[i]->SetTankState(state);
	}
}

void EnemyManager::IsAlive(bool isAlive)
{
	for (int i = 0; i < enemyCurrCount; i++)
	{
		vecEnemys[i]->SetIsAlive(isAlive);
	}
}

