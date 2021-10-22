#include "BattleTest2.h"
#include "Image.h"
#include "Tank.h"
#include "EnemyManager.h"
#include "Item.h"
#include "Ammo.h"
#include "AmmoManager.h"

HRESULT BattleTest2::Init()
{
    // 타일 맵 이미지
    sampleImage = ImageManager::GetSingleton()->AddImage("Image/BattleCity/SamlpTile1.bmp", 220, 220, 11, 11, true, RGB(255, 0, 255));
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

    // 적 매니저
    enemyMgr = new EnemyManager;
    enemyMgr->Init();
    enemyMgr->SetTileMapManager(tileInfo);
    Load();

    // 플레이어 탱크
    player = new Tank;
    player->Init();
    playerSpawnPos = GetSpawnPos(tileInfo, ObjectType::PLAYER).back();
    player->SetPos(playerSpawnPos);
    player->SetTileMap(tileInfo);
    playerTankRect = player->GetShape();
    
    // 아이템
    mpItem = new Item;
    mpItem->Init();
    itemRect = mpItem->GetShape();

    return S_OK;
}

void BattleTest2::Update()
{
    //cout << boolalpha << "mpItem->GetExistItem() : " << mpItem->GetExistItem() << endl;

    // 타일 속성 확인용 코드
    for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
    {
        if (PtInRect(&(tileInfo[i].rc), g_ptMouse))
        {
            if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON)) // 디버그용
            {
                if (tileInfo[i].terrain == Terrain::WALL) cout << "WALL" << tileInfo[i].hp << endl;
                else if (tileInfo[i].playerSpawn) cout << "playerSpawn" << tileInfo[i].hp << endl;
                else if (tileInfo[i].enemySpawn) cout << "enemySpawn" << tileInfo[i].hp << endl;
                else if (tileInfo[i].itemSpawn) cout << "itemSpawn" << tileInfo[i].hp << endl;
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
    if (enemyMgr)
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
    if (tileInfo[609].terrain == Terrain::HQ_STEEL)
    {
        elapsedChange++;
        if (elapsedChange >= 300)
        {
            for (int i = 600; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
            {
                if (tileInfo[i].terrain == Terrain::HQ_STEEL)
                {
                    tileInfo[i].terrain = Terrain::HQ_WALL;
                    tileInfo[i].frameX = 8;
                    tileInfo[i].frameY = 0;
                    elapsedChange = 0;
                }
            }
        }
    }

    //적탱크의 상태가 IDLE일 때
    if (elapsedCount < 10000)
    {
        elapsedCount++;
        if (elapsedCount >= 300)
        {
            enemyMgr->TankState(ecTankState::MOVE);
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
                else if ((boomEffect[i].boom->GetCurrFrameX() == 3) && boomEffect[i].type == BoomType::BIG_BOOM)
                {
                    boomEffect[i].bigBoom->SetCurrFrameX(boomEffect[i].bigBoom->GetCurrFrameX() + 1);
                }
                boomEffect[i].elapsedCount = 0;
            }
        }
    }
}

void BattleTest2::Render(HDC hdc)
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

    // 미사일 타일 접촉
    AmmoMapCollision(boomEffect, player, tileInfo);

    // 미사일 탱크 접촉
    AmmoTankCollision(boomEffect, player, enemyMgr);

    // 폭발 이펙트 렌더
    for (int i = 0; i < BOOM_NUM; i++)
    {
        if (boomEffect[i].isRender)
        {
            boomEffect[i].boom->Render(hdc, boomEffect[i].boomPos.x, boomEffect[i].boomPos.y, boomEffect[i].boom->GetCurrFrameX(), boomEffect[i].boom->GetCurrFrameY(), 2.0f);

            break;
        }
    }
}

void BattleTest2::Release()
{
    // 플레이어 탱크
    SAFE_RELEASE(player);

    // 적 탱크
    SAFE_RELEASE(enemyMgr);
    
    // 아이템
    SAFE_RELEASE(mpItem);
}

void BattleTest2::Load(int loadIndex)
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

