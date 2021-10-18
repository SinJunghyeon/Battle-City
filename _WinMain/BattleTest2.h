#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"

class GameObject;
class EnemyManager;
class Tank;
class Image;
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
    POINTFLOAT spawnPos;

    // ��
    EnemyManager* enemies;

    // �浹ó���� RECT
    RECT tempRect;

    // ����׿�
    POINTFLOAT tempPos;

public:
    HRESULT Init();
    void Update();
    void Render(HDC hdc);	// �����ε�
    void Release();

    void Load(int loadIndex = 0);

    void Collision(GameObject* tank, TILE_INFO* tile);
};

