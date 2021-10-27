#include "TitleScene.h"
#include "Config.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	iconPosArr = 0;

	// ��� �̹���
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Title.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Title.bmp");
	// ��ũ �̹���
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256, 8, 4, true, RGB(255, 0, 255));
	selectIcon = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Player/Player.bmp");

	return S_OK;
}

void TitleScene::Update()
{
	// �Ʒ��� ������ �� ������ �Ʒ��� �̵�
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		iconPosArr++;
		iconPosY[iconPosArr];
		if (iconPosArr > 1)
		{
			iconPosArr = 0;
		}
	}
	// ���� ������ �� ������ ���� �̵�
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		iconPosArr--;
		iconPosY[iconPosArr];
		if (iconPosArr < 0)
		{
			iconPosArr = 1;
		}
	}
	// Ÿ��Ʋ �ִϸ��̼�
	if (countFrameY >= WIN_SIZE_Y / 2)	
	{
		countFrameY -= 10;
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
		{
			countFrameY = WIN_SIZE_Y / 2;
		}
	}
	// ����� �߾ӿ� ���� �� ���� Ű ������ ���� ������ �̵�
	if (countFrameY <= WIN_SIZE_Y / 2)
	{
		bIsSceneIcon = true;
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
		{
			SceneManager::GetSingleton()->ChangeScene("stageS");
			iconPosArr = 0;
		}
	}
	// ��ũ�� �ִϸ��̼� ���
	switch (iconFrameX)
	{
	case 7:
		iconFrameX = 6;
		break;
	case 6:
		iconFrameX = 7;
		break;
	}
}

void TitleScene::Render(HDC hdc)
{
	// ��� ����
	backGround->Render(hdc, WIN_SIZE_X / 2, countFrameY);
	// Ÿ��Ʋ �ִϸ��̼� ������ ��ũ�� ������ ����
	if (bIsSceneIcon)
	{
		timeLate = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);	// ��ũ ������ ����
		selectIcon->Render(hdc, WIN_SIZE_X / 4, iconPosY[iconPosArr], iconFrameX, 0, 0.8f);

	}
}

void TitleScene::Release()
{
	timeLate = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);	// ������ ���󺹱�
}
