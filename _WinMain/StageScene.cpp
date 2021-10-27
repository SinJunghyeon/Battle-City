#include "StageScene.h"
#include "Image.h"
#include "TitleScene.h"

HRESULT StageScene::Init()
{
	startTopImagePosY = -(WIN_SIZE_Y / 2);
	startBottomImagePosY = WIN_SIZE_Y + WIN_SIZE_Y / 2;

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
	// ó�� ��� �̹��� �ö���Բ� �ϰ� ��� �̹��� �߰��� ������ ����
	if(isAnimation)
	{
		startBottomImagePosY -= 10;
		startTopImagePosY += 10;
	
		if (startBottomImagePosY == WIN_SIZE_Y*3/4 && startTopImagePosY== WIN_SIZE_Y*1/4)
		{
			isAnimation = false;
		}
	}
	// ���� ���� �� �ִϸ��̼� ���(��� �̹��� �ö�)
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		isAnimation = true;
	}
	// ��� �̹��� �� �ö� ���� �� �� ��ȯ
	if (startBottomImagePosY <= WIN_SIZE_Y / 2 - WIN_SIZE_Y)
	{
		SceneManager::GetSingleton()->ChangeScene("battleS");
	}

}

void StageScene::Render(HDC hdc)
{
	background->Render(hdc, WIN_SIZE_X / 2, startBottomImagePosY);
	background2->Render(hdc, WIN_SIZE_X / 2, startTopImagePosY);

	if (!isAnimation)
	{
		stageImage->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		stageNum->Render(hdc, WIN_SIZE_X / 2 + stageImageSizeX*2/3, WIN_SIZE_Y/2 - 13, stageN, 0, 5.0f);
	}
}

void StageScene::Release()
{
	
}
