#include "TitleScene.h"
#include "Config.h"
#include "Image.h"

HRESULT TitleScene::Init()
{	
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Title.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Title.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256, 8, 4, true, RGB(255, 0, 255));
	pSelectIcon = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Player/Player.bmp");

	return S_OK;
}

void TitleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		SceneManager::GetSingleton()->ChangeScene("ÀüÅõ¾À", "·Îµù¾À");
		return;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
	{
		iconPosNum++;
		iconPosY[iconPosNum];
		if (iconPosNum > 1)
		{
			iconPosNum = 0;
		}
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
	{
		iconPosNum--;
		iconPosY[iconPosNum];
		if (iconPosNum < 0)
		{
			iconPosNum = 1;
		}
	}


	if (countFrameY >= WIN_SIZE_Y / 2)
	{
		countFrameY -= 10;
	}
	
	switch (selectIcon)
	{
	case 7:
		selectIcon = 6;
		break;
	case 6:
		selectIcon = 7;
		break;
	}

	if (countFrameY <= WIN_SIZE_Y / 2)
	{
		bIsSceneIcon = true;
	}

	elapsedCount++;
}

void TitleScene::Render(HDC hdc)
{
	backGround->Render(hdc, WIN_SIZE_X / 2, countFrameY);


	if (bIsSceneIcon)
	{
		pSelectIcon->Render(hdc, WIN_SIZE_X / 4, iconPosY[iconPosNum], selectIcon, 0);
	}
}

void TitleScene::Release()
{
	SAFE_DELETE(arg);
}
