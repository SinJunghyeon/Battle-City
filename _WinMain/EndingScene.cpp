#include "EndingScene.h"
#include "Image.h"
#include "StageScene.h"

HRESULT EndingScene::Init()
{
    hiscoreTextPos.x = 470;
    hiscoreTextPos.y = 50;


    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/HISocre.bmp", hiscoreTextPos.x, hiscoreTextPos.y, true, RGB(255, 0, 255));
    hiscoreText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/HISocre.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage_w.bmp", hiscoreTextPos.x / 3, hiscoreTextPos.y/2, true, RGB(255, 0, 255));
    stageText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage_w.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number_w.bmp", hiscoreTextPos.x / 2, hiscoreTextPos.y, 5, 2, true, RGB(255, 0, 255));
    stageNumText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
    totalKillText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
    for(int i = 0; i<4; i++)
    {
        scoreText[i] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
    }

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
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
    {
        SceneManager::GetSingleton()->ChangeScene("gameoverS");
    }

        for (int i = 0; i < 4; i++)
        {
            while (killEnemyNumber[i] >= 10)  //앞(10의자리)으로 넘어가기
            {
                killEnemyNumber10[i] ++;
                killEnemyNumber[i] -= 10;
                if (killEnemyNumber[i] < 10)
                {
                    break;
                }
            }
            if (killEnemyNumber[i] >= 5)   //앞으로 안가고 자기네에서 출력
            {
                killEnemyNumber5[i] ++;
                killEnemyNumber[i] -= 5;
            }
        }

        while (totalKillEnemy >= 10)  //앞(10의자리)으로 넘어가기
        {
            totalKillEnemy10 ++;
            totalKillEnemy -= 10;
            if (totalKillEnemy < 10)
            {
                break;
            }
        }
        if (totalKillEnemy >= 5)   //앞으로 안가고 자기네에서 출력
        {
            totalKillEnemy5 ++;
            totalKillEnemy -= 5;
        }

    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
    {
    }


   // if(killEnemyNumber)
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
        killEnemyArrow->Render(hdc, killEnemyPosX - 50, killEnemyPosY[i]);
        textPTS->Render(hdc, scoreTextPosX * 2 / 3, killEnemyPosY[i]);

        scoreText[i]->Render(hdc, scoreTextPosX, killEnemyPosY[i], killEnemyNumber[i], killEnemyNumber5[i]);//죽인 에너미 1의 자리

        scoreText[i]->Render(hdc, scoreTextPosX / 2, killEnemyPosY[i], 0, 0);
        if (killEnemyNumber[i] >= 1 || killEnemyNumber5[i] >= 1 || killEnemyNumber10[i] >= 1)//왼쪽 스코어
        {
            scoreText[i]->Render(hdc, scoreTextPosX / 2, killEnemyPosY[i], 0, 0);                                         //1의자리
            scoreText[i]->Render(hdc, scoreTextPosX / 2 - 50, killEnemyPosY[i], 0, 0);                                    //10의 자리
            scoreText[i]->Render(hdc, scoreTextPosX / 2 - 100, killEnemyPosY[i], killEnemyNumber[i], killEnemyNumber5[i]);//100의 자리
        }
        if (killEnemyNumber10[i] >= 1)
        {
            scoreText[i]->Render(hdc, scoreTextPosX - 50, killEnemyPosY[i], killEnemyNumber10[i], 0);      //죽인 에너미 10의 자리
            scoreText[i]->Render(hdc, scoreTextPosX / 2 - 150, killEnemyPosY[i], killEnemyNumber10[i], 0); //스코어 1000의 자리
        }
        
    }

    textTotal->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y * 4 / 5);
    totalKillText->Render(hdc, scoreTextPosX, WIN_SIZE_Y * 4 / 5, totalKillEnemy, totalKillEnemy5);
    if (totalKillEnemy10 >= 1)
    {
        totalKillText->Render(hdc, scoreTextPosX - 50, WIN_SIZE_Y * 4 / 5, totalKillEnemy10, 0);
    }
}

void EndingScene::Release()
{
}
