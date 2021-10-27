#include "BattleScene.h"
#include "Image.h"
#include "Tank.h"
#include "EnemyManager.h"
#include "Item.h"
#include "Ammo.h"
#include "AmmoManager.h"
#include "StageScene.h"
#include "DestroyCountManager.h"

HRESULT BattleScene::Init()
{
    // 아이템
    elapsedChange = NULL;
    elapsedCount = 1005;


    UIposX = TILE_SIZE * TILE_COUNT_X + 120;
    iconSize = 30;

    playerLife = 2;

    //파괴한 에너미 숫자
    destroyedEnemyCount = 0;


    //게임 오버 이미지 y값
    gameOverPosY = WIN_SIZE_Y * 3 / 2;

    // HQ 파괴 여부
    isHQDestroyed = false;
    elapsedEnding = NULL;


    // 타일 맵 이미지
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/SamlpTile1.bmp", 220, 220, 11, 11, true, RGB(255, 0, 255));
    sampleImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/SamlpTile1.bmp");
    if (sampleImage == nullptr)
    {
        cout << "Image/BattleCity/SamlpTile1.bmp 로드 실패!!" << endl;
        return E_FAIL;
    }

    // 배경 이미지
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
    backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");
    if (backGround == nullptr)
    {
        cout << "Image/BattleCity/mapImage.bmp 파일 로드에 실패했다." << endl;

        return E_FAIL;
    }

    // 폭발 이미지
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Boom_Effect.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Big_Boom_Effect.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));

    for (int i = 0; i < BOOM_NUM; i++)
    {
        boomEffect[i].boom = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Boom_Effect.bmp");
        if (boomEffect[i].boom == nullptr)
        {
            cout << "Image/BattleCity/Effect/Boom_Effect.bmp 파일 로드에 실패했다." << endl;

            return E_FAIL;
        }

        boomEffect[i].bigBoom = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Effect/Big_Boom_Effect.bmp");
        if (boomEffect[i].bigBoom == nullptr)
        {
            cout << "Image/BattleCity/Effect/Big_Boom_Effect.bmp 파일 로드에 실패했다." << endl;

            return E_FAIL;
        }
    }

    // 타일맵 로드
    Load();


    // 적 매니저
    enemyMgr = new EnemyManager;
    enemyMgr->Init();
    enemyMgr->SetTileMapManager(tileInfo);
    vecEnemies = enemyMgr->GetEnemies();
    vecEnemies.resize(enemyMgr->GetEnemyMaxCount());


    // 플레이어 탱크
    player = new Tank;
    player->Init();
    playerSpawnPos = GetSpawnPos(tileInfo, ObjectType::PLAYER).back();
    player->SetPos(playerSpawnPos);
    player->SetTileMap(tileInfo);
    playerTankRect = player->GetShape();
    player->SetEnemy(vecEnemies);

    // ���� �÷��̾��� ��� ������
    for (int i = 0; i < vecEnemies.size(); ++i)
    {
        vecEnemies[i]->SetPlayer(player);
    }

    // 아이템
    mpItem = new Item;
    mpItem->Init();
    itemSpawnPos = GetSpawnPos(tileInfo, ObjectType::ITEM).back();
    mpItem->SetPos(itemSpawnPos);
    itemRect = mpItem->GetShape();
    itemRect.left = mpItem->GetPos().x - mpItem->GetBodySize() / 2;
    itemRect.top = mpItem->GetPos().y - mpItem->GetBodySize() / 2;
    itemRect.right = mpItem->GetPos().x + mpItem->GetBodySize() / 2;
    itemRect.bottom = mpItem->GetPos().y + mpItem->GetBodySize() / 2;
    mpItem->SetShape(itemRect);

    //UI
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/Icon_Enemy.bmp", iconSize-5, iconSize-5);
    enemyIcon = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/Icon_Enemy.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/player1Life.bmp", iconSize * 2, iconSize * 2, true, RGB(255, 0, 255));
    P1LifeImage = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/player1Life.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number.bmp", 40, 14, 5, 2, true, RGB(255,0,255));
    numberText = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Number.bmp");

    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/StageFlag.bmp", iconSize * 2, iconSize * 1.5, true, RGB(255, 0, 255));
    stageFlag = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Icon/StageFlag.bmp");

    //게임 오버
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Game_Over.bmp", WIN_SIZE_X / 8 , WIN_SIZE_Y / 12, true, RGB(255, 0, 255));
    gameOverImg = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Game_Over.bmp");

    return S_OK;
}

