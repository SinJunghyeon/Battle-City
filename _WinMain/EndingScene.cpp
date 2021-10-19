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

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number_w.bmp", hiscoreTextPos.x / 2, hiscoreTextPos.y, 5, 2, true, RGB(255, 0, 255));
    stageNumText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Player1.bmp", 230, 40, true, RGB(255, 0, 255));
    player1Text = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Player1.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/PTS.bmp", 90, 40, true, RGB(255, 0, 255));
    //textPTS = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/PTS.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Enemy/Enemy.bmp", 512, 384, 8, 6,true, RGB(255, 0, 255));
    killEnemy = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Enemy/Enemy.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/Arrow.bmp", 23, 20, true, RGB(255, 0, 255));
    killEnemyArrow = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Arrow.bmp");

    //스코어 텍스트 크기 조정 필요 스코어 텍스트에 사용하는 이미지가 이미 있어서 크기 조정이 안되는것이니 조정하자
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number_w.bmp", 40, 14, 5, 2, true, RGB(255, 0, 255));
    scoreText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");

    return S_OK;
}

void EndingScene::Update()
{   

}

void EndingScene::Render(HDC hdc)
{
    hiscoreText->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 10);
    stageText->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 6);
    stageNumText->Render(hdc, WIN_SIZE_X * 3 / 5, WIN_SIZE_Y / 6, 1, 0);
    player1Text->Render(hdc, WIN_SIZE_X * 1 / 5, WIN_SIZE_Y / 4);
    //textPTS->Render(hdc, )

    for (int i = 0; i < 4; i++)
    {
        killEnemy->Render(hdc, killEnemyPosX, killEnemyPosY[i], 0, i);
        killEnemyArrow->Render(hdc, killEnemyPosX-50, killEnemyPosY[i]);
        scoreText->Render(hdc, scoreTextPosX, killEnemyPosY[i],0,0);
    }

    //if(죽인 적 숫자 >= 10)
    //{
    //    scoreText[1]->Render(hdc,scoreTextPos.x-(scoreTextPos.x/2),scoreTextPos.y,죽인 적 숫자/10,0);
    //}

}

void EndingScene::Release()
{
}
