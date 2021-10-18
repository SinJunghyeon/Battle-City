#include "BattleTest2.h"
#include "Image.h"
#include "Tank.h"
#include "EnemyManager.h"

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

    Load();

    // 플레이어 탱크
    player = new Tank;
    player->Init();
    spawnPos = GetSpawnPos(tileInfo, ObjectType::PLAYER).back();
    player->SetPos(spawnPos);

    return S_OK;
}

void BattleTest2::Update()
{
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
    Collision(player, tileInfo);
    player->Update();

    if (tempPos.x != player->GetPos().x || tempPos.y != player->GetPos().y)
    {
        cout << "x : " << player->GetPos().x << " y : " << player->GetPos().y << endl;
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

            sampleImage->Render(hdc,
                tileInfo[i * TILE_COUNT_X + j].rc.left + TILE_SIZE / 2,
                tileInfo[i * TILE_COUNT_X + j].rc.top + TILE_SIZE / 2,
                tileInfo[i * TILE_COUNT_X + j].frameX,
                tileInfo[i * TILE_COUNT_X + j].frameY);

            /* Rectangle(hdc, tileInfo[i * TILE_COUNT_X + j].rc.left,
                 tileInfo[i * TILE_COUNT_X + j].rc.top,
                 tileInfo[i * TILE_COUNT_X + j].rc.right,
                 tileInfo[i * TILE_COUNT_X + j].rc.bottom);*/
        }
    }

    // 플레이어 탱크
    player->Render(hdc);
}

void BattleTest2::Release()
{
    // 플레이어 탱크
    player->Release();
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

void BattleTest2::Collision(GameObject* tank, TILE_INFO* tile)
{
    POINTFLOAT pos; // SetPos를 사용하기 위해 임시로 만든 변수
    pos.x = tank->GetPos().x;
    pos.y = tank->GetPos().y;

    int moveSpeed = tank->GetMoveSpeed();
    for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
    {
        if (IntersectRect(&tempRect, &tank->GetShape(), &tile[i].rc))
        {
            if ((tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::STEEL) || (tile[i].terrain == Terrain::HQ_WALL) || (tile[i].terrain == Terrain::HQ_STEEL))
            {
                switch (tank->GetMoveDir())
                {
                case MoveDir::DOWN:
                    pos.y -= (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime());
                    tank->SetPos(pos);
                    break;
                case MoveDir::UP:
                    pos.y += (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime());
                    tank->SetPos(pos);
                    break;
                case MoveDir::LEFT:
                    pos.x += (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime());
                    tank->SetPos(pos);
                    break;
                case MoveDir::RIGHT:
                    pos.x -= (moveSpeed * TimerManager::GetSingleton()->GetDeltaTime());
                    tank->SetPos(pos);
                    break;
                default:
                    break;
                }
            }
        }
    }
}
