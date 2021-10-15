#include "StageScene.h"
#include "Image.h"
#include "TitleScene.h"

HRESULT StageScene::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	pBackground = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage.bmp", stageImageSizeX, stageImageSizeY);
	pStageImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number.bmp", 40*5, 14*5, 5, 2);
	pStageNum = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number.bmp");

	return S_OK;
}

void StageScene::Update()
{
	if (downFrameY >= WIN_SIZE_Y / 2)
	{
		downFrameY -= 10;
	}
}

void StageScene::Render(HDC hdc)
{
	pBackground->Render(hdc, WIN_SIZE_X / 2, downFrameY);

	if (downFrameY <= WIN_SIZE_Y / 2 && upFrameY >= WIN_SIZE_Y / 2)
	{
		pStageImage->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		pStageNum->Render(hdc, WIN_SIZE_X / 2 + stageImageSizeX*2/3, WIN_SIZE_Y / 2, 0/*test->GetTextNum()*/, 0, 100);
	}
}

void StageScene::Release()
{
}
