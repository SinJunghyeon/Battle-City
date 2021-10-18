#include "StageScene.h"
#include "Image.h"
#include "TitleScene.h"

HRESULT StageScene::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	Background = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");

//	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
//	Background2 = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage.bmp", stageImageSizeX, stageImageSizeY);
	StageImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number.bmp", 40*5, 14*5, 5, 2);
	StageNum = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number.bmp");

	return S_OK;
}

void StageScene::Update()
{
	if (downFrameY >= WIN_SIZE_Y / 2)
	{
		downFrameY -= 10;
		upFrameY += 10;
	}
}

void StageScene::Render(HDC hdc)
{
	Background->Render(hdc, WIN_SIZE_X / 2, downFrameY);
	//Background2->Render(hdc, WIN_SIZE_X / 2, upFrameY);

	if (downFrameY <= WIN_SIZE_Y / 2 && upFrameY >= WIN_SIZE_Y / 2)
	{
		StageImage->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		StageNum->Render(hdc, WIN_SIZE_X / 2 + stageImageSizeX*2/3, WIN_SIZE_Y / 2, 0/*test->GetTextNum()*/, 0, 100);
	}
}

void StageScene::Release()
{
}
