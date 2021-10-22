#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"
#include "Enemy.h"

#define BOOM_NUM 10

enum class BoomType { SMALL_BOOM, BIG_BOOM };

struct Boom
{
    Image* boom;
    Image* bigBoom;
    bool isRender = false;
    int elapsedCount = 0;
    BoomType type = BoomType::SMALL_BOOM;
    POINTFLOAT boomPos = {};
};

class GameObject;
class EnemyManager;
class Tank;
class Image;
class Item;
class Ammo;
class BattleTest2 : public GameEntity
{
private:
    // 맵 타일
    TILE_INFO tileInfo[TILE_COUNT_Y * TILE_COUNT_X];

    // 타일 이미지
    Image* sampleImage;

    // 배경 이미지
    Image* backGround;

    // 폭발 이펙트
    Boom boomEffect[BOOM_NUM];

    // 플레이어
    Tank* player;
    POINTFLOAT playerSpawnPos;
    RECT playerTankRect;

    // 적
    EnemyManager* enemyMgr;

    // 충돌처리용 RECT
    RECT tempRect;

    // 디버그용
    POINTFLOAT tempPos;

    //아이템
    Item* mpItem;
    RECT itemRect;

    int elapsedChange = NULL;
    int elapsedCount = 10000;

    // UI
    int playerLife = 2;
    int destroyedEnemy[4] = {}; // 1 : 일반형  2 : 속도형   3 : 속사형   4 : 슈퍼탱크

public:
    HRESULT Init();
    void Update();
    void Render(HDC hdc);	// 오버로딩
    void Release();

    void Load(int loadIndex = 0);

    void AmmoMapCollision(Boom* boom, Tank* tank, TILE_INFO* tile);
    void AmmoTankCollision(Boom* boom, Tank* player, EnemyManager* enemy);
    void CollisionItem();
    void FunctionItem();

    void BoomAnimation(Boom* boom, BoomType type, POINTFLOAT pos);

    inline int* GetDestroyedEnemy() { return this->destroyedEnemy; }
};

