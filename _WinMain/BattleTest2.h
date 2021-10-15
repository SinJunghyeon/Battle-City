#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"

class EnemyManager;
class Tank;
class Image;
class BattleTest2 : public GameEntity
{
private:
    // 맵 타일
    TILE_INFO tileInfo[TILE_COUNT_Y * TILE_COUNT_X];

    // 타일 이미지
    Image* sampleImage;

    // 배경 이미지
    Image* backGround;

    // 플레이어
    Tank* player;

    // 적
    EnemyManager* enemies;

public:
    HRESULT Init();
    void Update();
    void Render(HDC hdc);	// 오버로딩
    void Release();

    void Load(int loadIndex = 0);


};

