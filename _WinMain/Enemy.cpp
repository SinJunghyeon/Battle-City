#include "Enemy.h"
#include "Image.h"
#include "AmmoManager.h"

HRESULT Enemy::Init()
{
	elapsedCount1 = 0;
	elapsedCount2 = 0;
	fireDelay = 100;
	fireTimer = 0;

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Enemy/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Enemy/Enemy.bmp");
	if (img == nullptr)
	{
		return E_FAIL;
	}

	ammoMgr = new AmmoManager;
	ammoMgr->Init();
	ammoMgr->SetOwner(this);

	pos.x = WIN_SIZE_X / 2.0f;
	pos.y = 100.0f;
	moveSpeed = 10.0f;
	bodySize = 32;
	moveDir = MoveDir::UP;

	return S_OK;
}

void Enemy::Update()
{
	elapsedCount1++;
	if (elapsedCount1 >= 100)
	{
		moveDir = (MoveDir)(rand() % 4);
		elapsedCount1 = 0;
	}
	AutoMove();

	fireTimer++;
	if (fireTimer >= fireDelay)
	{
		ammoMgr->Fire();
		fireTimer = 0;
		fireDelay = rand() % 100;
	}
	ammoMgr->Update();
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
			if (img->GetCurrFrameX() <= 5 || img->GetCurrFrameX() >= 8)
			{
				img->SetCurrFrameX(6);
			}
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
			elapsedCount2++;

			if (elapsedCount2 >= 5)
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
			if (elapsedCount2 >= 5)
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
			if (elapsedCount2 >= 5)
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
			if (elapsedCount2 >= 5)
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