#include "PlayerTankScene.h"
#include "Image.h"
#include "Tank.h"
#include "Item.h"
#include "EnemyTank.h"

//예상치 않은 결과 : enemyCount 수만큼 elapsdecount가 늘어남.
HRESULT PlayerTankScene::Init()
{
	srand(time(NULL));
	//탱크
	mpPlayerTank = new Tank;
	mpPlayerTank->Init();
	playerTankRect = mpPlayerTank->GetShape();
	//playerTankRect.left = mpPlayerTank->GetShape().left;
	//playerTankRect.top = mpPlayerTank->GetShape().top;
	//playerTankRect.right = mpPlayerTank->GetShape().right;
	//playerTankRect.bottom = mpPlayerTank->GetShape().bottom;
	//아이템
	mpItem = new Item;
	mpItem->Init();
	itemRect = mpItem->GetShape();
	//itemRect.left = mpItem->GetShape().left;
	//itemRect.top = mpItem->GetShape().top;
	//itemRect.right = mpItem->GetShape().right;
	//itemRect.bottom = mpItem->GetShape().bottom;
	//적
	//mpEnemy->Init();
	enemyCount = 2;
	mpEnemy = new EnemyTank[enemyCount];
	mpImgEnemy = new Image[enemyCount];
	for (int i = 0; i < enemyCount; i++)
	{
		mpEnemy[i].Init();
		mpImgEnemy[i].Init("Image/BattleCity/Enemy/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
	}
	//EnemyTankState();

	// 배경 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");
	if (backGround == nullptr)
	{
		cout << "Image/BattleCity/mapImage.bmp 파일 로드에 실패했다." << endl;

		return E_FAIL;
	}


	return S_OK;
}

void PlayerTankScene::Update()
{
	//for (int i = 0; i < enemyCount; i++)
	//{
	//	cout << i << "의 탱크 : " << mpEnemy[i].GetElapsedCount() << endl;
	//}
	mpPlayerTank->Update();
	mpItem->Update();
	//mpEnemy->Update();
	for (int i = 0; i < enemyCount; i++)
	{
		mpEnemy[i].Update();		
		//if (mpEnemy[i].GetShape().left > WIN_SIZE_X || mpEnemy[i].GetShape().right < 0 || 
		//	mpEnemy[i].GetShape().top > WIN_SIZE_Y || mpEnemy[i].GetShape().bottom < 0)
		//{
		//	mpEnemy[i].SeteTankState(IDLE);
		//}
		EnemyTankState();
	}
	//플레이어
	playerTankRect = mpPlayerTank->GetShape();
	//playerTankRect.left = mpPlayerTank->GetShape().left;
	//playerTankRect.top = mpPlayerTank->GetShape().top;
	//playerTankRect.right = mpPlayerTank->GetShape().right;
	//playerTankRect.bottom = mpPlayerTank->GetShape().bottom;

	//아이템
	//cout << boolalpha << "mpItem->GetExistItem() : " << mpItem->GetExistItem() << endl;
	if (mpItem->GetExistItem() == true)
	{
		itemRect = mpItem->GetShape();
	}
	//itemRect.left = mpItem->GetShape().left;
	//itemRect.top = mpItem->GetShape().top;
	//itemRect.right = mpItem->GetShape().right;
	//itemRect.bottom = mpItem->GetShape().bottom;
	//플레이어 아이템 접촉
	CollisionItem();
}

void PlayerTankScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);
	mpPlayerTank->Render(hdc);
	//Rectangle(hdc, playerTankRect.left, playerTankRect.top, playerTankRect.right, playerTankRect.bottom);
	mpItem->Render(hdc);
	//Rectangle(hdc, itemRect.left, itemRect.top, itemRect.right, itemRect.bottom);
	//mpEnemy->Render(hdc);
	for (int i = 0; i < enemyCount; i++)
	{
		mpEnemy[i].Render(hdc);
		mpImgEnemy[i].Render(hdc, mpEnemy[i].GetPos().x, mpEnemy[i].GetPos().y, mpImgEnemy[i].GetCurrFrameX(), mpImgEnemy[i].GetCurrFrameY());
	}
}

void PlayerTankScene::Release()
{
	SAFE_RELEASE(mpPlayerTank);
	SAFE_RELEASE(mpItem);
	//SAFE_RELEASE(mpEnemy);
	delete[] mpEnemy;
}

