#include "TitleScene.h"
#include "Config.h"
#include "Image.h"

HRESULT TitleScene::Init()
{	
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Title.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Title.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256, 8, 4, true, RGB(255, 0, 255));
	selectIcon = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Player/Player.bmp");

	return S_OK;
}

void TitleScene::Update()
{

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		iconPosNum++;
		iconPosY[iconPosNum];
		if (iconPosNum > 1)
		{
			iconPosNum = 0;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
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
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
		{
			countFrameY = WIN_SIZE_Y / 2;
		}
	}
	
	switch (iconFrameX)
	{
	case 7:
		iconFrameX = 6;
		break;
	case 6:
		iconFrameX = 7;
		break;
	}

	if (countFrameY <= WIN_SIZE_Y / 2)
	{
		bIsSceneIcon = true;
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
		{
			SceneManager::GetSingleton()->ChangeScene("stageS");
			iconPosNum = 0;
		}
	}

	elapsedCount++;
}

void TitleScene::Render(HDC hdc)
{
	backGround->Render(hdc, WIN_SIZE_X / 2, countFrameY);


	if (bIsSceneIcon)
	{
		timeLate = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);	//탱크 프레임 조정
		selectIcon->Render(hdc, WIN_SIZE_X / 4, iconPosY[iconPosNum], iconFrameX, 0);
	}
}

void TitleScene::Release()
{
	SAFE_DELETE(arg);
	timeLate = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);	//프레임 원상복구
}
