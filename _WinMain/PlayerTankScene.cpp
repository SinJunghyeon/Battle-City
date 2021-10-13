#include "PlayerTankScene.h"
#include "Image.h"
#include "Tank.h"
#include "Item.h"

HRESULT PlayerTankScene::Init()
{
	//��ũ
	mpPlayerTank = new Tank;
	mpPlayerTank->Init();
	//������
	mpItem = new Item;
	mpItem->Init();

	// ��� �̹���
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");
	if (backGround == nullptr)
	{
		cout << "Image/BattleCity/mapImage.bmp ���� �ε忡 �����ߴ�." << endl;

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
	mpItem->Render(hdc);
}

void PlayerTankScene::Release()
{
	SAFE_RELEASE(mpPlayerTank);
	SAFE_RELEASE(mpItem);
}
