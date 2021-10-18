#include "StageScene.h"
#include "Image.h"
#include "TitleScene.h"

HRESULT StageScene::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	background = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");

//	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
//	background2 = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage.bmp", stageImageSizeX, stageImageSizeY);
	stageImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number.bmp", 40*5, 14*5, 5, 2);
	stageNum = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number.bmp");


	return S_OK;
}

void StageScene::Update()
{
	if (isAnimation)
	{
		downFrameY -= WIN_SIZE_Y/60;

		if (downFrameY == WIN_SIZE_Y / 2)
		{
			isAnimation = false;
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		isAnimation = true;
	}

	if (downFrameY <= WIN_SIZE_Y / 2 - WIN_SIZE_Y)
	{
		SceneManager::GetSingleton()->ChangeScene("endingS");
		//upFrameY += 10;
	}

}

void StageScene::Render(HDC hdc)
{
	background->Render(hdc, WIN_SIZE_X / 2, downFrameY);
	//Background2->Render(hdc, WIN_SIZE_X / 2, upFrameY);

	if (downFrameY == WIN_SIZE_Y / 2)
	{
		stageImage->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		stageNum->Render(hdc, WIN_SIZE_X / 2 + stageImageSizeX*2/3, WIN_SIZE_Y / 2, stageN, 0);
	}
}

void StageScene::Release()
{
}
