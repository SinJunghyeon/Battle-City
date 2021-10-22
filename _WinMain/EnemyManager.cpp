#include "EnemyManager.h"
#include "MapConfig.h"

HRESULT EnemyManager::Init()
{
	enemyMaxCount = 6;
	enemyCurrCount = 3;

	enemySpawnDelay = 0;

	vecEnemys.resize(enemyMaxCount);

	for (int i = 0; i < enemyMaxCount; i++)
	{
		vecEnemys[i] = new Enemy;
		vecEnemys[i]->Init();
	}

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
				if (i == j)
					continue;
				switch (vecEnemys[i]->GetMoveDir())
				{
				case MoveDir::RIGHT:
					if (//(vecEnemys[i]->GetShape().right >= vecEnemys[j]->GetShape().left) &&
						(abs(vecEnemys[i]->GetPos().y - vecEnemys[j]->GetPos().y) <= 40)
						&& abs(vecEnemys[i]->GetPos().x - vecEnemys[j]->GetPos().x) <= 40)
					{
						vecEnemys[i]->SetIsCollision(true);
						vecEnemys[j]->SetIsCollision(true);
						cout << "case right collision : " << i << "," << vecEnemys[i]->GetIsCollision() << endl;
					}
					break;
				case MoveDir::LEFT:
					if (//(vecEnemys[i]->GetShape().left <= vecEnemys[j]->GetShape().right) &&
						(abs(vecEnemys[i]->GetPos().y - vecEnemys[j]->GetPos().y) <= 40)
						&& abs(vecEnemys[i]->GetPos().x - vecEnemys[j]->GetPos().x) <= 40)
					{

						vecEnemys[i]->SetIsCollision(true);
						vecEnemys[j]->SetIsCollision(true);
						cout << "case left collision : " << i << "," << vecEnemys[i]->GetIsCollision() << endl;
					}
					break;
				case MoveDir::UP:
					if (//(vecEnemys[i]->GetShape().top <= vecEnemys[j]->GetShape().bottom) &&
						(abs(vecEnemys[i]->GetPos().x - vecEnemys[j]->GetPos().x) <= 40)
						&& abs(vecEnemys[i]->GetPos().y - vecEnemys[j]->GetPos().y) <= 40)
					{
						vecEnemys[i]->SetIsCollision(true);
						vecEnemys[j]->SetIsCollision(true);
						cout << "case up collision : " << i << "," << vecEnemys[i]->GetIsCollision() << endl;
					}
					break;
				case MoveDir::DOWN:
					if (//(vecEnemys[i]->GetShape().bottom >= vecEnemys[j]->GetShape().top) &&
						(abs(vecEnemys[i]->GetPos().x - vecEnemys[j]->GetPos().x) <= 40)
						&& abs(vecEnemys[i]->GetPos().y - vecEnemys[j]->GetPos().y) <= 40)
					{
						vecEnemys[i]->SetIsCollision(true);
						vecEnemys[j]->SetIsCollision(true);
						cout << "case down collision : " << i << "," << vecEnemys[i]->GetIsCollision() << endl;
						cout << "tank" << i << " bottom : " << vecEnemys[i]->GetShape().bottom << endl;
						cout << "tank" << j << " top : " << vecEnemys[j]->GetShape().top << endl;
						cout << "(abs(vecEnemys[i]->GetPos().x - vecEnemys[j]->GetPos().x) : " << (abs(vecEnemys[i]->GetPos().x - vecEnemys[j]->GetPos().x)) << endl;
					}
					break;
				default:
					break;
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
	//for (int i = 0; i < GetSpawnPos(tile, ObjectType::ENEMY).size(); i++)
	//{
		enemySpawnPos = GetSpawnPos(tile, ObjectType::ENEMY);
	//}
	
	for (int i = 0; i < enemyMaxCount; i++)
	{
		//enemySpawnPos[i] = GetSpawnPos(tile, ObjectType::ENEMY);
		vecEnemys[i]->SetTileMap(tile);
		vecEnemys[i]->SetPos(enemySpawnPos[i % 3]);
		//vecEnemys[i]->SetPos(enemySpawnPos[i]);
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

