#include "BattleTest2.h"
#include "Image.h"
#include "Tank.h"
#include "EnemyManager.h"
#include "Item.h"
#include "Ammo.h"

HRESULT BattleTest2::Init()
{
    // 타일 맵 이미지
    sampleImage = ImageManager::GetSingleton()->AddImage("Image/BattleCity/SamlpTile1.bmp",
        220, 220, 11, 11, true, RGB(255, 0, 255));
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

    // 적 매니저
    enemyMgr = new EnemyManager;
    enemyMgr->Init();
    
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

    // 미사일 타일 접촉
    AmmoMapCollision(player, tileInfo);
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

            sampleImage->Render(hdc,
                tileInfo[i * TILE_COUNT_X + j].rc.left + TILE_SIZE / 2,
                tileInfo[i * TILE_COUNT_X + j].rc.top + TILE_SIZE / 2,
                tileInfo[i * TILE_COUNT_X + j].frameX,
                tileInfo[i * TILE_COUNT_X + j].frameY);

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

void BattleTest2::AmmoMapCollision(Tank* tank, TILE_INFO* tile)
{
    POINTFLOAT pos;
    pos.x = 0;
    pos.y = 0;
    for (int j = 0; j < tank->ammoCount; j++)
    {
        RECT TankRect = tank->ammoPack[j].GetShape();
        //cout << "battletest2 pos.x : " << tank->ammoPack[j].GetPos().x << endl;
        //cout << "battletest2 pos.y : " << tank->ammoPack[j].GetPos().y << endl;
        for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
        {
            if (IntersectRect(&tempRect, &TankRect, &tile[i].rc)) // Ammo랑 Tile이 충돌하면
            {
                if ((tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::HQ_WALL)) // 충돌한 Tile이 벽일때
                {
                    tank->ammoPack[j].SetIsFire(false);
                    tank->ammoPack[j].SetPos(pos);
                    if (tile[i].hp == 1) // 파괴된 벽인 경우
                    {
                        tile[i].frameX = 10;
                        tile[i].frameY = 10; // ROAD로 바꾼다.
                    }
                    else
                    {
                        tile[i].hp--;
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
                }
            }
        }
    }
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

    }
    //삽
    if (mpItem->GetItemState() == ecFunctionItem::SHOVEL)
    {

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

    }
    //탱크
    if (mpItem->GetItemState() == ecFunctionItem::TANK)
    {
        player->SetptLife(player->GetptLife() + 1);
    }
}