void BattleScene::Update()
{
    //cout << boolalpha << "mpItem->GetExistItem() : " << mpItem->GetExistItem() << endl;
    //cout << "elapsedChange : " << elapsedChange << endl;
    //cout << "elapsedCount : " << elapsedCount << endl;

    // 타일 속성 확인용 코드
    for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
    {
        if (PtInRect(&(tileInfo[i].rc), g_ptMouse))
        {
            if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON)) // 디버그용
            {
                cout << i << " tile" << endl;
                cout << "mouse x : " << g_ptMouse.x << "mouse y : " << g_ptMouse.y << endl;
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

    // 플레이어 탱크
    tempPos = player->GetPos();
    player->Update();
    //if (tempPos.x != player->GetPos().x || tempPos.y != player->GetPos().y)
    //{
    //    cout << "x : " << player->GetPos().x << " y : " << player->GetPos().y << endl;
    //}
    playerTankRect = player->GetShape();

    //적 탱크
    enemyMgr->Update();

    //아이템
    mpItem->Update();
    if (mpItem->GetExistItem() == true)
    {
        itemRect = mpItem->GetShape();
    }

    //플레이어 아이템 접촉
    CollisionItem();

    //HQ주변 타일 되돌리기
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
        //적탱크의 상태가 IDLE일 때
        if (elapsedCount < 1005)
        {
            elapsedCount++;
            if ((vecEnemies[i]->GetTankState() == ecTankState::IDLE) && elapsedCount >= 1000)
            {
                (vecEnemies[i]->SetTankState(ecTankState::MOVE));
            }
        }
    }

    // 폭발 이펙트 업데이트
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

    // 플레이어 미사일 타일 접촉
    PlayerAmmoMapCollision(boomEffect, player, tileInfo);

    // 적 미사일 타일 접촉
    for (int i = 0; i < vecEnemies.size(); ++i)
    {
        EnemyAmmoMapCollision(boomEffect, vecEnemies[i], tileInfo);
    }

    // 미사일 탱크 접촉
    AmmoTankCollision(boomEffect, player);

    // �� ���߼� �ֽ�ȭ
    DestroyCountManager::GetSingleton()->SetDestroyCount(destroyedEnemy);

    //테스트
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
  
    //탱크 라이프 초기화        //숫자를 높여줘야하는데 init에 사용할 시 한번밖에 안불러와서 playerLife가 2로 계속 유지된다.
    numberText->SetCurrFrameX(playerLife);

    // ���ӿ�� ���� Ȯ��
    if ((playerLife < 0) || isHQDestroyed)
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
        player->SetMoveSpeed(0.0f);                                 // 21.10.26 게임이 끝났을 때 스피드 0으로 -> 다음 스테이지로 넘어갈 시 스피드 초기화하기
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

    // 플레이어 탱크
    player->Render(hdc);

    // 적 탱크
    if (enemyMgr)
        enemyMgr->Render(hdc);

    // 아이템    
    if (mpItem->GetExistItem() == true)
    {
        mpItem->Render(hdc);
    }

    // 폭발 이펙트 렌더
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

    //에너미탱크 UI
    for (int i = 0; i < (enemyMgr->GetEnemyMaxCount() - destroyedEnemyCount); i++)
    {
        switch (i % 2)
        {
        case 0:
            enemyIcon->Render(hdc, UIposX, 50 + (i * 15));
            break;
        case 1:
            enemyIcon->Render(hdc, UIposX + iconSize-5, 50 + (i - 1) * 15);
            break;
        default:
            break;
        }
    }

    //라이프 UI
    P1LifeImage->Render(hdc, UIposX + iconSize / 2, WIN_SIZE_Y * 3 / 5);

    if (playerLife % 10 < 5)  // 1의 자리(5미만)
    {
        numberText->Render(hdc, UIposX + iconSize * 3 / 2, WIN_SIZE_Y * 3 / 5 + iconSize / 2, playerLife % 5, 0, 3.0f);
    }
    else if (playerLife % 10 >= 5)  // 1의 자리(5이상)
    {
        numberText->Render(hdc, UIposX + iconSize * 3 / 2, WIN_SIZE_Y * 3 / 5 + iconSize / 2, playerLife % 5, 1, 3.0f);
    }

    if (playerLife / 10 >= 1 && playerLife / 10 < 5)   // 10의 자리 (50미만)
    {
        numberText->Render(hdc, UIposX + iconSize/ 2, WIN_SIZE_Y * 3 / 5 + iconSize / 2, numberText->GetCurrFrameX() / 10, 0, 3.0f);
    }
    else if (playerLife / 10 >= 5)   // 10의 자리 (50이상)
    {
        numberText->Render(hdc, UIposX + iconSize/ 2, WIN_SIZE_Y * 3 / 5 + iconSize / 2, (numberText->GetCurrFrameX() / 10) % 5, 1, 3.0f);
    }
    // -> img->GetCurrFrameX, GetCurrFrameY를 사용하여 변수 줄이기

    stageFlag->Render(hdc, UIposX + iconSize / 2, WIN_SIZE_Y * 4 / 5);                                  // 스테이지 깃발
    numberText->Render(hdc, UIposX + iconSize, WIN_SIZE_Y * 4 / 5 + iconSize, stagescene.GetStageNum(), 0, 4.0f);        // 스테이지 숫자

    //게임 오버
    gameOverImg->Render(hdc, 330, gameOverPosY);
}

