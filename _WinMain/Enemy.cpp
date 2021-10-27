#include "Enemy.h"
#include "Image.h"

#include "Tank.h"

/*
	TO DO LIST
	 1. 방향 전환 자연스럽게 하기
	 2. 적 탱크 종류 추가
*/

HRESULT Enemy::Init()
{
	elapsedCount = 0;
	fireDelay = 100;
	fireTimer = 0;

	img = new Image;
	img->Init("Image/BattleCity/Enemy/Enemy.bmp", 320, 240, 8, 6, true, RGB(255, 0, 255));
	if (img == nullptr)
	{
		return E_FAIL;
	}

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Spawn_Effect.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255));
	spawnImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Spawn_Effect.bmp");
	if (spawnImg == nullptr)
	{
		return E_FAIL;
	}

	ammoMgr.Init();
	ammoMgr.SetOwner(this);

	pos.x = 0.0f;
	pos.y = 0.0f;
	moveSpeed = 0.0f;
	bodySize = 40;
	moveDir = MoveDir::DOWN;
	tankState = ecTankState::MOVE;

	shape.left = pos.x - bodySize / 2 + 1;
	shape.top = pos.y - bodySize / 2 + 1;
	shape.right = shape.left + bodySize - 5;
	shape.bottom = shape.top + bodySize - 5;

	return S_OK;
}

void Enemy::Update()
{
	RECT buffRect = shape;
	POINTFLOAT buffPos = pos;

	if (!isAlive && (tankState != ecTankState::DIE))
	{
		elapsedSpawn++;
		if (elapsedSpawn >= 5)
		{
			spawnImg->SetCurrFrameX(spawnImg->GetCurrFrameX() + 1);
			elapsedSpawn = 0;
			if (spawnImg->GetCurrFrameX() >= 4)
			{
				spawnImg->SetCurrFrameX(0);
				spawnCount++;
				if (spawnCount >= 3)
				{
					isAlive = true;
				}
			}
		}
	}

	if (!isAlive && (tankState == ecTankState::DIE))
	{
		shape.left = 0;
		shape.top = 0;
		shape.right = 0;
		shape.bottom = 0;
	}

	if (isAlive && tankState == ecTankState::MOVE)
	{
		Move(moveDir);
		MoveFrame();
		// 충돌 시 방향 전환
		if (isCollision)
		{
			switch (moveDir)
			{
			case MoveDir::RIGHT:
				moveSpeed = 0.0f;
				pos = buffPos;
				shape = buffRect;
				elapsedTurn++;
				if (elapsedTurn >= 30)
				{
					while (moveDir == MoveDir::RIGHT)
					{
						moveDir = (MoveDir)(rand() % 4);
					}

					if(tankType == EnemyType::SPEED)
					{
						moveSpeed = 100.0f;
					}
					else
					{
						moveSpeed = 50.0f;
					}

					isCollision = false;
					elapsedTurn = 0;
				}
				break;
			case MoveDir::LEFT:
				moveSpeed = 0.0f;
				pos = buffPos;
				shape = buffRect;
				elapsedTurn++;
				if (elapsedTurn >= 30)
				{
					pos.x += 1;
					while (moveDir == MoveDir::LEFT)
					{
						moveDir = (MoveDir)(rand() % 4);
					}
					if (tankType == EnemyType::SPEED)
					{
						moveSpeed = 100.0f;
					}
					else
					{
						moveSpeed = 50.0f;
					}
					isCollision = false;
					elapsedTurn = 0;
				}
				break;
			case MoveDir::UP:
				moveSpeed = 0.0f;
				pos = buffPos;
				shape = buffRect;
				elapsedTurn++;
				if (elapsedTurn >= 30)
				{
					pos.y += 1;
					while (moveDir == MoveDir::UP)
					{
						moveDir = (MoveDir)(rand() % 4);
					}
					if (tankType == EnemyType::SPEED)
					{
						moveSpeed = 100.0f;
					}
					else
					{
						moveSpeed = 50.0f;
					}
					isCollision = false;
					elapsedTurn = 0;
				}
				break;
			case MoveDir::DOWN:
				moveSpeed = 0.0f;
				pos = buffPos;
				shape = buffRect;
				elapsedTurn++;
				if (elapsedTurn >= 30)
				{
					pos.y -= 1;
					while (moveDir == MoveDir::DOWN)
					{
						moveDir = (MoveDir)(rand() % 4);
					}
					if (tankType == EnemyType::SPEED)
					{
						moveSpeed = 100.0f;
					}
					else
					{
						moveSpeed = 50.0f;
					}
					isCollision = false;
					elapsedTurn = 0;
				}
				break;
			default:
				break;
			}
			isCollision = false;
		}

		// moveSpeed가 0.1로 고정되는 오류 방지
		if (moveSpeed == 0.0f)
		{
			elapsedSpeed++;
			if (moveSpeed != 0.0f)
			{
				elapsedSpeed = 0;
			}

			if (elapsedSpeed >= 50)
			{
				//TankAbilitySetting();
			}
		}

		fireTimer++;
		if (fireTimer >= fireDelay)
		{
			ammoMgr.Fire();
			fireTimer = 0;
			if (tankType == EnemyType::RPD)
			{
				fireDelay = 0;
			}
			else
			{
				fireDelay = rand() % 100;
			}
		}
		ammoMgr.Update();

		shape.left = pos.x - bodySize / 2 + 1;
		shape.top = pos.y - bodySize / 2 + 1;
		shape.right = shape.left + bodySize - 5;
		shape.bottom = shape.top + bodySize - 5;
	}
}

