#include "BattleTest.h"
#include "Image.h"

HRESULT BattleTest::Init()
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

    Load();

    return S_OK;
}

void BattleTest::Update()
{
    // Ÿ�� �Ӽ� Ȯ�ο� �ڵ�
    for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
    {
        if (PtInRect(&(tileInfo[i].rc), g_ptMouse))
        {
            if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON)) // ����׿�
            {
                if (tileInfo[i].terrain == Terrain::WALL) cout << "WALL" << endl;
                else if (tileInfo[i].terrain == Terrain::STEEL) cout << "STEEL" << endl;
                else if (tileInfo[i].terrain == Terrain::ROAD) cout << "ROAD" << endl;
                else if (tileInfo[i].terrain == Terrain::HQ) cout << "HQ" << endl;
            }
        }
    }
}

void BattleTest::Render(HDC hdc)
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
}

void BattleTest::Release()
{
}

void BattleTest::Load(int loadIndex)
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