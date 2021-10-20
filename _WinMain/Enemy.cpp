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

	ammoMgr = new AmmoManager;
	ammoMgr->Init();
	ammoMgr->SetOwner(this);

	pos.x = WIN_SIZE_X / 2.0f;
	pos.y = 100.0f;
	moveSpeed = 0.0f;
	bodySize = 40;
	moveDir = MoveDir::RIGHT;

	shape.left = pos.x - bodySize / 2 + 1;
	shape.top = pos.y - bodySize / 2 + 1;
	shape.right = shape.left + bodySize - 5;
	shape.bottom = shape.top + bodySize - 5;

	return S_OK;
}

void Enemy::Update()
{
	AutoMove();
	if (Collider())
	{
		moveDir = (MoveDir)(rand() % 4);
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

void Enemy::Render(HDC hdc)
{
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

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
		if (shape.right >= WIN_SIZE_X)
		{
			return true;
		}
		break;
	case MoveDir::LEFT:
		if (shape.left <= 0)
		{
			return true;
		}
		break;
	case MoveDir::UP:
		if (shape.top <= 0)
		{
			return true;
		}
		break;
	case MoveDir::DOWN:
		if (shape.bottom >= WIN_SIZE_Y)
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}