void Enemy::Render(HDC hdc)
{
	// 임시 충돌 박스
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

	if (!isAlive && (tankState != ecTankState::DIE))	//죽어있을 때 -> 스폰 이미지를 부르고 -> 살게끔
	{
		spawnImg->Render(hdc, pos.x, pos.y, spawnImg->GetCurrFrameX(), spawnImg->GetCurrFrameY());
	}

	if (isAlive)
	{
		img->Render(hdc, pos.x, pos.y, img->GetCurrFrameX(), img->GetCurrFrameY());

		ammoMgr.Render(hdc);
	}
}

void Enemy::Release()
{
	//SAFE_RELEASE(ammoMgr);
	ammoMgr.Release();
	SAFE_RELEASE(img);

}

// 움직이는 모양
void Enemy::MoveFrame()
{
	switch (moveDir)
	{
	case MoveDir::RIGHT:
		if (img->GetCurrFrameX() <= 5 || img->GetCurrFrameX() >= 8)
		{
			img->SetCurrFrameX(6);
		}
		elapsedCount++;

		if (elapsedCount >= 2)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 8)
			{
				img->SetCurrFrameX(6);
				elapsedCount = 0;
			}
		}
		break;
	case MoveDir::LEFT:
		if (img->GetCurrFrameX() <= 1 || img->GetCurrFrameX() >= 4)
		{
			img->SetCurrFrameX(2);
		}
		elapsedCount++;
		if (elapsedCount >= 2)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 4)
			{
				img->SetCurrFrameX(2);
				elapsedCount = 0;
			}
		}
		break;
	case MoveDir::UP:
		if (img->GetCurrFrameX() <= -1 || img->GetCurrFrameX() >= 2)
		{
			img->SetCurrFrameX(0);
		}
		elapsedCount++;
		if (elapsedCount >= 2)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 2)
			{
				img->SetCurrFrameX(0);
				elapsedCount = 0;
			}
		}
		break;
	case MoveDir::DOWN:
		if (img->GetCurrFrameX() <= 3 || img->GetCurrFrameX() >= 6)
		{
			img->SetCurrFrameX(4);
		}
		elapsedCount++;
		if (elapsedCount >= 2)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 6)
			{
				img->SetCurrFrameX(4);
				elapsedCount = 0;
			}
		}
		break;
	default:
		break;
	}
}

void Enemy::Move(MoveDir dir)
{
	POINTFLOAT buffPos;  // 현재 좌표를 백업하기 위한 버퍼
	buffPos.x = pos.x;
	buffPos.y = pos.y;
	RECT buffRect;
	buffRect = shape;

	switch (dir)
	{
	case MoveDir::LEFT: pos.x -= (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()); break;
	case MoveDir::RIGHT: pos.x += (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()); break;
	case MoveDir::UP: pos.y -= (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()); break;
	case MoveDir::DOWN: pos.y += (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()); break;
	}

	for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
	{
		//if (isCollision == false)
		//{
			if (IntersectRect(&tempRect, &shape, &tile[i].rc))
			{
				if ((tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::STEEL) || (tile[i].terrain == Terrain::HQ_WALL) || (tile[i].terrain == Terrain::HQ_STEEL))
				{
					pos = buffPos;
					shape = buffRect;
					isCollision = true;
				}
			}
		//}
	}
}

void Enemy::SetEnemyType(EnemyType type)
{
	tankType = type;

	switch (tankType)
	{
	case EnemyType::NORMAL:
		moveSpeed = 50.0f;
		img->SetCurrFrameY(0);
		break;
	case EnemyType::SPEED:
		moveSpeed = 100.0f;
		img->SetCurrFrameY(1);
		break;
	case EnemyType::RPD:
		moveSpeed = 50.0f;
		img->SetCurrFrameY(2);
		fireDelay = 50;
		ammoMgr.SetAmmoSpeed(600.0f);
		break;
	case EnemyType::SUPER:
		moveSpeed = 50.0f;
		img->SetCurrFrameY(3);
		hp = 3;
		break;
	default:
		break;
	}
}
