#include "TitleScene.h"
#include "Config.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	iconPosArr = 0;

	// 배경 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Title.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Title.bmp");
	// 탱크 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256, 8, 4, true, RGB(255, 0, 255));
	selectIcon = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Player/Player.bmp");

	return S_OK;
}

void TitleScene::Update()
{
	// 아래로 눌렀을 때 아이콘 아래로 이동
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		iconPosArr++;
		iconPosY[iconPosArr];
		if (iconPosArr > 1)
		{
			iconPosArr = 0;
		}
	}
	// 위로 눌렀을 때 아이콘 위로 이동
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		iconPosArr--;
		iconPosY[iconPosArr];
		if (iconPosArr < 0)
		{
			iconPosArr = 1;
		}
	}
	// 타이틀 애니메이션
	if (countFrameY >= WIN_SIZE_Y / 2)	
	{
		countFrameY -= 10;
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
		{
			countFrameY = WIN_SIZE_Y / 2;
		}
	}
	// 배경이 중앙에 왔을 때 엔터 키 누르면 다음 씬으로 이동
	if (countFrameY <= WIN_SIZE_Y / 2)
	{
		bIsSceneIcon = true;
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
		{
			SceneManager::GetSingleton()->ChangeScene("stageS");
			iconPosArr = 0;
		}
	}
	// 탱크의 애니메이션 재생
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
	// 배경 렌더
	backGround->Render(hdc, WIN_SIZE_X / 2, countFrameY);
	// 타이틀 애니메이션 끝나고 탱크의 아이콘 렌더
	if (bIsSceneIcon)
	{
		timeLate = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);	// 탱크 프레임 조정
		selectIcon->Render(hdc, WIN_SIZE_X / 4, iconPosY[iconPosArr], iconFrameX, 0, 0.8f);

	}
}

void TitleScene::Release()
{
	timeLate = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);	// 프레임 원상복구
}
