#include "EndingScene.h"
#include "Image.h"
#include "StageScene.h"

HRESULT EndingScene::Init()
{
    hiscoreTextPos.x = 470;
    hiscoreTextPos.y = 50;

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/HISocre.bmp", hiscoreTextPos.x, hiscoreTextPos.y, true, RGB(255, 0, 255));
    hiscoreText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/HISocre.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage_w.bmp", hiscoreTextPos.x/3, hiscoreTextPos.y/2, true, RGB(255, 0, 255));
    stageText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage_w.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number_w.bmp", hiscoreTextPos.x / 3, hiscoreTextPos.y / 2, 5, 2, true, RGB(255, 0, 255));
    stageNumText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");

    return S_OK;
}

void EndingScene::Update()
{
}

void EndingScene::Render(HDC hdc)
{
    hiscoreText->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 10);
    stageText->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 6);
    stageNumText->Render(hdc, WIN_SIZE_X *2 / 3, WIN_SIZE_Y / 6, 1, 0);//위치 수정 필요
}

void EndingScene::Release()
{
}
