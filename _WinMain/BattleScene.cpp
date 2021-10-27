#include "BattleScene.h"
#include "Image.h"
#include "Tank.h"
#include "EnemyManager.h"
#include "Item.h"
#include "Ammo.h"
#include "AmmoManager.h"
#include "StageScene.h"

HRESULT BattleScene::Init()
{
    // Ÿ�� �� �̹���
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/SamlpTile1.bmp", 220, 220, 11, 11, true, RGB(255, 0, 255));
    sampleImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/SamlpTile1.bmp");
    if (sampleImage == nullptr)
    {
        cout << "Image/BattleCity/SamlpTile1.bmp �ε� ����!!" << endl;
        return E_FAIL;
    }

    // ��� �̹���
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
    backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");
    if (backGround == nullptr)
    {
        cout << "Image/BattleCity/mapImage.bmp ���� �ε忡 �����ߴ�." << endl;

        return E_FAIL;
    }

    // ���� �̹���
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Boom_Effect.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Big_Boom_Effect.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));

    for (int i = 0; i < BOOM_NUM; i++)
    {
        boomEffect[i].boom = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Boom_Effect.bmp");
        if (boomEffect[i].boom == nullptr)
        {
            cout << "Image/BattleCity/Effect/Boom_Effect.bmp ���� �ε忡 �����ߴ�." << endl;

            return E_FAIL;
        }

        boomEffect[i].bigBoom = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Big_Boom_Effect.bmp");
        if (boomEffect[i].bigBoom == nullptr)
        {
            cout << "Image/BattleCity/Effect/Big_Boom_Effect.bmp ���� �ε忡 �����ߴ�." << endl;

            return E_FAIL;
        }
    }

    // Ÿ�ϸ� �ε�
    Load();


    // �� �Ŵ���
    enemyMgr = new EnemyManager;
    enemyMgr->Init();
    enemyMgr->SetTileMapManager(tileInfo);
    vecEnemies = enemyMgr->GetEnemies();
    vecEnemies.resize(enemyMgr->GetEnemyMaxCount());


    // �÷��̾� ��ũ
    player = new Tank;
    player->Init();
    playerSpawnPos = GetSpawnPos(tileInfo, ObjectType::PLAYER).back();
    player->SetPos(playerSpawnPos);
    player->SetTileMap(tileInfo);
    playerTankRect = player->GetShape();
    player->SetEnemy(vecEnemies);

    // ���� �÷��̾��� ���� ��������
    for (int i = 0; i < vecEnemies.size(); ++i)
    {
        vecEnemies[i]->SetPlayer(player);
    }

    // ������
    mpItem = new Item;
    mpItem->Init();
    itemRect = mpItem->GetShape();

    //UI
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/Icon_Enemy.bmp", iconSize, iconSize);
    enemyIcon = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Icon_Enemy.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/player1Life.bmp", iconSize * 2, iconSize * 2, true, RGB(255, 0, 255));
    P1LifeImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/player1Life.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number.bmp", 40 * 3, 14 * 3, 5, 2);
    numberText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/StageFlag.bmp", iconSize * 2, iconSize * 1.5, true, RGB(255, 0, 255));
    stageFlag = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/StageFlag.bmp");

    //���� ����
    gameOverImgSize.x = WIN_SIZE_X / 8;
    gameOverImgSize.y = WIN_SIZE_Y / 12;
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Game_Over.bmp", gameOverImgSize.x, gameOverImgSize.y, true, RGB(255, 0, 255));
    gameOverImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Game_Over.bmp");

    return S_OK;
}