void BattleTest2::AmmoMapCollision(Boom* boom, Tank* tank, TILE_INFO* tile)
{
    for (int j = 0; j < tank->ammoCount; j++)
    {
        RECT ammoRect = tank->ammoPack[j].GetShape();

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
                else if ((tile[i].terrain == Terrain::STEEL) || (tile[i].terrain == Terrain::HQ_STEEL))
                {
                    tank->ammoPack[j].SetIsFire(false);
                    tank->ammoPack[j].SetPos(tank->GetPos());
                    tank->ammoPack[j].SetBodySize(0);
                }
            }
        }
    }
}

void BattleTest2::AmmoTankCollision(Boom* boom, Tank* player, EnemyManager* enemy)
{
    // 적 정보들을 가져온다.
    vector<Enemy*> vecEnemies = enemy->GetEnemies();
    vecEnemies.resize(enemy->GetEnemyMaxCount());
    AmmoManager ammoMgr;
    vector<Ammo*> vecAmmos;

    // 플레이어 정보들을 가져온다.
    RECT playerRect = player->GetShape();

    // 플레이어 미사일이 적이나 적 미사일에 히트했을 경우
    for (int i = 0; i < player->ammoCount; ++i)
    {
        RECT ammoRect = player->ammoPack[i].GetShape();
        for (int j = 0; j < vecEnemies.size(); ++j)
        {
            RECT enemyRect = vecEnemies[j]->GetShape();
            if (IntersectRect(&tempRect, &ammoRect, &enemyRect) && player->ammoPack[i].GetIsFire())    // 플레이어 미사일과 적 탱크가 충돌했을 경우
            {
                BoomAnimation(boom, BoomType::SMALL_BOOM, vecEnemies[j]->GetPos());
                vecEnemies[j]->SetIsAlive(false);
                vecEnemies[j]->SetTankState(ecTankState::DIE);
                player->ammoPack[i].SetIsFire(false);
                player->ammoPack[i].SetBodySize(0);
            }

            ammoMgr = vecEnemies[j]->GetAmmoManager();
            vecAmmos = ammoMgr.GetAmmos();
            for (int k = 0; k < vecAmmos.size(); ++k)
            {
                RECT enemyAmmoRect = vecAmmos[k]->GetShape();
                if (IntersectRect(&tempRect, &ammoRect, &enemyAmmoRect))  // 플레이어 미사일과 적 미사일이 충돌했을 경우
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

}

void BattleTest2::CollisionItem()
{
    RECT a;        
    if (mpItem->GetExistItem() == true)
    {
        if (IntersectRect(&a, &playerTankRect, &itemRect))
        {
            //cout << "아이템 접촉! !" << endl;
            //cout << "기능획득! !" << endl;
            FunctionItem();
            mpItem->SetExistItem(false);
        }
    }
}

void BattleTest2::FunctionItem()
{
    //헬멧
    if (mpItem->GetItemState() == ecFunctionItem::HELMET)
    {
        player->SetInvincible(true);
        player->SetElapsedInvincible(0);
    }
    //시계
    if (mpItem->GetItemState() == ecFunctionItem::WATCH)
    {
        //적탱크 일시정지
        enemyMgr->TankState(ecTankState::IDLE);
        elapsedCount = 0;
    }
    //삽
    if (mpItem->GetItemState() == ecFunctionItem::SHOVEL)
    {
        //HQ주변 타일 강철로
        for (int i = 600; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
        {
            if (tileInfo[i].terrain == Terrain::HQ_WALL)
            {
                tileInfo[i].terrain = Terrain::HQ_STEEL;
                tileInfo[i].frameX = 8;
                tileInfo[i].frameY = 2;
            }
        }
    }
    //별
    if (mpItem->GetItemState() == ecFunctionItem::STAR)
    {
        player->SetImgFrameY(player->GetImgFrameY() + 1);
        if (player->GetImgFrameY() >= 3)
        {
            player->SetImgFrameY(3);
        }
        if (player->GetImgFrameY() >= 2)
        {
            player->SetAmmoCount(2);
        }
    }
    //수류탄
    if (mpItem->GetItemState() == ecFunctionItem::GRENADE)
    {
        //나와있는 적 모두 죽임
        enemyMgr->IsAlive(false);
    }
    //탱크
    if (mpItem->GetItemState() == ecFunctionItem::TANK)
    {
        player->SetptLife(player->GetptLife() + 1);
    }
}

void BattleTest2::BoomAnimation(Boom* boom, BoomType type, POINTFLOAT pos)
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
