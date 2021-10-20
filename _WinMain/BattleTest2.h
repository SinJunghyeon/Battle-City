#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"
#include "Enemy.h"

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

    void AmmoMapCollision(Tank* tank, TILE_INFO* tile);
    void CollisionItem();
    void FunctionItem();
};