void PlayerTankScene::EnemyTankState()
{
	for (int i = 0; i < enemyCount; i++)
	{
		if (mpEnemy[i].GetMoveDir() == MoveDir::LEFT)
		{
			mpImgEnemy[i].SetCurrFrameX(2);
			if (mpEnemy[i].GetTankState() == eTankState::MOVE)
			{
				mpEnemy[i].SetElapsedCount(mpEnemy[i].GetElapsedCount() + 1);
				if (mpEnemy[i].GetElapsedCount() >= 20)
				{
					mpImgEnemy[i].SetCurrFrameX(3);
				}
				if (mpEnemy[i].GetElapsedCount() >= 40)
				{
					mpImgEnemy[i].SetCurrFrameX(2);
					mpEnemy[i].SetElapsedCount(0);
				}
			}
		}
		if (mpEnemy[i].GetMoveDir() == MoveDir::RIGHT)
		{
			mpImgEnemy[i].SetCurrFrameX(6);
			if (mpEnemy[i].GetTankState() == eTankState::MOVE)
			{
				mpEnemy[i].SetElapsedCount(mpEnemy[i].GetElapsedCount() + 1);
				if (mpEnemy[i].GetElapsedCount() >= 20)
				{
					mpImgEnemy[i].SetCurrFrameX(7);
				}
				if (mpEnemy[i].GetElapsedCount() >= 40)
				{
					mpImgEnemy[i].SetCurrFrameX(6);
					mpEnemy[i].SetElapsedCount(0);
				}
			}
		}
		if (mpEnemy[i].GetMoveDir() == MoveDir::UP)
		{
			mpImgEnemy[i].SetCurrFrameX(0);
			if (mpEnemy[i].GetTankState() == eTankState::MOVE)
			{
				mpEnemy[i].SetElapsedCount(mpEnemy[i].GetElapsedCount() + 1);
				if (mpEnemy[i].GetElapsedCount() >= 20)
				{
					mpImgEnemy[i].SetCurrFrameX(1);
				}
				if (mpEnemy[i].GetElapsedCount() >= 40)
				{
					mpImgEnemy[i].SetCurrFrameX(0);
					mpEnemy[i].SetElapsedCount(0);
				}
			}
		}
		if (mpEnemy[i].GetMoveDir() == MoveDir::DOWN)
		{
			mpImgEnemy[i].SetCurrFrameX(4);
			if (mpEnemy[i].GetTankState() == eTankState::MOVE)
			{
				mpEnemy[i].SetElapsedCount(mpEnemy[i].GetElapsedCount() + 1);
				if (mpEnemy[i].GetElapsedCount() >= 20)
				{
					mpImgEnemy[i].SetCurrFrameX(5);
				}
				if (mpEnemy[i].GetElapsedCount() >= 40)
				{
					mpImgEnemy[i].SetCurrFrameX(4);
					mpEnemy[i].SetElapsedCount(0);
				}
			}
		}
	}
  
}

void PlayerTankScene::CollisionItem()
{
	RECT a;
	if (IntersectRect(&a, &playerTankRect, &itemRect))
	{
		//cout << "아이템 접촉! !" << endl;
		if (mpItem->GetExistItem() == true)
		{
			//cout << "기능획득! !" << endl;
			FunctionItem();
		}
		mpItem->SetExistItem(false);
	}
}

void PlayerTankScene::FunctionItem()
{
	//헬멧
	if (mpItem->GetItemState() == ecFunctionItem::HELMET)
	{
		mpPlayerTank->SetInvincible(true);
		mpPlayerTank->SetElapsedInvincible(0);
	}
	//시계
	if (mpItem->GetItemState() == ecFunctionItem::WATCH)
	{

	}
	//삽
	if (mpItem->GetItemState() == ecFunctionItem::SHOVEL)
	{

	}
	//별
	if (mpItem->GetItemState() == ecFunctionItem::STAR)
	{
		mpPlayerTank->SetImgFrameY(mpPlayerTank->GetImgFrameY() + 2);
		if (mpPlayerTank->GetImgFrameY() >= 3)
		{
			mpPlayerTank->SetImgFrameY(3);
		}
		if (mpPlayerTank->GetImgFrameY() >= 2)
		{
			mpPlayerTank->SetAmmoCount(2);
		}
	}
	//수류탄
	if (mpItem->GetItemState() == ecFunctionItem::GRENADE)
	{

	}
	//탱크
	if (mpItem->GetItemState() == ecFunctionItem::TANK)
	{
		mpPlayerTank->SetptLife(mpPlayerTank->GetptLife() + 1);
	}
}
