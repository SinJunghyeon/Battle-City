#include "PlayerTankScene.h"
#include "Image.h"
#include "Tank.h"
#include "Item.h"
#include "EnemyTank.h"

//예상치 않은 결과 : enemyCount 수만큼 elapsdecount가 늘어남.
HRESULT PlayerTankScene::Init()
{
	//탱크
	mpPlayerTank = new Tank;
	mpPlayerTank->Init();
	//아이템
	//mpItem = new Item;
	//mpItem->Init();
	//적
	//mpEnemy->Init();
	enemyCount = 17;
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
	for (int i = 0; i < enemyCount; i++)
	{
		cout << mpEnemy[i].GetElapsedCount() << endl;
	}
	mpPlayerTank->Update();
	//mpItem->Update();
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
}

void PlayerTankScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);
	mpPlayerTank->Render(hdc);
	//mpItem->Render(hdc);
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
	//SAFE_RELEASE(mpItem);
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
