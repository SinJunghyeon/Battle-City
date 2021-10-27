#include "StageScene.h"
#include "Image.h"
#include "TitleScene.h"

HRESULT StageScene::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	background = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");
	background2 = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage.bmp", stageImageSizeX, stageImageSizeY);
	stageImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage.bmp");

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number.bmp", 40, 14, 5, 2, true, RGB(255, 0, 255));
	stageNum = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number.bmp");

	return S_OK;
}

void StageScene::Update()
{
	// 처음 배경 이미지 올라오게끔 하고 배경 이미지 중간에 왔을때 멈춤
	if(isAnimation)
	{
		startBottomPosY -= 10;
		startTopPosY += 10;
	
		if (startBottomPosY == WIN_SIZE_Y*3/4 && startTopPosY== WIN_SIZE_Y*1/4)
		{
			isAnimation = false;
		}
	}
	// 엔터 누를 시 애니메이션 재생(배경 이미지 올라감)
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		isAnimation = true;
	}
	// 배경 이미지 다 올라 갔을 때 씬 전환
	if (startBottomPosY <= WIN_SIZE_Y / 2 - WIN_SIZE_Y)
	{
		SceneManager::GetSingleton()->ChangeScene("battleS");
	}

}

void StageScene::Render(HDC hdc)
{
	background->Render(hdc, WIN_SIZE_X / 2, startBottomPosY);
	background2->Render(hdc, WIN_SIZE_X / 2, startTopPosY);

	if (!isAnimation)
	{
		stageImage->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		stageNum->Render(hdc, WIN_SIZE_X / 2 + stageImageSizeX*2/3, WIN_SIZE_Y/2 - 13, stageN, 0, 5.0f);
	}
}

void StageScene::Release()
{
	//배경 이미지 초기 위치로 설정
	startTopPosY = -(WIN_SIZE_Y / 2);
	startBottomPosY = WIN_SIZE_Y + WIN_SIZE_Y / 2;
}
