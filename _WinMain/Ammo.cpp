#include "Ammo.h"
#include "Tank.h"
#include "Image.h"
#include "CommonFunction.h"


HRESULT Ammo::Init()
{
	pos.x = 0.0f;
	pos.y = 0.0f;

	bodySize = 8;

	shape.left = 0;
	shape.top = 0;
	shape.right = 0;
	shape.bottom = 0;

	moveSpeed = 300.0f;

	moveDir = MoveDir::UP;

	mpPlayerTank = new Tank;

	isFire = false;

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile.bmp", bodySize, bodySize);
	img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Bullet/Missile.bmp");
	if (img == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}

void Ammo::Update()
{
	if (isFire)
	{
		//cout << "Ammo : " << moveDir << endl;
		if (moveDir == MoveDir::UP)
		{
			pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		}
		if (moveDir == MoveDir::DOWN)
		{
			pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		}
		if (moveDir == MoveDir::LEFT)
		{
			pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		}
		if (moveDir == MoveDir::RIGHT)
		{
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		}

		shape.left = pos.x - (bodySize / 2.0f);
		shape.top = pos.y - (bodySize / 2.0f);
		shape.right = pos.x + (bodySize / 2.0f);
		shape.bottom = pos.y + (bodySize / 2.0f);

		// È­¸éÀ» ¹þ¾î³µ´ÂÁö È®ÀÎ
		if (shape.left > WIN_SIZE_X || shape.right < 0 ||
			shape.top > WIN_SIZE_Y || shape.bottom < 0)
		{
			isFire = false;
		}
	}
}

void Ammo::SetIsFire(bool fire)
{
	this->isFire = fire;
}

void Ammo::Render(HDC hdc)
{
	if (isFire)
	{
		img->Render(hdc, pos.x, pos.y);
		//Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void Ammo::Release()
{
}

Ammo::Ammo()
{
}

Ammo::~Ammo()
{
}
