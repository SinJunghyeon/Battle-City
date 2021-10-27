#include "StageScene.h"
#include "Image.h"
#include "TitleScene.h"

HRESULT StageScene::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	background = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage.bmp", stageImageSizeX, stageImageSizeY);
	stageImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number.bmp", 40*5, 14*5, 5, 2);
	stageNum = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number.bmp");

	return S_OK;
}

void StageScene::Update()
{
	// 처음 배경 이미지 올라오게끔 하고 배경 이미지 중간에 왔을때 멈춤
	if (isAnimation)
	{
		downFrameY -= WIN_SIZE_Y/60;

		if (downFrameY == WIN_SIZE_Y / 2)
		{
			isAnimation = false;
		}
	}
	// 엔터 누를 시 애니메이션 재생(배경 이미지 올라감)
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		isAnimation = true;
	}
	// 배경 이미지 다 올라 갔을 때 씬 전환, 배경 이미지 아래로 위치 설정
	if (downFrameY <= WIN_SIZE_Y / 2 - WIN_SIZE_Y)
	{
		SceneManager::GetSingleton()->ChangeScene("battleTest2");
		downFrameY = WIN_SIZE_Y + WIN_SIZE_Y / 2;
	}

}

void StageScene::Render(HDC hdc)
{
	background->Render(hdc, WIN_SIZE_X / 2, downFrameY);

	if (downFrameY == WIN_SIZE_Y / 2)
	{
		stageImage->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		stageNum->Render(hdc, WIN_SIZE_X / 2 + stageImageSizeX*2/3, WIN_SIZE_Y / 2, stageN, 0);
	}
}

void StageScene::Release()
{
}
