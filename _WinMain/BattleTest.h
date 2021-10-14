#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"

class Image;
class BattleTest : public GameEntity
{
private:
    TILE_INFO tileInfo[TILE_COUNT_Y * TILE_COUNT_X];

    // Ÿ�� �̹���
    Image* sampleImage;

    // ��� �̹���
    Image* backGround;

public:
    HRESULT Init();
    void Update();
    void Render(HDC hdc);	// �����ε�
    void Release();

    void Load(int loadIndex = 0);
};

