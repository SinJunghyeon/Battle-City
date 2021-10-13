#include "Tank.h"
#include "Image.h"


HRESULT Tank::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256, 8, 4, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Player/Player.bmp");
	if (img == nullptr)
	{
		return E_FAIL;
	}
	pos.x = WIN_SIZE_X / 2.0f;
	pos.y = WIN_SIZE_Y - 100.0f;

	bodySize = 64;
	moveSpeed = 50.0f;

	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = pos.x + (bodySize / 2);
	shape.bottom = pos.y + (bodySize / 2);

	moveDir = MoveDir::UP;
	tanckState = ecTankState::IDLE;
	elapsedCount = 0;
	isAlive = true;

	ammoCount = 300;
	ammoPack = new Ammo[ammoCount];
	// 미사일 초기화
	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Init();
	}

	return S_OK;
}

void Tank::Update()
{
	if (isAlive == false)	return;

	//cout << "Tank : " << moveDir << endl;

	// 위치에 따른 모양값 갱신
	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = shape.left + bodySize;
	shape.bottom = shape.top + bodySize;

	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Update();
	}

	ProcessInputKey();	// 입력키
	//cout << "img->GetCurrFrameX() : " << img->GetCurrFrameX() << endl;
}

void Tank::Render(HDC hdc)
{
	if (isAlive == false)	return;

	// 몸통
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

	// 미사일
	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Render(hdc);
	}
	// 플레이어 이미지
	img->Render(hdc, pos.x, pos.y, img->GetCurrFrameX(), img->GetCurrFrameY());
}

void Tank::Release()
{
	delete[] ammoPack;
}

void Tank::Fire()
{
	for (int i = 0; i < ammoCount; i++)
	{
		// 전체 미사일을 순회하면서 발사 됐는지 안됐는지 판단
		if (ammoPack[i].GetIsFire()/* && ammoPack[i].GetIsAlive()*/)
			continue;
		ammoPack[i].SetMoveDir(moveDir);
		ammoPack[i].SetPos(pos);		// 미사일 위치 변경
		ammoPack[i].SetIsFire(true);	// 미사일 상태 변경

		break;
	}
}

void Tank::ProcessInputKey()
{
	// 공격키
	if (Singleton<KeyManager>::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		Fire();
	}
	// 이동(상)
	if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		moveDir = MoveDir::UP;
		Move(MoveDir::UP);
		tanckState = ecTankState::MOVE;
		//프레임 움직임
		elapsedCount++;
		if (elapsedCount >= 10)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 2)
			{
				img->SetCurrFrameX(0);
			}
		}
	}
	// 이동(하)
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		moveDir = MoveDir::DOWN;
		Move(MoveDir::DOWN);
		tanckState = ecTankState::MOVE;
		//프레임 움직임
		elapsedCount++;
		if (elapsedCount >= 10)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 6)
			{
				img->SetCurrFrameX(4);
			}
		}
	}
	// 이동(좌)
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		moveDir = MoveDir::LEFT;
		Move(MoveDir::LEFT);
		tanckState = ecTankState::MOVE;
		//프레임 움직임
		elapsedCount++;
		if (elapsedCount >= 10)
		{
			img->SetCurrFrameX(img->GetCurrFrameX() + 1);
			if (img->GetCurrFrameX() >= 4)
			{
				img->SetCurrFrameX(2);
			}
		}
	}
	// 이동(우)
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		moveDir = MoveDir::RIGHT;
		Move(MoveDir::RIGHT);
		tanckState = ecTankState::MOVE;
		//프레임 움직임
		img->SetCurrFrameX(img->GetCurrFrameX() + 1);
		if (img->GetCurrFrameX() >= 8)
		{
			img->SetCurrFrameX(6);
		}
	}
	// 키 뺐을때(상)
	if (Singleton<KeyManager>::GetSingleton()->IsOnceKeyUp(VK_UP))
	{
		moveDir = MoveDir::UP;
		tanckState = ecTankState::IDLE;
	}
	// 키 뺐을때(하)
	if (Singleton<KeyManager>::GetSingleton()->IsOnceKeyUp(VK_DOWN))
	{
		moveDir = MoveDir::DOWN;
		tanckState = ecTankState::IDLE;
	}
	// 키 뺐을때(좌)
	if (Singleton<KeyManager>::GetSingleton()->IsOnceKeyUp(VK_LEFT))
	{
		moveDir = MoveDir::LEFT;
		tanckState = ecTankState::IDLE;
	}
	// 키 뺐을때(우)
	if (Singleton<KeyManager>::GetSingleton()->IsOnceKeyUp(VK_RIGHT)) 
	{
		moveDir = MoveDir::RIGHT;
		tanckState = ecTankState::IDLE;
	}
}

void Tank::Move(MoveDir dir)
{
	switch (dir)
	{
	case MoveDir::LEFT: pos.x -= (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()); break;
	case MoveDir::RIGHT: pos.x += (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()); break;
	case MoveDir::UP: pos.y -= (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()); break;
	case MoveDir::DOWN: pos.y += (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime()); break;
	}
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
