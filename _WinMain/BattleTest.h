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
    // �� Ÿ��
    TILE_INFO tileInfo[TILE_COUNT_Y * TILE_COUNT_X];

    // Ÿ�� �̹���
    Image* sampleImage;

    // ��� �̹���
    Image* backGround;

    // �÷��̾�
    Tank* player;
    POINTFLOAT spawnPos;
    RECT playerTankRect;

    // ��
    EnemyManager* enemies;

    // �浹ó���� RECT
    RECT tempRect;

    // ����׿�
    POINTFLOAT tempPos;

    //������
    Item* mpItem;
    RECT itemRect;

    // Ÿ�� ����
    TILE_INFO* tiles;

public:
    HRESULT Init();
    void Update();
    void Render(HDC hdc);	// �����ε�
    void Release();

    void Load(int loadIndex = 0);

    void Collision(GameObject* tank, TILE_INFO* tile);
    void CollisionItem();
    void FunctionItem();	
    
    // Ÿ�� ������ �޾ƿ��� �Լ�
    inline void SetTileMap(TILE_INFO* tiles) { this->tiles = tiles; }
};

