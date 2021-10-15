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
	img->Init("Image/BattleCity/Enemy/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
	if (img == nullptr)
	{
		return E_FAIL;
	}

	ammoMgr = new AmmoManager;
	ammoMgr->Init();
	ammoMgr->SetOwner(this);

	pos.x = WIN_SIZE_X / 2.0f;
	pos.y = 100.0f;
	moveSpeed = 30.0f;
	bodySize = 32;
	moveDir = MoveDir::RIGHT;

	shape.left = pos.x - bodySize / 2;
	shape.top = pos.y - bodySize / 2;
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	return S_OK;
}

void Enemy::Update()
{
	// 임시 충돌 체크

	AutoMove();
	//Collider();

	fireTimer++;
	if (fireTimer >= fireDelay)
	{
		ammoMgr->Fire();
		fireTimer = 0;
		fireDelay = rand() % 100;
	}
	ammoMgr->Update();

	shape.left = pos.x - bodySize / 2;
	shape.top = pos.y - bodySize / 2;
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;
}

void Enemy::Render(HDC hdc)
{
	img->Render(hdc, pos.x, pos.y, img->GetCurrFrameX(), img->GetCurrFrameY());

	ammoMgr->Render(hdc);
}

void Enemy::Release()
{
	SAFE_RELEASE(ammoMgr);
}

void Enemy::AutoMove()
{
	switch (moveDir)
	{
	case MoveDir::RIGHT:
		if (shape.right >= WIN_SIZE_X)
		{
			moveDir = (MoveDir)(rand() % 4);
			return;
		}
		if (img->GetCurrFrameX() <= 5 || img->GetCurrFrameX() >= 8)
		{
			img->SetCurrFrameX(6);
		}
		pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
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
		pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
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
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
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
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
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

bool Enemy::Collider()
{
	switch (moveDir)
	{
	case MoveDir::RIGHT:
		break;
	case MoveDir::LEFT:
		break;
	case MoveDir::UP:
		break;
	case MoveDir::DOWN:
		break;
	default:
		break;
	}

	return false;
}
