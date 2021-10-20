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
    // �� Ÿ��
    TILE_INFO tileInfo[TILE_COUNT_Y * TILE_COUNT_X];

    // Ÿ�� �̹���
    Image* sampleImage;

    // ��� �̹���
    Image* backGround;

    // ���� ����Ʈ
    Boom boomEffect[BOOM_NUM];

    // �÷��̾�
    Tank* player;
    POINTFLOAT playerSpawnPos;
    RECT playerTankRect;

    // ��
    EnemyManager* enemyMgr;

    // �浹ó���� RECT
    RECT tempRect;

    // ����׿�
    POINTFLOAT tempPos;

    //������
    Item* mpItem;
    RECT itemRect;

public:
    HRESULT Init();
    void Update();
    void Render(HDC hdc);	// �����ε�
    void Release();

    void Load(int loadIndex = 0);

    void AmmoMapCollision(Boom* boom, Tank* tank, TILE_INFO* tile);
    void CollisionItem();
    void FunctionItem();

    void BoomAnimation(Boom* boom, BoomType type, POINTFLOAT pos);
};

