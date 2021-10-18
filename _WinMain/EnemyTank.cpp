#include "EnemyTank.h"
#include "Image.h"

HRESULT EnemyTank::Init()
{
	pos.x = rand() % 980 + 40;
	pos.y = 500;
	bodySize = 64;
	moveSpeed = 50.0f;

	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = pos.x + (bodySize / 2);
	shape.bottom = pos.y + (bodySize / 2);

	etHP = 1;
	etAttackValue = 1;

	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Enemy/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
	//mpEImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Enemy/Enemy.bmp");
	//if (mpEImg == nullptr)
	//{
	//	return E_FAIL;
	//}

	mChangeDir = rand() % 4;			//MoveDir 변수(0 : LEFT, 1 : RIGHT, 2 : UP, 3 : DOWN)
	SetMoveDir();						//MoveDir설정
	mChangeObState = rand() % 2;		//Obstate 변수(0 : IDLE, 1 : MOVE)
	SetObState();						//ObState설정

	mDelayCount = 0;
	bIsAlive = true;

	elapsedCount = 0;

	return S_OK;
}

void EnemyTank::Update()
{
	//cout << boolalpha << bIsAlive << endl;
	//cout << "mChangeDir : " << mChangeDir << endl;
	//cout << "mChangeObState : " << mChangeObState << endl;
	if (bIsAlive)
	{
		SetEnemyTankState();
		AutoMove();
	}

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
		//mpEImg->Render(hdc, pos.x, pos.y, mpEImg->GetCurrFrameX(), mpEImg->GetCurrFrameY());
	}
}

void EnemyTank::Release()
{
}

void EnemyTank::SetMoveDir()
{
	switch (mChangeDir) {
	case 0:
		moveDir = MoveDir::LEFT;
		//mpEImg->SetCurrFrameX(2);
		break;
	case 1:
		moveDir = MoveDir::RIGHT;
		//mpEImg->SetCurrFrameX(6);
		break;
	case 2:
		moveDir = MoveDir::UP;
		//mpEImg->SetCurrFrameX(0);
		break;
	case 3:
		moveDir = MoveDir::DOWN;
		//mpEImg->SetCurrFrameX(4);
		break;
	}
}

void EnemyTank::SetObState()
{
	switch (mChangeObState) {
	case 0:
		tanckState = eTankState::IDLE;
		break;
	case 1:
		tanckState = eTankState::MOVE;
		break;
	}
}

void EnemyTank::SetEnemyTankState()
{
	mDelayCount++;
	if (mDelayCount >= 300) {
		mChangeDir = rand() % 4;
		mChangeObState = rand() % 2;
		SetMoveDir();
		SetObState();
		mDelayCount = 0;
	}
}

void EnemyTank::AutoMove()
{
	if (tanckState == eTankState::MOVE)
	{
		if (moveDir == MoveDir::LEFT)
		{
			//mpEImg->SetCurrFrameX(2);
			pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		}
		if (moveDir == MoveDir::RIGHT)
		{
			//mpEImg->SetCurrFrameX(6);
			pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		}
		if (moveDir == MoveDir::UP)
		{
			//mpEImg->SetCurrFrameX(0);
			pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		}
		if (moveDir == MoveDir::DOWN)
		{
			//mpEImg->SetCurrFrameX(4);
			pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		}
	}
}

EnemyTank::EnemyTank()
{
}

EnemyTank::~EnemyTank()
{
}
