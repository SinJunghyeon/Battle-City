#include "Enemy.h"
#include "Image.h"
#include "AmmoManager.h"

HRESULT Enemy::Init()
{
	elapsedCount = 0;
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
	moveSpeed = 50.0f;
	bodySize = 32;
	moveDir = MoveDir::DOWN;

	return S_OK;
}

void Enemy::Update()
{
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
			break;
		case MoveDir::LEFT:
			break;
		case MoveDir::UP:
			break;
		case MoveDir::DOWN:
			cout << elapsedCount << endl;
			pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
			elapsedCount++;
			if (elapsedCount >= 30)
			{
				img->SetCurrFrameX(img->GetCurrFrameX() + 1);
				if (img->GetCurrFrameX() >= 6)
				{
					img->SetCurrFrameX(4);
					elapsedCount = 0;
					//cout << "초기화 프레임 : " << img->GetCurrFrameX() << endl << endl;
				}
			}
			break;
		default:
			break;
	}

}
