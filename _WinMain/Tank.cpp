#include "Tank.h"
//#include "Item.h"

HRESULT Tank::Init()
{
	//탱크 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256, 8, 4, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Player/Player.bmp");
	if (img == nullptr)
	{
		return E_FAIL;
	}
	//무적상태 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Shield.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	effectImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Shield.bmp");
	if (effectImg == nullptr)
	{
		return E_FAIL;
	}

	pos.x = WIN_SIZE_X / 2.0f;
	pos.y = WIN_SIZE_Y - 100.0f;

	bodySize = 38;
	moveSpeed = 100.0f;

	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = pos.x + (bodySize / 2);
	shape.bottom = pos.y + (bodySize / 2);

	moveDir = MoveDir::UP;
	tanckState = ecTankState::IDLE;
	elapsedCount = 0;
	isAlive = true;

	ammoCount = 1;
	ammoPack = new Ammo[2];
	// 미사일 초기화
	for (int i = 0; i < 2; i++)
	{
		ammoPack[i].Init();
	}

	ptAttackValue = 1;	//공격력

	ptLife = 2;			//총 목숨

	ptScore = 0;		//점수

	////아이템
	//mpItem = new Item;
	//mpItem->Init();
	//itemShape.left = mpItem->GetShape().left;
	//itemShape.top = mpItem->GetShape().top;
	//itemShape.right = mpItem->GetShape().right;
	//itemShape.bottom = mpItem->GetShape().bottom;

	isInvincible = true;	//무적상태
	elapsedInvincible = 0;

	return S_OK;
}

void Tank::Update()
{
	//cout << "img->GetCurrFrameX() : " << img->GetCurrFrameX() << endl;
	//cout << "img->GetCurrFrameY() : " << img->GetCurrFrameY() << endl;
	cout << "elapsedInvincible : " << elapsedInvincible << endl;
	cout << "elapsedCount : " << elapsedCount << endl;
	//cout << "ptLife : " << ptLife << endl;
	cout << "effectImg->GetCurrFrameX() : " << effectImg->GetCurrFrameX() << endl;
	cout << boolalpha << "isInvincible : " << isInvincible << endl;
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

	elapsedInvincible++;
	if (elapsedInvincible >= 100)
	{
		isInvincible = false;
	}
	if (elapsedInvincible >= 106)
	{
		elapsedInvincible = 105;
	}

	//무적상태
	if (isInvincible)
	{
		elapsedCount++;
		if (elapsedCount >= 10)
		{
			effectImg->SetCurrFrameX(1);
		}
		if (elapsedCount >= 20)
		{
			effectImg->SetCurrFrameX(0);
			elapsedCount = 0;
		}
	}

	////아이템획득
	//CollisionItem();
	////아이템
	//mpItem->Update();
	//cout << mpItem->GetShape().left << endl;
	//cout << "Attack : " << ptAttackValue << endl;
}

void Tank::Render(HDC hdc)
{
	if (isAlive == false)	return;

	// 몸통
	//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

	// 미사일
	for (int i = 0; i < ammoCount; i++)
	{
		ammoPack[i].Render(hdc);
	}
	// 플레이어 이미지
	img->Render(hdc, pos.x + 12, pos.y + 10, img->GetCurrFrameX(), img->GetCurrFrameY(), 0.625f);
	//무적상태
	if (isInvincible)
	{
	effectImg->Render(hdc, pos.x - 27, pos.y - 17, effectImg->GetCurrFrameX(), effectImg->GetCurrFrameY(), 4);
	}


	////아이템
	//mpItem->Render(hdc);
	//Rectangle(hdc, itemShape.left, itemShape.top, itemShape.right, itemShape.bottom);
}

void Tank::Release()
{
	//SAFE_RELEASE(mpItem);
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
		img->SetCurrFrameX(0);
		Move(MoveDir::UP);
		tanckState = ecTankState::MOVE;
		//프레임 움직임
		elapsedCount++;
		if (elapsedCount >= 20)
		{
			img->SetCurrFrameX(1);
		}
		if (elapsedCount >= 40)
		{
			img->SetCurrFrameX(0);
			elapsedCount = 0;
		}
	}
	// 이동(하)
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		moveDir = MoveDir::DOWN;
		img->SetCurrFrameX(4);
		Move(MoveDir::DOWN);
		tanckState = ecTankState::MOVE;
		//프레임 움직임
		elapsedCount++;
		if (elapsedCount >= 20)
		{
			img->SetCurrFrameX(5);
		}
		if (elapsedCount >= 40)
		{
			img->SetCurrFrameX(4);
			elapsedCount = 0;
		}
	}
	// 이동(좌)
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		moveDir = MoveDir::LEFT;
		img->SetCurrFrameX(2);
		Move(MoveDir::LEFT);
		tanckState = ecTankState::MOVE;
		//프레임 움직임					
		elapsedCount++;					
		if (elapsedCount >= 20)			
		{
			img->SetCurrFrameX(3);
		}
		if (elapsedCount >= 40)			
		{
			img->SetCurrFrameX(2);
			elapsedCount = 0;
		}
	}
	// 이동(우)
	else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		moveDir = MoveDir::RIGHT;
		img->SetCurrFrameX(6);
		Move(MoveDir::RIGHT);
		tanckState = ecTankState::MOVE;
		//프레임 움직임
		elapsedCount++;
		if (elapsedCount >= 20)
		{
			img->SetCurrFrameX(7);
		}
		if (elapsedCount >= 40)
		{
			img->SetCurrFrameX(6);
			elapsedCount = 0;
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

//void Tank::CollisionItem()
//{
//	RECT a;
//	if (IntersectRect(&a, &shape, &itemShape))
//	{
//		//cout << "아이템 접촉! !" << endl;
//		if (mpItem->GetExistItem() == true)
//		{
//			//cout << "기능획득! !" << endl;
//			FunctionItem();
//		}
//		mpItem->SetExistItem(false);
//	}
//}

//void Tank::FunctionItem()
//{
//	//스타
//	if (mpItem->GetItemState() == ecFunctionItem::STAR)
//	{
//		//cout << "a" << endl;
//		img->SetCurrFrameY(img->GetCurrFrameY() + 1);
//		if (img->GetCurrFrameY() >= 3)
//		{
//			img->SetCurrFrameY(3);
//		}
//		if (img->GetCurrFrameY() >= 2)
//		{
//			//미사일 개수 조정
//			ammoCount = 2;
//			ammoPack = new Ammo[ammoCount];
//			//미사일 초기화
//			for (int i = 0; i < ammoCount; i++)
//			{
//				ammoPack[i].Init();
//			}
//			//공격력 증가
//			ptAttackValue = 2;		
//		}
//	}
//	//탱크
//	if (mpItem->GetItemState() == ecFunctionItem::TANK)
//	{
//		ptLife += 1;
//	}
//}

Tank::Tank()
{
}

Tank::~Tank()
{
}
