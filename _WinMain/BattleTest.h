#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"

class Image;
class BattleTest : public GameEntity
{
private:
    TILE_INFO tileInfo[TILE_COUNT_Y * TILE_COUNT_X];

    // 타일 이미지
    Image* sampleImage;

    // 배경 이미지
    Image* backGround;

public:
    HRESULT Init();
    void Update();
    void Render(HDC hdc);	// 오버로딩
    void Release();

    void Load(int loadIndex = 0);
};

