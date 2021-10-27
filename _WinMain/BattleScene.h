#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"
#include "Enemy.h"
#include "StageScene.h"

#define BOOM_NUM 30

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

class StageScene;
class GameObject;
class EnemyManager;
class Tank;
class Image;
class Item;
class Ammo;
class BattleScene : public GameEntity
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
    vector<Enemy*> vecEnemies;

    // �浹ó���� RECT
    RECT tempRect;

    // ����׿�
    POINTFLOAT tempPos;

    // ������
    Item* mpItem;
    RECT itemRect;

    int elapsedChange = NULL;;
    int elapsedCount = 1005;

    // UI
    int UIposX = TILE_SIZE * TILE_COUNT_X + 120;
    int destroyedEnemy[4] = {}; // 1 : �Ϲ���  2 : �ӵ���   3 : �ӻ���   4 : ������ũ
    int iconSize = 30;
    int destroyedEnemyCount = 0;

    Image* enemyIcon;           // ���ʹ� ��ũ
    int enemyCount;

    Image* P1LifeImage;
    int playerLife=2;

    Image* numberText;

    Image* stageFlag;
    StageScene stagescene;

    //���� ���� �̹���
    Image* gameOverImg;
    int gameOverPosY = WIN_SIZE_Y * 3 / 2;

    // HQ �ı� ����
    bool isHQDestroyed = false;

    int elapsedEnding = NULL;
 

public:
    virtual HRESULT Init() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

    void Load(int loadIndex = 0);

    void PlayerAmmoMapCollision(Boom* boom, Tank* tank, TILE_INFO* tile);
    void EnemyAmmoMapCollision(Boom* boom, Enemy* enemy, TILE_INFO* tile);
    //void EnemyCollision();
    void AmmoTankCollision(Boom* boom, Tank* player);
    void CollisionItem();
    void FunctionItem(Boom* boom);

    void BoomAnimation(Boom* boom, BoomType type, POINTFLOAT pos);

    virtual ~BattleScene() = default;
};

