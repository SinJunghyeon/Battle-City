#include "EnemyTank.h"
#include "Image.h"

HRESULT EnemyTank::Init()
{
	pos.x = WIN_SIZE_X / 2;
	pos.y = 50;
	bodySize = 64;
	moveSpeed = 50.0f;

	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = pos.x + (bodySize / 2);
	shape.bottom = pos.y + (bodySize / 2);

	etHP = 1;
	etAttackValue = 1;

	bIsAlive = true;

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Enemy/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
	mpEImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Enemy/Enemy.bmp");
	if (mpEImg == nullptr)
	{
		return E_FAIL;
	}


	return S_OK;
}

void EnemyTank::Update()
{
	if (etHP <= 0)
	{
		bIsAlive = false;
	}
}

void EnemyTank::Render(HDC hdc)
{
	if (bIsAlive)
	{
		// 몸통
		//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
		// 플레이어 이미지
		mpEImg->Render(hdc, pos.x, pos.y, 4, mpEImg->GetCurrFrameY());
	}
}

void EnemyTank::Release()
{
}

EnemyTank::EnemyTank()
{
}

EnemyTank::~EnemyTank()
{
}
