#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
	enemyMaxCount = 6;
	enemyCurrCount = 3;

	enemySpawnDelay = 0;

	vecEnemys.resize(enemyMaxCount);

	for (int i = 0; i < enemyMaxCount; i++)
	{
		enemySpawnPos[i] = { 120.0f + (i % 3) * 242.0f, 120.0f };
		vecEnemys[i] = new Enemy;
		vecEnemys[i]->Init();
		vecEnemys[i]->SetPos(enemySpawnPos[i]);
	}

	return S_OK;
}

void EnemyManager::Update()
{
	for (int i = 0; i < enemyCurrCount; i++)
	{
		vecEnemys[i]->SetMoveSpeed(20.0f);
	}

	// 적 새로 리스폰
	enemySpawnDelay++;
	if (enemySpawnDelay >= 500)
	{
		AddEnemy(enemySpawnPos[enemyCurrCount]);

		enemySpawnDelay = 0;
	}

	// 적끼리 충돌확인
	for (int i = 0; i < enemyCurrCount; i++)
	{
		for (int j = 0; j < enemyCurrCount; j++)
		{
			if (i == j)
				continue;
			switch (vecEnemys[i]->GetMoveDir())
			{
			case MoveDir::RIGHT:
				if ((vecEnemys[i]->GetShape().right >= vecEnemys[j]->GetShape().left) &&
					(abs(vecEnemys[i]->GetPos().y - vecEnemys[j]->GetPos().y) <= 32))
				{
					vecEnemys[i]->SetMoveDir((MoveDir)(rand() % 4));
				}
				break;
			case MoveDir::LEFT:
				if ((vecEnemys[i]->GetShape().left <= vecEnemys[j]->GetShape().right) &&
					(abs(vecEnemys[i]->GetPos().y - vecEnemys[j]->GetPos().y) <= 32))
				{
					vecEnemys[i]->SetMoveDir((MoveDir)(rand() % 4));
				}
				break;
			case MoveDir::UP:
				if ((vecEnemys[i]->GetShape().top <= vecEnemys[j]->GetShape().bottom) &&
					(abs(vecEnemys[i]->GetPos().x - vecEnemys[j]->GetPos().x) <= 32))
				{
					vecEnemys[i]->SetMoveDir((MoveDir)(rand() % 4));
				}
				break;
			case MoveDir::DOWN:
				if ((vecEnemys[i]->GetShape().bottom >= vecEnemys[j]->GetShape().top) &&
					(abs(vecEnemys[i]->GetPos().x - vecEnemys[j]->GetPos().x) <= 32))
				{
					vecEnemys[i]->SetMoveDir((MoveDir)(rand() % 4));
				}
				break;
			default:
				break;
			}
		}
	}

	for (int i = 0; i < enemyCurrCount; i++)
	{
		vecEnemys[i]->Update();
	}
	
	/*for (itEnemys = vecEnemys.begin();
		itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Update();
	}*/
}

void EnemyManager::Render(HDC hdc)
{
	/*for (itEnemys = vecEnemys.begin();
		itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Render(hdc);
	}*/

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
		enemyCurrCount = enemyMaxCount;
}

void EnemyManager::SetTileMapManager(TILE_INFO* tile)
{
	for (int i = 0; i < enemyMaxCount; i++)
	{
		vecEnemys[i]->SetTileMap(tile);
	}
}
