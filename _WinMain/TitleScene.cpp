#include "TitleScene.h"
#include "Config.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Title.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Title.bmp");
	
	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256, 8, 4, true, RGB(255, 0, 255));
	//pSelectIcon = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Player/Player.bmp");

	return S_OK;
}

void TitleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		SceneManager::GetSingleton()->ChangeScene("ÀüÅõ¾À", "·Îµù¾À");
		return;
	}
	if (countFrameY >= WIN_SIZE_Y / 2)
	{
		countFrameY-=2;
	}

	/*if (selectIcon < 8)
	{
		selectIcon++;
	}
	else
	{
		selectIcon = 7;
	}*/
}

void TitleScene::Render(HDC hdc)
{
	if (backGround)
	{
		backGround->Render(hdc, WIN_SIZE_X / 2, countFrameY);
	}
	/*if (pSelectIcon)
	{
		pSelectIcon->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, selectIcon, 1);
	}*/
}

void TitleScene::Release()
{
	SAFE_DELETE(arg);
}
