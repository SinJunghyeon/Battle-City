#include "EndingScene.h"
#include "Image.h"
#include "StageScene.h"

HRESULT EndingScene::Init()
{
    hiscoreTextPos.x = 370;
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

    switch (arrNum)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    if (countKillEnemy[arrNum] < killEnemyNumber[arrNum])
    {
        countKillEnemy[arrNum]++;
        if (countKillEnemy[arrNum] >= 10)  //앞(10의자리)으로 넘어가기
        {
            killEnemyNumber10[arrNum] = countKillEnemy[arrNum] / 10;
            killEnemyNumber5[arrNum] = 0;
        }
        if (countKillEnemy[arrNum] % 10 >= 5)
        {
            killEnemyNumber5[arrNum] = 1;
        }
    }
    if (countKillEnemy[arrNum] == killEnemyNumber[arrNum])
    {
        arrNum++;
    }
    break;

    case 4:
        isAnimetion = false;
    break;

    default:
        arrNum = 0;
        break;
    }


    if (totalKillEnemy >= 10)  //앞(10의자리)으로 넘어가기
    {
        totalKillEnemy10 = totalKillEnemy / 10;
        totalKillEnemy5 = 0;
    }
    if (totalKillEnemy % 10 >= 5)   //앞으로 안가고 자기네에서 출력
    {
        totalKillEnemy5 = 1;
    }
}

void EndingScene::Render(HDC hdc)
{
    SetTimer(g_hWnd, 0, 1, NULL);

    hiscoreText->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 10);
    stageText->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 6);
    stageNumText->Render(hdc, WIN_SIZE_X * 3 / 5, WIN_SIZE_Y / 6, 1, 0);
    player1Text->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 4);

    for (int i = 0; i < 4; i++)
    {
        killEnemy->Render(hdc, killEnemyPosX, killEnemyPosY[i], 0, i);
        killEnemyArrow->Render(hdc, killEnemyPosX - 40, killEnemyPosY[i]);
        textPTS->Render(hdc, scoreTextPosX * 2 / 3, killEnemyPosY[i]);

        scoreText[i]->Render(hdc, scoreTextPosX, killEnemyPosY[i], countKillEnemy[i]%5, killEnemyNumber5[i]);//죽인 에너미 1의 자리

        scoreText[i]->Render(hdc, scoreTextPosX / 2, killEnemyPosY[i], 0, 0);
        if (countKillEnemy[i] >= 1/* || killEnemyNumber5[i] >= 1 || killEnemyNumber10[i] >= 1*/)//왼쪽 스코어
        {
            scoreText[i]->Render(hdc, scoreTextPosX / 2 - 40, killEnemyPosY[i], 0, 0);                         //10의 자리
            scoreText[i]->Render(hdc, scoreTextPosX / 2 - 80, killEnemyPosY[i], countKillEnemy[i]%5, killEnemyNumber5[i]);//100의 자리
        }
        if (killEnemyNumber10[i] >= 1)
        {
            scoreText[i]->Render(hdc, scoreTextPosX - 40, killEnemyPosY[i], killEnemyNumber10[i], 0);      //죽인 에너미 10의 자리
            scoreText[i]->Render(hdc, scoreTextPosX / 2 - 120, killEnemyPosY[i], killEnemyNumber10[i], 0); //스코어 1000의 자리
        }
    }

    textTotal->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y * 4 / 5);
    if (!isAnimetion)
    {
        totalKillText->Render(hdc, scoreTextPosX, WIN_SIZE_Y * 4 / 5, totalKillEnemy%5, totalKillEnemy5);
        if (totalKillEnemy10 >= 1 && totalKillEnemy10 < 5)
        {
            totalKillText->Render(hdc, scoreTextPosX - 40, WIN_SIZE_Y * 4 / 5, totalKillEnemy10, 0);
        }
        else if (totalKillEnemy10 >= 5 && totalKillEnemy10 <= 9)
        {
            totalKillText->Render(hdc, scoreTextPosX - 40, WIN_SIZE_Y * 4 / 5, totalKillEnemy10 % 5, 1);
        }
    }
}

void EndingScene::Release()
{
    SetTimer(g_hWnd, 0, 10, NULL);

    arrNum = 0;

    for (int i = 0; i < 4; i++)
    {
        countKillEnemy[i] = 0;
        killEnemyNumber5[i] = 0;
        killEnemyNumber10[i] = 0;
    }

    isAnimetion = true;
}
