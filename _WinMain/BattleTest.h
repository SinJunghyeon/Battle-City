#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"

class GameObject;
class EnemyManager;
class Tank;
class Image;
class Item;
class BattleTest : public GameEntity
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
    POINTFLOAT spawnPos;
    RECT playerTankRect;

    // 적
    EnemyManager* enemyMgr;
    POINTFLOAT enemySpawnPos;

    // 충돌처리용 RECT
    RECT tempRect;

    // 디버그용
    POINTFLOAT tempPos;

    //아이템
    Item* mpItem;
    RECT itemRect;

    int elapsedChange = NULL;

    int elapsedCount = 10000;

public:
    HRESULT Init();
    void Update();
    void Render(HDC hdc);	// 오버로딩
    void Release();

    void Load(int loadIndex = 0);

    void Collision(GameObject* tank, TILE_INFO* tile);
    void CollisionItem();
    void FunctionItem();
};

