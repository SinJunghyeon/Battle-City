#include "Enemy.h"
#include "Image.h"
#include "AmmoManager.h"

HRESULT Enemy::Init()
{
	elapsedCount1 = 0;
	elapsedCount2 = 0;
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

	ammoMgr = new AmmoManager;
	ammoMgr->Init();
	ammoMgr->SetOwner(this);

	pos.x = 0.0f;
	pos.y = 0.0f;
	moveSpeed = 0.0f;
	bodySize = 40;
	moveDir = MoveDir::DOWN;

	shape.left = pos.x - bodySize / 2 + 1;
	shape.top = pos.y - bodySize / 2 + 1;
	shape.right = shape.left + bodySize - 5;
	shape.bottom = shape.top + bodySize - 5;

	tankState = ecTankState::MOVE;

	return S_OK;
}

void Enemy::Update()
{
	if (!isAlive)
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
					isAlive = !isAlive;
				}
			}
		}
	}
	if (isAlive && tankState == ecTankState::MOVE)
	{
		Move(moveDir);
		MoveFrame();
		if (isCollision)
		{
			moveDir = (MoveDir)(rand() % 4);
			isCollision = false;

		}

		fireTimer++;
		if (fireTimer >= fireDelay)
		{
			ammoMgr->Fire();
			fireTimer = 0;
			fireDelay = rand() % 100;
		}
		ammoMgr->Update();

		shape.left = pos.x - bodySize / 2 + 1;
		shape.top = pos.y - bodySize / 2 + 1;
		shape.right = shape.left + bodySize - 5;
		shape.bottom = shape.top + bodySize - 5;
	}
}

void Enemy::Render(HDC hdc)
{
	// 임시 충돌
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

	if (!isAlive)	//죽어있을 때 -> 스폰 이미지를 부르고 -> 살게끔
	{
		spawnImg->Render(hdc, pos.x, pos.y, spawnImg->GetCurrFrameX(), spawnImg->GetCurrFrameY());
	}

	if (isAlive)
	{
		img->Render(hdc, pos.x, pos.y, img->GetCurrFrameX(), img->GetCurrFrameY());

		ammoMgr->Render(hdc);
	}

	// 화면 밖으로 나가는 것 체크
	switch (moveDir)
	{
	case MoveDir::RIGHT:
		if (shape.right >= 605)
		{
			isCollision = true;
		}
		break;
	case MoveDir::LEFT:
		if (shape.left <= 120)
		{
			isCollision = true;
		}
		break;
	case MoveDir::UP:
		if (shape.top <= 120)
		{
			isCollision = true;
		}
		break;
	case MoveDir::DOWN:
		if (shape.bottom >= 605)
		{
			isCollision = true;
		}
		break;
	default:
		break;
	}
}

void Enemy::Release()
{
	SAFE_RELEASE(ammoMgr);
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
		elapsedCount2++;

		if (elapsedCount2 >= 2)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 8)
			{
				img->SetCurrFrameX(6);
				elapsedCount2 = 0;
			}
		}
		break;
	case MoveDir::LEFT:
		if (img->GetCurrFrameX() <= 1 || img->GetCurrFrameX() >= 4)
		{
			img->SetCurrFrameX(2);
		}
		elapsedCount2++;
		if (elapsedCount2 >= 2)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 4)
			{
				img->SetCurrFrameX(2);
				elapsedCount2 = 0;
			}
		}
		break;
	case MoveDir::UP:
		if (img->GetCurrFrameX() <= -1 || img->GetCurrFrameX() >= 2)
		{
			img->SetCurrFrameX(0);
		}
		elapsedCount2++;
		if (elapsedCount2 >= 2)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 2)
			{
				img->SetCurrFrameX(0);
				elapsedCount2 = 0;
			}
		}
		break;
	case MoveDir::DOWN:
		if (img->GetCurrFrameX() <= 3 || img->GetCurrFrameX() >= 6)
		{
			img->SetCurrFrameX(4);
		}
		elapsedCount2++;
		if (elapsedCount2 >= 2)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 6)
			{
				img->SetCurrFrameX(4);
				elapsedCount2 = 0;
			}
		}
		break;
	default:
		break;
	}
}

// 게임 화면 밖 나가지 않게
//bool Enemy::Collider()
//{
//	switch (moveDir)
//	{
//	case MoveDir::RIGHT:
//		if (shape.right >= 605)
//		{
//			return true;
//		}
//		break;
//	case MoveDir::LEFT:
//		if (shape.left <= 120)
//		{
//			return true;
//		}
//		break;
//	case MoveDir::UP:
//		if (shape.top <= 120)
//		{
//			return true;
//		}
//		break;
//	case MoveDir::DOWN:
//		if (shape.bottom >= 605)
//		{
//			return true;
//		}
//		break;
//	default:
//		break;
//	}
//
//	return false;
//}

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


	// 위치에 따른 모양값 갱신
	shape.left = pos.x - (bodySize / 2) - 2;
	shape.top = pos.y - (bodySize / 2) - 3;
	shape.right = pos.x + (bodySize / 2);
	shape.bottom = pos.y + (bodySize / 2) - 3;

	for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
	{
		if (IntersectRect(&tempRect, &shape, &tile[i].rc))
		{
			if ((tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::STEEL) || (tile[i].terrain == Terrain::HQ_WALL) || (tile[i].terrain == Terrain::HQ_STEEL))
			{
				pos = buffPos;
				shape = buffRect;
			}
		}
	}
}