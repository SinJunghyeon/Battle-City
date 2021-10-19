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
    scoreText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Player1.bmp", 230, 40, true, RGB(255, 0, 255));
    player1Text = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Player1.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/PTS.bmp", 90, 40, true, RGB(255, 0, 255));
    textPTS = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/PTS.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Enemy/Enemy.bmp", 512, 384, 8, 6,true, RGB(255, 0, 255));
    killEnemy = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Enemy/Enemy.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/Arrow.bmp", 23, 20, true, RGB(255, 0, 255));
    killEnemyArrow = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Arrow.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/TotalScore.bmp", WIN_SIZE_X/2, 40*1.5, true, RGB(255, 0, 255));
    textTotal = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/TotalScore.bmp");


    return S_OK;
}

void EndingScene::Update()
{   
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
    {
        SceneManager::GetSingleton()->ChangeScene("gameoverS");
    }

    /*
    * if(1�� ��ũ || 2����ũ || 3�� ��ũ || 4����ũ)
    * {
    *   isAnimation = true;
    * }
    */
}

void EndingScene::Render(HDC hdc)
{
    hiscoreText->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 10);
    stageText->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 6);
    stageNumText->Render(hdc, WIN_SIZE_X * 3 / 5, WIN_SIZE_Y / 6, 1, 0);
    player1Text->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 4);

    for (int i = 0; i < 4; i++)
    {
        killEnemy->Render(hdc, killEnemyPosX, killEnemyPosY[i], 0, i);
        killEnemyArrow->Render(hdc, killEnemyPosX-50, killEnemyPosY[i]);
        scoreText->Render(hdc, scoreTextPosX, killEnemyPosY[i], 0, 0);
        textPTS->Render(hdc, scoreTextPosX - scoreTextPosX/3, killEnemyPosY[i]);
        //if(���� �� ���� >= 10)
        //{
        //    scoreText->Render(hdc,scoreTextPos.x-(scoreTextPos.x/2),scoreTextPos.y,���� �� ����/10,0);
        //}
    }
    textTotal->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y*4/5);


}

void EndingScene::Release()
{
}
