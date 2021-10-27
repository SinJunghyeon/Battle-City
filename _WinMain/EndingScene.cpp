#include "EndingScene.h"
#include "Image.h"
#include "StageScene.h"
#include "DestroyCountManager.h"

HRESULT EndingScene::Init()
{
    hiscoreTextPos.x = 370;
    hiscoreTextPos.y = 50;

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/HISocre.bmp", hiscoreTextPos.x, hiscoreTextPos.y, true, RGB(255, 0, 255));
    highScoreText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/HISocre.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage_w.bmp", hiscoreTextPos.x / 3, hiscoreTextPos.y/2, true, RGB(255, 0, 255));
    stageText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Stage_w.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number_w.bmp", hiscoreTextPos.x / 2, hiscoreTextPos.y, 5, 2, true, RGB(255, 0, 255));
    stageNumber = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
    enemyTotalText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
    for(int i = 0; i<4; i++)
    {
        scoreNumber[i] = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number_w.bmp");
    }

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Player1.bmp", 230, 40, true, RGB(255, 0, 255));
    player1Text = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Player1.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/PTS.bmp", 90, 40, true, RGB(255, 0, 255));
    textPTS = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/PTS.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Enemy/Enemy.bmp", 512, 384, 8, 6,true, RGB(255, 0, 255));
    enemyTankImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Enemy/Enemy.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/Arrow.bmp", 23, 20, true, RGB(255, 0, 255));
    arrowImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Arrow.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/TotalScore.bmp", WIN_SIZE_X/2, 40*1.5, true, RGB(255, 0, 255));
    textTotal = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/TotalScore.bmp");

    destroyedEnemy = DestroyCountManager::GetSingleton()->GetDestroyCount();

    return S_OK;
}

void EndingScene::Update()
{   
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
    {
        SceneManager::GetSingleton()->ChangeScene("gameoverS");
    }

    switch (enemyCountArrNum)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        if (enemyCount[enemyCountArrNum] < destroyedEnemy[enemyCountArrNum])
        {
            enemyCount[enemyCountArrNum]++;
        }
        if (enemyCount[enemyCountArrNum] == destroyedEnemy[enemyCountArrNum])
        {
            enemyTotal += enemyCount[enemyCountArrNum];
            enemyCountArrNum++;
        }
        break;
    case 4:
        isAnimation = false;
        break;
    default:
        enemyCountArrNum = 0;
        break;
    }

}

void EndingScene::Render(HDC hdc)
{
    SetTimer(g_hWnd, 0, 1, NULL);

    highScoreText->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 10);

    stageText->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 6);
    stageNumber->Render(hdc, WIN_SIZE_X * 3 / 5, WIN_SIZE_Y / 6, stageScene.GetStageNum(), 0);
    player1Text->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 4);

    for (int i = 0; i < 4; i++)
    {
        enemyTankImage->Render(hdc, enemyTankImagePosX, enemyTankImagePosY[i], 0, i,0.8f);
        arrowImage->Render(hdc, enemyTankImagePosX - 50, enemyTankImagePosY[i]);
        textPTS->Render(hdc, scoreNumberPosX * 2 / 3, enemyTankImagePosY[i]);

        // 죽인 에너미 1의 자리
        if (enemyCount[i] % 10 < 5)
        {
            scoreNumber[i]->Render(hdc, scoreNumberPosX, enemyTankImagePosY[i], enemyCount[i] % 5, 0);
        }
        else if (enemyCount[i] % 10 >= 5)
        {
            scoreNumber[i]->Render(hdc, scoreNumberPosX, enemyTankImagePosY[i], enemyCount[i] % 5, 1);
        }

        // 스코어
        scoreNumber[i]->Render(hdc, scoreNumberPosX / 2, enemyTankImagePosY[i], 0, 0);           // 1의 자리

        if (enemyCount[i] >= 1)
        {
            scoreNumber[i]->Render(hdc, scoreNumberPosX / 2 - 40, enemyTankImagePosY[i], 0, 0);  // 10의 자리

            // 100의 자리
            if (enemyCount[i] < 5)                                                               
            {
                scoreNumber[i]->Render(hdc, scoreNumberPosX / 2 - 80, enemyTankImagePosY[i], enemyCount[i] % 5, 0);
            }
            else if (enemyCount[i] >= 5)
            {
                scoreNumber[i]->Render(hdc, scoreNumberPosX / 2 - 80, enemyTankImagePosY[i], enemyCount[i] % 5, 1);
            }
        }

        if (enemyCount[i] >= 10)
        {
            scoreNumber[i]->Render(hdc, scoreNumberPosX - 40, enemyTankImagePosY[i], enemyCount[i] / 10, 0);      // 죽인 에너미 10의 자리
            scoreNumber[i]->Render(hdc, scoreNumberPosX / 2 - 120, enemyTankImagePosY[i], enemyCount[i] / 10, 0); // 스코어 1000의 자리
        }
        else if (enemyCount[i] >= 50)
        {
            scoreNumber[i]->Render(hdc, scoreNumberPosX - 40, enemyTankImagePosY[i], (enemyCount[i] / 10) % 5, 1);      // 죽인 에너미 10의 자리
            scoreNumber[i]->Render(hdc, scoreNumberPosX / 2 - 120, enemyTankImagePosY[i], (enemyCount[i] / 10) % 5, 1); // 스코어 1000의 자리
        }
    }

    textTotal->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y * 4 / 5);
    if (!isAnimation)
    {
        if (enemyTotal < 5)
        {
            enemyTotalText->Render(hdc, scoreNumberPosX, WIN_SIZE_Y * 4 / 5, enemyTotal % 5, 0);
        }
        else if (enemyTotal >= 5)
        {
            enemyTotalText->Render(hdc, scoreNumberPosX, WIN_SIZE_Y * 4 / 5, enemyTotal % 5, 1);
        }
        
        if (enemyTotal >= 10 && enemyTotal < 50)
        {
            enemyTotalText->Render(hdc, scoreNumberPosX - 40, WIN_SIZE_Y * 4 / 5, enemyTotal / 10, 0);
        }
        else if (enemyTotal >= 50 && enemyTotal <= 99)
        {
            enemyTotalText->Render(hdc, scoreNumberPosX - 40, WIN_SIZE_Y * 4 / 5, (enemyTotal / 10) % 5, 1);
        }
    }
}

void EndingScene::Release()
{
    SetTimer(g_hWnd, 0, 10, NULL);

    enemyCountArrNum = 0;

    for (int i = 0; i < 4; i++)
    {
        enemyCount[i] = 0;
    }
    isAnimation = true;

}