void BattleScene::Update()
{
    //cout << boolalpha << "mpItem->GetExistItem() : " << mpItem->GetExistItem() << endl;
    //cout << "elapsedChange : " << elapsedChange << endl;
    //cout << "elapsedCount : " << elapsedCount << endl;

    // Ÿ�� �Ӽ� Ȯ�ο� �ڵ�
    for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
    {
        if (PtInRect(&(tileInfo[i].rc), g_ptMouse))
        {
            if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON)) // ����׿�
            {
                cout << i << " tile" << endl;
                if (tileInfo[i].terrain == Terrain::WALL) cout << "WALL" << tileInfo[i].hp << endl;
                else if (tileInfo[i].playerSpawn) cout << "playerSpawn" << tileInfo[i].hp << endl;
                else if (tileInfo[i].enemySpawn) cout << "enemySpawn" << tileInfo[i].hp << endl;
                else if (tileInfo[i].itemSpawn) cout << "itemSpawn" << tileInfo[i].hp << endl;
                else if (tileInfo[i].isHQWall) cout << "isHQWall" << tileInfo[i].hp << endl;

                else if (tileInfo[i].terrain == Terrain::STEEL) cout << "STEEL" << tileInfo[i].hp << endl;
                else if (tileInfo[i].terrain == Terrain::ROAD) cout << "ROAD" << tileInfo[i].hp << endl;
                else if (tileInfo[i].terrain == Terrain::HQ) cout << "HQ" << tileInfo[i].hp << endl;
                else if (tileInfo[i].terrain == Terrain::GRASS) cout << "GRASS" << tileInfo[i].hp << endl;
                else if (tileInfo[i].terrain == Terrain::HQ_WALL) cout << "HQ_WALL" << tileInfo[i].hp << endl;
                else if (tileInfo[i].terrain == Terrain::HQ_STEEL) cout << "HQ_STEEL" << tileInfo[i].hp << endl;
            }
        }
    }

    // �÷��̾� ��ũ
    tempPos = player->GetPos();
    player->Update();
    //if (tempPos.x != player->GetPos().x || tempPos.y != player->GetPos().y)
    //{
    //    cout << "x : " << player->GetPos().x << " y : " << player->GetPos().y << endl;
    //}
    playerTankRect = player->GetShape();

    //�� ��ũ
    enemyMgr->Update();

    //������
    mpItem->Update();
    if (mpItem->GetExistItem() == true)
    {
        itemRect = mpItem->GetShape();
    }

    //�÷��̾� ������ ����
    CollisionItem();

    //HQ�ֺ� Ÿ�� �ǵ�����
    for (int i = 680; i < 750; i++)
    {
        if (tileInfo[i].terrain == Terrain::HQ_STEEL) //684, 685, 686, 687, 712, 715, 740, 743 -> HQ_STEEL
        {
            elapsedChange++;
            if (elapsedChange >= 2400)
            {
                for (int j = 600; j < TILE_COUNT_X * TILE_COUNT_Y; j++)
                {
                    if (tileInfo[j].terrain == Terrain::HQ_STEEL)
                    {
                        tileInfo[j].terrain = Terrain::HQ_WALL;
                        tileInfo[j].frameX = 8;
                        tileInfo[j].frameY = 0;
                        elapsedChange = 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < vecEnemies.size(); ++i)
    {
        //����ũ�� ���°� IDLE�� ��
        if (elapsedCount < 1005)
        {
            elapsedCount++;
            if ((vecEnemies[i]->GetTankState() == ecTankState::IDLE) && elapsedCount >= 1000)
            {
                (vecEnemies[i]->SetTankState(ecTankState::MOVE));
            }
        }
    }

    // ���� ����Ʈ ������Ʈ
    for (int i = 0; i < BOOM_NUM; i++)
    {
        if (boomEffect[i].isRender)
        {
            boomEffect[i].elapsedCount++;
            if (boomEffect[i].elapsedCount >= 5)
            {
                boomEffect[i].boom->SetCurrFrameX(boomEffect[i].boom->GetCurrFrameX() + 1);

                if ((boomEffect[i].boom->GetCurrFrameX() == 2) && boomEffect[i].type == BoomType::SMALL_BOOM)
                {
                    boomEffect[i].isRender = false;
                    boomEffect[i].boom->SetCurrFrameX(0);
                }
                else if ((boomEffect[i].boom->GetCurrFrameX() >= 3) && boomEffect[i].type == BoomType::BIG_BOOM)
                {
                    boomEffect[i].bigBoom->SetCurrFrameX(boomEffect[i].bigBoom->GetCurrFrameX() + 1);
                    if (boomEffect[i].bigBoom->GetCurrFrameX() == 2)
                    {
                        boomEffect[i].isRender = false;
                        boomEffect[i].bigBoom->SetCurrFrameX(0);
                        boomEffect[i].boom->SetCurrFrameX(0);
                    }
                }
                boomEffect[i].elapsedCount = 0;
            }
        }
    }

    // �÷��̾� �̻��� Ÿ�� ����
    PlayerAmmoMapCollision(boomEffect, player, tileInfo);

    // �� �̻��� Ÿ�� ����
    for (int i = 0; i < vecEnemies.size(); ++i)
    {
        EnemyAmmoMapCollision(boomEffect, vecEnemies[i], tileInfo);
    }

    // �̻��� ��ũ ����
    AmmoTankCollision(boomEffect, player);

    //EnemyCollision();

    //�׽�Ʈ
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
    {
        playerLife++;
        //destroyedEnemyCount++;
        cout << "P1L:" << playerLife << endl << "GetcurrFrameX:" << numberText->GetCurrFrameX() << endl;

    }
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RBUTTON))
    {
        playerLife--;
        //destroyedEnemyCount++;
        cout << "P1L:" << playerLife << endl << "GetcurrFrameX:" << numberText->GetCurrFrameX() << endl;
    }

    //��ũ ������ �ʱ�ȭ                    //���ڸ� ��������ϴµ� init�� ����� �� �ѹ��ۿ� �Ⱥҷ��ͼ� playerLife�� 2�� ��� �����ȴ�.
    numberText->SetCurrFrameX(playerLife);

    if (playerLife < 0)
    {
        gameOverPosY -= 5;
        if (gameOverPosY <= WIN_SIZE_Y / 2)
        {
            Sleep(1000);
            SceneManager::GetSingleton()->ChangeScene("endingS");
        }
    }
    else if (destroyedEnemyCount == enemyMgr->GetEnemyMaxCount())
    {
        player->SetMoveSpeed(0.0f);                                 // 21.10.26 ������ ������ �� ���ǵ� 0���� -> ���� ���������� �Ѿ �� ���ǵ� �ʱ�ȭ�ϱ�
        elapsedEnding++;
        if (elapsedEnding >= 100)
        {
            SceneManager::GetSingleton()->ChangeScene("endingS");
            elapsedEnding = 0;
        }
    }

}

void BattleScene::Render(HDC hdc)
{
    if (backGround)
        backGround->Render(hdc);

    for (int i = 0; i < TILE_COUNT_Y; i++)
    {
        for (int j = 0; j < TILE_COUNT_X; j++)
        {

            SetTerrain(&tileInfo[i * TILE_COUNT_X + j]);

            if (tileInfo[i * TILE_COUNT_X + j].isRender)
            {
                sampleImage->Render(hdc,
                    tileInfo[i * TILE_COUNT_X + j].rc.left + TILE_SIZE / 2,
                    tileInfo[i * TILE_COUNT_X + j].rc.top + TILE_SIZE / 2,
                    tileInfo[i * TILE_COUNT_X + j].frameX,
                    tileInfo[i * TILE_COUNT_X + j].frameY);
            }

            //Rectangle(hdc, tileInfo[i * TILE_COUNT_X + j].rc.left,
            //    tileInfo[i * TILE_COUNT_X + j].rc.top,
            //    tileInfo[i * TILE_COUNT_X + j].rc.right,
            //    tileInfo[i * TILE_COUNT_X + j].rc.bottom);
        }
    }

    // �÷��̾� ��ũ
    player->Render(hdc);

    // �� ��ũ
    if (enemyMgr)
        enemyMgr->Render(hdc);

    // ������    
    if (mpItem->GetExistItem() == true)
    {
        mpItem->Render(hdc);
    }

    // ���� ����Ʈ ����
    for (int i = 0; i < BOOM_NUM; i++)
    {
        if (boomEffect[i].isRender)
        {
            if (boomEffect[i].boom->GetCurrFrameX() <= 2)
            {
                boomEffect[i].boom->Render(hdc, boomEffect[i].boomPos.x, boomEffect[i].boomPos.y, boomEffect[i].boom->GetCurrFrameX(), boomEffect[i].boom->GetCurrFrameY(), 2.0f);

            }
            else if ((boomEffect[i].bigBoom->GetCurrFrameX() <= 1) && boomEffect[i].type == BoomType::BIG_BOOM)
            {
                boomEffect[i].bigBoom->Render(hdc, boomEffect[i].boomPos.x, boomEffect[i].boomPos.y, boomEffect[i].bigBoom->GetCurrFrameX(), boomEffect[i].bigBoom->GetCurrFrameY(), 2.0f);
            }
            break;
        }
    }

    //���ʹ���ũ UI
    for (int i = 0; i < (enemyMgr->GetEnemyMaxCount() - destroyedEnemyCount); i++)
    {
        switch (i % 2)
        {
        case 0:
            enemyIcon->Render(hdc, UIposX, 100 + (i * 15));
            break;
        case 1:
            enemyIcon->Render(hdc, UIposX + iconSize, 100 + (i - 1) * 15);
            break;
        default:
            break;
        }
    }

    //������ UI
    P1LifeImage->Render(hdc, UIposX + iconSize / 2, WIN_SIZE_Y / 2);

    if (playerLife % 10 < 5)  // 1�� �ڸ�(5�̸�)
    {
        numberText->Render(hdc, UIposX + iconSize * 2, WIN_SIZE_Y / 2 + iconSize / 2, playerLife % 5, 0);
    }
    else if (playerLife % 10 >= 5)  // 1�� �ڸ�(5�̻�)
    {
        numberText->Render(hdc, UIposX + iconSize * 2, WIN_SIZE_Y / 2 + iconSize / 2, playerLife % 5, 1);
    }

    if (playerLife / 10 >= 1 && playerLife / 10 < 5)   // 10�� �ڸ� (50�̸�)
    {
        numberText->Render(hdc, UIposX + iconSize, WIN_SIZE_Y / 2 + iconSize / 2, numberText->GetCurrFrameX() / 10, 0);
    }
    else if (playerLife / 10 >= 5)   // 10�� �ڸ� (50�̻�)
    {
        numberText->Render(hdc, UIposX + iconSize, WIN_SIZE_Y / 2 + iconSize / 2, (numberText->GetCurrFrameX() / 10) % 5, 1);
    }
    // -> img->GetCurrFrameX, GetCurrFrameY�� ����Ͽ� ���� ���̱�

    stageFlag->Render(hdc, UIposX + iconSize / 2, WIN_SIZE_Y * 4 / 5);                                  // �������� ���
    numberText->Render(hdc, UIposX + iconSize, WIN_SIZE_Y * 4 / 5 + iconSize, stagescene.GetStageNum(), 0);        // �������� ����

    //���� ����
    gameOverImg->Render(hdc, 330, gameOverPosY);
}

void BattleScene::Release()
{
    // �÷��̾� ��ũ
    SAFE_RELEASE(player);
    // �� ��ũ
    SAFE_RELEASE(enemyMgr);
    // ������
    SAFE_RELEASE(mpItem);
}

void BattleScene::Load(int loadIndex)
{
    string loadFileName = "Save/saveMapData_" + to_string(loadIndex);
    loadFileName += ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,           // �б�, ����
        0, NULL,                // ����, ���� ���
        OPEN_EXISTING,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);

    // �б�
    DWORD readByte;
    if (ReadFile(hFile, tileInfo, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y,
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
    }

    CloseHandle(hFile);
}

void BattleScene::PlayerAmmoMapCollision(Boom* boom, Tank* tank, TILE_INFO* tile)
{
    for (int j = 0; j < tank->ammoCount; j++)
    {
        RECT ammoRect = tank->ammoPack[j].GetShape();
        if (tank->GetImgFrameY() < 3)                                                   //21.10.25 �÷��̾� ��ũ ���������� �Ʒ��� �� ��ö �� �ν�
        {
            for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
            {
                if (IntersectRect(&tempRect, &ammoRect, &tile[i].rc) && tank->ammoPack[j].GetIsFire()) // Ammo�� Tile�� �浹�ϸ�
                {
                    if ((tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::HQ_WALL)) // �浹�� Tile�� ���϶�
                    {
                        BoomAnimation(boom, BoomType::SMALL_BOOM, tank->ammoPack[j].GetPos());
                        tile[i].hp--;
                        if (tile[i].hp == 0) // �ı��� ���� ���
                        {
                            tile[i].frameX = 10;
                            tile[i].frameY = 10; // ROAD�� �ٲ۴�.
                        }
                        else
                        {
                            tile[i].frameY = 8;
                            switch (tank->ammoPack[j].GetMoveDir()) // Ammo�� ���⿡ ���� ó��
                            {
                            case MoveDir::DOWN:
                                tile[i].frameX = 2;
                                break;
                            case MoveDir::UP:
                                tile[i].frameX = 4;
                                break;
                            case MoveDir::LEFT:
                                tile[i].frameX = 3;
                                break;
                            case MoveDir::RIGHT:
                                tile[i].frameX = 1;
                                break;
                            default:
                                break;
                            }
                        }
                        tank->ammoPack[j].SetIsFire(false);
                        tank->ammoPack[j].SetPos(tank->GetPos());
                        tank->ammoPack[j].SetBodySize(0);
                    }
                    if ((tile[i].terrain == Terrain::STEEL) || (tile[i].terrain == Terrain::HQ_STEEL))
                    {
                        tank->ammoPack[j].SetIsFire(false);
                        tank->ammoPack[j].SetPos(tank->GetPos());
                        tank->ammoPack[j].SetBodySize(0);
                    }
                    else if (tile[i].terrain == Terrain::HQ)    // �浹�� Ÿ���� HQ�϶�
                    {
                        POINTFLOAT hqPos;
                        hqPos.x = tile[713].rc.right;
                        hqPos.y = tile[713].rc.top;

                        BoomAnimation(boom, BoomType::BIG_BOOM, hqPos);
                        tile[713].frameX += 2;
                        tile[714].frameX += 2;
                        tile[741].frameX += 2;
                        tile[742].frameX += 2;
                        tank->ammoPack[j].SetIsFire(false);
                        tank->ammoPack[j].SetPos(tank->GetPos());
                        tank->ammoPack[j].SetBodySize(0);
                    }
                }
            }
        }
        if (player->GetImgFrameY() >= 3)                                                        //21.10.25 �÷��̾� ��ũ �������� �� ��ö �ν�
        {
            for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
            {
                if (IntersectRect(&tempRect, &ammoRect, &tile[i].rc) && tank->ammoPack[j].GetIsFire()) // Ammo�� Tile�� �浹�ϸ�
                {
                    if ((tile[i].terrain == Terrain::STEEL) || (tile[i].terrain == Terrain::HQ_STEEL) || (tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::HQ_WALL)) // �浹�� Tile�� ���϶�
                    {
                        BoomAnimation(boom, BoomType::SMALL_BOOM, tank->ammoPack[j].GetPos());
                        tile[i].hp -= 3;
                        if (tile[i].hp < 0)
                        {
                            tile[i].frameX = 10;
                            tile[i].frameY = 10; // ROAD�� �ٲ۴�.
                        }

                        tank->ammoPack[j].SetIsFire(false);
                        tank->ammoPack[j].SetPos(tank->GetPos());
                        tank->ammoPack[j].SetBodySize(0);
                    }
                }
            }
        }
    }
}

void BattleScene::EnemyAmmoMapCollision(Boom* boom, Enemy* enemy, TILE_INFO* tile)
{
    AmmoManager ammoMgr = enemy->GetAmmoManager();
    vector<Ammo*> ammoPack = ammoMgr.GetAmmos();

    for (int j = 0; j < ammoPack.size(); j++)
    {
        RECT ammoRect = ammoPack[j]->GetShape();

        for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
        {
            if (IntersectRect(&tempRect, &ammoRect, &tile[i].rc) && ammoPack[j]->GetIsFire()) // Ammo�� Tile�� �浹�ϸ�
            {
                if ((tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::HQ_WALL)) // �浹�� Tile�� ���϶�
                {
                    BoomAnimation(boom, BoomType::SMALL_BOOM, ammoPack[j]->GetPos());
                    tile[i].hp--;
                    if (tile[i].hp == 0) // �ı��� ���� ���
                    {
                        tile[i].frameX = 10;
                        tile[i].frameY = 10; // ROAD�� �ٲ۴�.
                    }
                    else
                    {
                        tile[i].frameY = 8;
                        switch (ammoPack[j]->GetMoveDir()) // Ammo�� ���⿡ ���� ó��
                        {
                        case MoveDir::DOWN:
                            tile[i].frameX = 2;
                            break;
                        case MoveDir::UP:
                            tile[i].frameX = 4;
                            break;
                        case MoveDir::LEFT:
                            tile[i].frameX = 3;
                            break;
                        case MoveDir::RIGHT:
                            tile[i].frameX = 1;
                            break;
                        default:
                            break;
                        }
                    }
                    ammoPack[j]->SetIsFire(false);
                    ammoPack[j]->SetPos(enemy->GetPos());
                    ammoPack[j]->SetBodySize(0);
                }
                else if ((tile[i].terrain == Terrain::STEEL) || (tile[i].terrain == Terrain::HQ_STEEL))
                {
                    ammoPack[j]->SetIsFire(false);
                    ammoPack[j]->SetPos(enemy->GetPos());
                    ammoPack[j]->SetBodySize(0);
                }
                else if (tile[i].terrain == Terrain::HQ)    // �浹�� Ÿ���� HQ�϶�
                {
                    POINTFLOAT hqPos;
                    hqPos.x = tile[713].rc.right;
                    hqPos.y = tile[713].rc.bottom;

                    BoomAnimation(boom, BoomType::BIG_BOOM, hqPos);
                    tile[713].frameX += 2;
                    tile[714].frameX += 2;
                    tile[741].frameX += 2;
                    tile[742].frameX += 2;
                    ammoPack[j]->SetIsFire(false);
                    ammoPack[j]->SetPos(enemy->GetPos());
                    ammoPack[j]->SetBodySize(0);
                }
            }
        }
    }
}

//void BattleScene::EnemyCollision()
//{
//    for (int i = 0; i < vecEnemies.size(); ++i)
//    {
//        for (int j = 0; j < vecEnemies.size(); ++j)
//        {
//            if (i != j)
//            {
//                POINTFLOAT buffPos1 = vecEnemies[i]->GetPos();
//                POINTFLOAT buffPos2 = vecEnemies[j]->GetPos();
//                RECT enemyRect1 = vecEnemies[i]->GetShape();
//                RECT enemyRect2 = vecEnemies[j]->GetShape();
//                RECT buffRect1 = enemyRect1;
//                RECT buffRect2 = enemyRect2;
//                if (IntersectRect(&tempRect, &enemyRect1, &enemyRect2))
//                {
//                    cout << "c" << endl;
//                    vecEnemies[i]->SetPos(buffPos1);
//                    vecEnemies[i]->SetShape(buffRect1);
//                    vecEnemies[j]->SetPos(buffPos2);
//                    vecEnemies[j]->SetShape(buffRect2);
//                }
//            }
//        }
//    }
//}

void BattleScene::AmmoTankCollision(Boom* boom, Tank* player)
{
    // �� �������� �����´�.
    AmmoManager ammoMgr;
    vector<Ammo*> vecAmmos;

    // �÷��̾� �̻����� ���̳� �� �̻��Ͽ� ��Ʈ���� ���
    for (int i = 0; i < player->ammoCount; ++i)
    {
        RECT ammoRect = player->ammoPack[i].GetShape();
        for (int j = 0; j < vecEnemies.size(); ++j)
        {
            RECT enemyRect = vecEnemies[j]->GetShape();
            ammoMgr = vecEnemies[j]->GetAmmoManager();
            vecAmmos = ammoMgr.GetAmmos();
            // �÷��̾� �̻��ϰ� �� ��ũ�� �浹���� ���
            if (IntersectRect(&tempRect, &ammoRect, &enemyRect) && player->ammoPack[i].GetIsFire())
            {
                BoomAnimation(boom, BoomType::BIG_BOOM, vecEnemies[j]->GetPos());
                vecEnemies[j]->SetIsAlive(false);
                vecEnemies[j]->SetTankState(ecTankState::DIE);

                player->ammoPack[i].SetIsFire(false);
                player->ammoPack[i].SetBodySize(0);

                switch (vecEnemies[j]->GetEnemyType())
                {
                case EnemyType::NORMAL:
                    destroyedEnemy[0]++;
                    cout << "destroy NORMAL : " << destroyedEnemy[0] << endl;
                    destroyedEnemyCount++;
                    cout << destroyedEnemyCount << endl;
                    break;
                case EnemyType::SPEED:
                    destroyedEnemy[1]++;
                    cout << "destroy SPEED : " << destroyedEnemy[1] << endl;
                    destroyedEnemyCount++;
                    cout << destroyedEnemyCount << endl;
                    break;
                case EnemyType::RPD:
                    destroyedEnemy[2]++;
                    cout << "destroy RPD : " << destroyedEnemy[2] << endl;
                    destroyedEnemyCount++;
                    cout << destroyedEnemyCount << endl;
                    break;
                case EnemyType::SUPER:
                    destroyedEnemy[3]++;
                    cout << "destroy SUPER : " << destroyedEnemy[3] << endl;
                    destroyedEnemyCount++;
                    cout << destroyedEnemyCount << endl;
                    break;
                default:
                    break;
                }
            }

            for (int k = 0; k < vecAmmos.size(); ++k)
            {
                RECT enemyAmmoRect = vecAmmos[k]->GetShape();
                // �÷��̾� �̻��ϰ� �� �̻����� �浹���� ���
                if (IntersectRect(&tempRect, &ammoRect, &enemyAmmoRect) && player->ammoPack[i].GetIsFire() && vecAmmos[k]->GetIsFire())
                {
                    player->ammoPack[i].SetIsFire(false);
                    player->ammoPack[i].SetBodySize(0);
                    vecAmmos[k]->SetIsFire(false);
                    vecAmmos[k]->SetBodySize(0);
                }
            }
        }
    }

    // �� �̻����� �÷��̾�� ��Ʈ���� ���
    for (int i = 0; i < vecEnemies.size(); ++i)
    {
        ammoMgr = vecEnemies[i]->GetAmmoManager();
        vecAmmos = ammoMgr.GetAmmos();
        for (int j = 0; j < vecAmmos.size(); ++j)
        {
            RECT enemyAmmoRect = vecAmmos[j]->GetShape();
            if (vecAmmos[j]->GetIsFire() && IntersectRect(&tempRect, &playerTankRect, &enemyAmmoRect))  // �� �̻��ϰ� �÷��̾� ��ũ�� �浹���� ���
            {
                vecAmmos[j]->SetIsFire(false);
                vecAmmos[j]->SetBodySize(0);
                if (player->GetInVincible() == false)
                {
                    BoomAnimation(boom, BoomType::BIG_BOOM, player->GetPos());
                    player->SetIsAlive(false);
                    player->Init();
                    player->SetImgFrameX(0);                                                // 21.10.25 �÷��̾� �׾��� �� ������ ���� ���Բ�
                    player->SetplayerLife(playerLife - 1);                                  // 21.10.25 �÷��̾� ��ũ������ �Ծ��� �� ���� ����
                    playerSpawnPos = GetSpawnPos(tileInfo, ObjectType::PLAYER).back();
                    player->SetPos(playerSpawnPos);
                    playerLife--;
                    //cout << "�÷��̾� ��� : " << playerLife << endl;
                }
            }
        }
    }
}

void BattleScene::CollisionItem()
{
    if (mpItem->GetExistItem() == true)
    {
        if (IntersectRect(&tempRect, &playerTankRect, &itemRect))
        {
            FunctionItem(boomEffect);
            mpItem->SetExistItem(false);
        }
    }
}

void BattleScene::FunctionItem(Boom* boom)
{
    //���
    if (mpItem->GetItemState() == ecFunctionItem::HELMET)
    {
        player->SetInvincible(true);
        player->SetElapsedInvincible(0);
        //playerTankRect.left = player->GetPos().x + 
    }
    //�ð�
    if (mpItem->GetItemState() == ecFunctionItem::WATCH)
    {
        //����ũ �Ͻ�����
        for (int i = 0; i < vecEnemies.size(); ++i)
        {
            if (vecEnemies[i]->GetIsAilve() == true)
            {
                vecEnemies[i]->SetTankState(ecTankState::IDLE);
            }
            elapsedCount = 0;
        }
    }
    //��
    if (mpItem->GetItemState() == ecFunctionItem::SHOVEL)
    {
        for (int i = 684; i < 688; i++)
        {
            tileInfo[i].terrain = Terrain::HQ_STEEL;
            tileInfo[i].frameX = 8;
            tileInfo[i].frameY = 2;
        }
        tileInfo[712].terrain = Terrain::HQ_STEEL;
        tileInfo[712].frameX = 8;
        tileInfo[712].frameY = 2;
        tileInfo[715].terrain = Terrain::HQ_STEEL;
        tileInfo[715].frameX = 8;
        tileInfo[715].frameY = 2;
        tileInfo[740].terrain = Terrain::HQ_STEEL;
        tileInfo[740].frameX = 8;
        tileInfo[740].frameY = 2;
        tileInfo[743].terrain = Terrain::HQ_STEEL;
        tileInfo[743].frameX = 8;
        tileInfo[743].frameY = 2;
    }
    //��
    if (mpItem->GetItemState() == ecFunctionItem::STAR)
    {
        player->SetImgFrameY(player->GetImgFrameY() + 1);
        if (player->GetImgFrameY() >= 1)
        {
            for (int i = 0; i < 2; i++)
            {
                player->ammoPack[i].SetMoveSpeed(600.0f);
            }
        }
        if (player->GetImgFrameY() >= 2)
        {
            player->SetAmmoCount(2);            //ź�� 2��
        }
        if (player->GetImgFrameY() >= 3)
        {
            player->SetptAttackValue(2.5);      //���ݷ� ����
            player->SetImgFrameY(3);            //�ִ� �������� �� �̹��� �״��
        }
    }
    //����ź
    if (mpItem->GetItemState() == ecFunctionItem::GRENADE)
    {
        //�����ִ� �� ��� ����  
        int count = 0;
        for (int i = 0; i < vecEnemies.size(); ++i)
        {
            if (vecEnemies[i]->GetIsAilve() == true)
            {
                BoomAnimation(boom, BoomType::BIG_BOOM, vecEnemies[i]->GetPos());
                vecEnemies[i]->SetIsAlive(false);
                vecEnemies[i]->SetTankState(ecTankState::DIE);
                count++;
            }
        }
        destroyedEnemyCount += count;
    }
    //��ũ
    if (mpItem->GetItemState() == ecFunctionItem::TANK)
    {
        player->SetplayerLife(player->GetplayerLife() + 1);
        playerLife = player->GetplayerLife();
    }
}

void BattleScene::BoomAnimation(Boom* boom, BoomType type, POINTFLOAT pos)
{
    for (int i = 0; i < BOOM_NUM; i++)
    {
        if (!boom[i].isRender)
        {
            boom[i].type = type;
            boom[i].boomPos = pos;
            boom[i].isRender = true;
            break;
        }
    }
}
