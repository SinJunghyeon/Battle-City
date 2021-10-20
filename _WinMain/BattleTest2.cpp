#include "BattleTest2.h"
#include "Image.h"
#include "Tank.h"
#include "EnemyManager.h"
#include "Item.h"
#include "Ammo.h"

HRESULT BattleTest2::Init()
{
    // Ÿ�� �� �̹���
    sampleImage = ImageManager::GetSingleton()->AddImage("Image/BattleCity/SamlpTile1.bmp",
        220, 220, 11, 11, true, RGB(255, 0, 255));
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

    // �� �Ŵ���
    enemyMgr = new EnemyManager;
    enemyMgr->Init();
    
    Load();

    // �÷��̾� ��ũ
    player = new Tank;
    player->Init();
    playerSpawnPos = GetSpawnPos(tileInfo, ObjectType::PLAYER).back();
    player->SetPos(playerSpawnPos);
    player->SetTileMap(tileInfo);
    playerTankRect = player->GetShape();
    
    // ������
    mpItem = new Item;
    mpItem->Init();
    itemRect = mpItem->GetShape();

    return S_OK;
}

void BattleTest2::Update()
{
    //cout << boolalpha << "mpItem->GetExistItem() : " << mpItem->GetExistItem() << endl;

    // Ÿ�� �Ӽ� Ȯ�ο� �ڵ�
    for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
    {
        if (PtInRect(&(tileInfo[i].rc), g_ptMouse))
        {
            if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON)) // ����׿�
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

    // �÷��̾� ��ũ
    tempPos = player->GetPos();
    player->Update();
    //if (tempPos.x != player->GetPos().x || tempPos.y != player->GetPos().y)
    //{
    //    cout << "x : " << player->GetPos().x << " y : " << player->GetPos().y << endl;
    //}
    playerTankRect = player->GetShape();

    //�� ��ũ
    if (enemyMgr)
        enemyMgr->Update();

    //������
    mpItem->Update();
    if (mpItem->GetExistItem() == true)
    {
        itemRect = mpItem->GetShape();
    }

    //�÷��̾� ������ ����
    CollisionItem();

    // �̻��� Ÿ�� ����
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
}

void BattleTest2::Release()
{
    // �÷��̾� ��ũ
    SAFE_RELEASE(player);

    // �� ��ũ
    SAFE_RELEASE(enemyMgr);
    
    // ������
    SAFE_RELEASE(mpItem);
}

void BattleTest2::Load(int loadIndex)
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

void BattleTest2::AmmoMapCollision(Tank* tank, TILE_INFO* tile)
{
    POINTFLOAT pos;
    pos.x = 0;
    pos.y = 0;
    for (int j = 0; j < tank->ammoCount; j++)
    {
        cout << "battletest2 pos.x : " << tank->ammoPack[j].GetPos().x << endl;
        cout << "battletest2 pos.y : " << tank->ammoPack[j].GetPos().y << endl;
        for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
        {
            if (IntersectRect(&tempRect, &tank->ammoPack[j].GetShape(), &tile[i].rc)) // Ammo�� Tile�� �浹�ϸ�
            {
                if ((tile[i].terrain == Terrain::WALL) || (tile[i].terrain == Terrain::HQ_WALL)) // �浹�� Tile�� ���϶�
                {
                    tank->ammoPack[j].SetIsFire(false);
                    tank->ammoPack[j].SetPos(pos);
                    if (tile[i].hp == 1) // �ı��� ���� ���
                    {
                        tile[i].frameX = 10;
                        tile[i].frameY = 10; // ROAD�� �ٲ۴�.
                    }
                    else
                    {
                        tile[i].hp--;
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
            //cout << "������ ����! !" << endl;
            //cout << "���ȹ��! !" << endl;
            FunctionItem();
            mpItem->SetExistItem(false);
        }
    }
}

void BattleTest2::FunctionItem()
{
    //���
    if (mpItem->GetItemState() == ecFunctionItem::HELMET)
    {
        player->SetInvincible(true);
        player->SetElapsedInvincible(0);
    }
    //�ð�
    if (mpItem->GetItemState() == ecFunctionItem::WATCH)
    {

    }
    //��
    if (mpItem->GetItemState() == ecFunctionItem::SHOVEL)
    {

    }
    //��
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
    //����ź
    if (mpItem->GetItemState() == ecFunctionItem::GRENADE)
    {

    }
    //��ũ
    if (mpItem->GetItemState() == ecFunctionItem::TANK)
    {
        player->SetptLife(player->GetptLife() + 1);
    }
}