void BattleScene::Release()
{
    // 플레이어 탱크
    SAFE_RELEASE(player);
    // 적 탱크
    SAFE_RELEASE(enemyMgr);
    // 아이템
    SAFE_RELEASE(mpItem);
}

void BattleScene::Load(int loadIndex)
{
    string loadFileName = "Save/saveMapData_" + to_string(loadIndex);
    loadFileName += ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,           // 읽기, 쓰기
        0, NULL,                // 공유, 보안 모드
        OPEN_EXISTING,          // 파일 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등등)
        NULL);

    // 읽기
    DWORD readByte;
    if (ReadFile(hFile, tileInfo, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y,
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);
}

void BattleScene::PlayerAmmoMapCollision(Boom* boom, Tank* tank, TILE_INFO* tile)
{
    for (int j = 0; j < tank->ammoCount; j++)
    {
        RECT ammoRect = tank->ammoPack[j].GetShape();
        if (tank->GetImgFrameY() < 3)                                                   //21.10.25 플레이어 탱크 최종렙보다 아래일 때 강철 못 부심
        {
            for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
            {
                if (IntersectRect(&tempRect, &ammoRect, &tile[i].rc) && tank->ammoPack[j].GetIsFire()) // Ammo랑 Tile이 충돌하면
                {
                    if ((tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::HQ_WALL)) // 충돌한 Tile이 벽일때
                    {
                        BoomAnimation(boom, BoomType::SMALL_BOOM, tank->ammoPack[j].GetPos());
                        tile[i].hp--;
                        if (tile[i].hp == 0) // 파괴된 벽인 경우
                        {
                            tile[i].frameX = 10;
                            tile[i].frameY = 10; // ROAD로 바꾼다.
                        }
                        else
                        {
                            tile[i].frameY = 8;
                            switch (tank->ammoPack[j].GetMoveDir()) // Ammo의 방향에 따라 처리
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
                    if ((tile[i].terrain == Terrain::STEEL) || (tile[i].terrain == Terrain::HQ_STEEL) || (tile[i].terrain == Terrain::DESTROYED_HQ))
                    {
                        tank->ammoPack[j].SetIsFire(false);
                        tank->ammoPack[j].SetPos(tank->GetPos());
                        tank->ammoPack[j].SetBodySize(0);
                    }
                    else if (tile[i].terrain == Terrain::HQ)    // 충돌한 타일이 HQ일때
                    {
                        POINTFLOAT hqPos;
                        hqPos.x = tile[713].rc.left;
                        hqPos.y = tile[713].rc.bottom;

                        BoomAnimation(boom, BoomType::BIG_BOOM, hqPos);
                        tile[713].frameX += 2;
                        tile[714].frameX += 2;
                        tile[741].frameX += 2;
                        tile[742].frameX += 2;
                        tile[713].terrain = Terrain::DESTROYED_HQ;
                        tile[714].terrain = Terrain::DESTROYED_HQ;
                        tile[741].terrain = Terrain::DESTROYED_HQ;
                        tile[742].terrain = Terrain::DESTROYED_HQ;
                        tank->ammoPack[j].SetIsFire(false);
                        tank->ammoPack[j].SetPos(tank->GetPos());
                        tank->ammoPack[j].SetBodySize(0);

                        isHQDestroyed = true;
                    }
                }
            }
        }
        if (player->GetImgFrameY() >= 3)                                                        //21.10.25 플레이어 탱크 최종렙일 때 강철 부심
        {
            for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
            {
                if (IntersectRect(&tempRect, &ammoRect, &tile[i].rc) && tank->ammoPack[j].GetIsFire()) // Ammo랑 Tile이 충돌하면
                {
                    if ((tile[i].terrain == Terrain::STEEL) || (tile[i].terrain == Terrain::HQ_STEEL) || (tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::HQ_WALL)) // 충돌한 Tile이 벽일때
                    {
                        BoomAnimation(boom, BoomType::SMALL_BOOM, tank->ammoPack[j].GetPos());
                        tile[i].hp -= 3;
                        if (tile[i].hp < 0)
                        {
                            tile[i].frameX = 10;
                            tile[i].frameY = 10; // ROAD로 바꾼다.
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
            if (IntersectRect(&tempRect, &ammoRect, &tile[i].rc) && ammoPack[j]->GetIsFire()) // Ammo랑 Tile이 충돌하면
            {
                if ((tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::HQ_WALL)) // 충돌한 Tile이 벽일때
                {
                    BoomAnimation(boom, BoomType::SMALL_BOOM, ammoPack[j]->GetPos());
                    tile[i].hp--;
                    if (tile[i].hp == 0) // 파괴된 벽인 경우
                    {
                        tile[i].frameX = 10;
                        tile[i].frameY = 10; // ROAD로 바꾼다.
                    }
                    else
                    {
                        tile[i].frameY = 8;
                        switch (ammoPack[j]->GetMoveDir()) // Ammo의 방향에 따라 처리
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
                else if ((tile[i].terrain == Terrain::STEEL) || (tile[i].terrain == Terrain::HQ_STEEL) || (tile[i].terrain == Terrain::DESTROYED_HQ))
                {
                    ammoPack[j]->SetIsFire(false);
                    ammoPack[j]->SetPos(enemy->GetPos());
                    ammoPack[j]->SetBodySize(0);
                }
                else if (tile[i].terrain == Terrain::HQ)    // 충돌한 타일이 HQ일때
                {
                    POINTFLOAT hqPos;
                    hqPos.x = tile[713].rc.left;
                    hqPos.y = tile[713].rc.bottom;

                    BoomAnimation(boom, BoomType::BIG_BOOM, hqPos);
                    tile[713].frameX += 2;
                    tile[714].frameX += 2;
                    tile[741].frameX += 2;
                    tile[742].frameX += 2;
                    tile[713].terrain = Terrain::DESTROYED_HQ;
                    tile[714].terrain = Terrain::DESTROYED_HQ;
                    tile[741].terrain = Terrain::DESTROYED_HQ;
                    tile[742].terrain = Terrain::DESTROYED_HQ;
                    ammoPack[j]->SetIsFire(false);
                    ammoPack[j]->SetPos(enemy->GetPos());
                    ammoPack[j]->SetBodySize(0);

                    isHQDestroyed = true;
                }
            }
        }
    }
}

void BattleScene::AmmoTankCollision(Boom* boom, Tank* player)
{
    // 적 정보들을 가져온다.
    AmmoManager ammoMgr;
    vector<Ammo*> vecAmmos;

    // 플레이어 미사일이 적이나 적 미사일에 히트했을 경우
    for (int i = 0; i < player->ammoCount; ++i)
    {
        RECT ammoRect = player->ammoPack[i].GetShape();
        for (int j = 0; j < vecEnemies.size(); ++j)
        {
            RECT enemyRect = vecEnemies[j]->GetShape();
            ammoMgr = vecEnemies[j]->GetAmmoManager();
            vecAmmos = ammoMgr.GetAmmos();
            // 플레이어 미사일과 적 탱크가 충돌했을 경우
            if (IntersectRect(&tempRect, &ammoRect, &enemyRect) && player->ammoPack[i].GetIsFire())
            {
                BoomAnimation(boom, BoomType::BIG_BOOM, vecEnemies[j]->GetPos());
                vecEnemies[j]->SetIsAlive(false);
                vecEnemies[j]->SetTankState(ecTankState::DIE);
                if (j == 3 || j == 10 || j == 17)
                {
                    mpItem->SetExistItem(true);
                }

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
                // 플레이어 미사일과 적 미사일이 충돌했을 경우
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

    // 적 미사일이 플레이어에게 히트했을 경우
    for (int i = 0; i < vecEnemies.size(); ++i)
    {
        ammoMgr = vecEnemies[i]->GetAmmoManager();
        vecAmmos = ammoMgr.GetAmmos();
        for (int j = 0; j < vecAmmos.size(); ++j)
        {
            RECT enemyAmmoRect = vecAmmos[j]->GetShape();
            if (vecAmmos[j]->GetIsFire() && IntersectRect(&tempRect, &playerTankRect, &enemyAmmoRect))  // 적 미사일과 플레이어 탱크가 충돌했을 경우
            {
                vecAmmos[j]->SetIsFire(false);
                vecAmmos[j]->SetBodySize(0);
                if (player->GetInVincible() == false)
                {
                    BoomAnimation(boom, BoomType::BIG_BOOM, player->GetPos());
                    player->SetIsAlive(false);
                    player->Init();
                    player->SetImgFrameX(0);                                                // 21.10.25 플레이어 죽었을 때 리스폰 위로 보게끔
                    player->SetplayerLife(playerLife - 1);                                  // 21.10.25 플레이어 탱크아이템 먹었을 때 생명 수정
                    playerSpawnPos = GetSpawnPos(tileInfo, ObjectType::PLAYER).back();
                    player->SetPos(playerSpawnPos);
                    playerLife--;
                    //cout << "플레이어 목숨 : " << playerLife << endl;
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
    //헬멧
    if (mpItem->GetItemState() == ecFunctionItem::HELMET)
    {
        player->SetInvincible(true);
        player->SetElapsedInvincible(0);
        //playerTankRect.left = player->GetPos().x + 
    }
    //시계
    if (mpItem->GetItemState() == ecFunctionItem::WATCH)
    {
        //적탱크 일시정지
        for (int i = 0; i < vecEnemies.size(); ++i)
        {
            if (vecEnemies[i]->GetIsAilve() == true)
            {
                vecEnemies[i]->SetTankState(ecTankState::IDLE);
            }
            elapsedCount = 0;
        }
    }
    //삽
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
    //별
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
            player->SetAmmoCount(2);            //탄수 2개
        }
        if (player->GetImgFrameY() >= 3)
        {
            player->SetptAttackValue(2.5);      //공격력 증가
            player->SetImgFrameY(3);            //최대 레벨업일 때 이미지 그대로
        }
    }
    //수류탄
    if (mpItem->GetItemState() == ecFunctionItem::GRENADE)
    {
        //나와있는 적 모두 죽임  
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
    //탱크
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
