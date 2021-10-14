#include "PlayerTankScene.h"
#include "Image.h"
#include "Tank.h"
#include "Item.h"
#include "EnemyTank.h"

HRESULT PlayerTankScene::Init()
{
	//탱크
	mpPlayerTank = new Tank;
	mpPlayerTank->Init();
	//아이템
	//mpItem = new Item;
	//mpItem->Init();
	//적
	mpEnemy = new EnemyTank;
	mpEnemy->Init();

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
	mpPlayerTank->Update();
	//mpItem->Update();
}

void PlayerTankScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);
	mpPlayerTank->Render(hdc);
	//mpItem->Render(hdc);
	mpEnemy->Render(hdc);
}

void PlayerTankScene::Release()
{
	SAFE_RELEASE(mpPlayerTank);
	//SAFE_RELEASE(mpItem);
	SAFE_RELEASE(mpEnemy);
}
