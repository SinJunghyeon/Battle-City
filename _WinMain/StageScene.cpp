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
	// ó�� ��� �̹��� �ö���Բ� �ϰ� ��� �̹��� �߰��� ������ ����
	if (isAnimation)
	{
		downFrameY -= WIN_SIZE_Y/60;

		if (downFrameY == WIN_SIZE_Y / 2)
		{
			isAnimation = false;
		}
	}
	// ���� ���� �� �ִϸ��̼� ���(��� �̹��� �ö�)
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		isAnimation = true;
	}
	// ��� �̹��� �� �ö� ���� �� �� ��ȯ, ��� �̹��� �Ʒ��� ��ġ ����
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
