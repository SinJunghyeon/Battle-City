#include "PlayerTankScene.h"
#include "Tank.h"
#include "Image.h"

HRESULT PlayerTankScene::Init()
{
	mpPlayerTank = new Tank;
	mpPlayerTank->Init();

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
}

void PlayerTankScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);
	mpPlayerTank->Render(hdc);
}

void PlayerTankScene::Release()
{
	SAFE_RELEASE(mpPlayerTank);
}
