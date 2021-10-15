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
    // �� Ÿ��
    TILE_INFO tileInfo[TILE_COUNT_Y * TILE_COUNT_X];

    // Ÿ�� �̹���
    Image* sampleImage;

    // ��� �̹���
    Image* backGround;

    // �÷��̾�
    Tank* player;

    // ��
    EnemyManager* enemies;

public:
    HRESULT Init();
    void Update();
    void Render(HDC hdc);	// �����ε�
    void Release();

    void Load(int loadIndex = 0);


};

