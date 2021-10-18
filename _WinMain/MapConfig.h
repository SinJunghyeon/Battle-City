#pragma once
enum class Terrain { ROAD, WALL, WATER, GRASS, STEEL, ICE, HQ, End };

#define TILE_SIZE	20
#define TILE_COUNT_X	26
#define TILE_COUNT_Y	26
#define SAMPLE_TILE_COUNT_X	11
#define SAMPLE_TILE_COUNT_Y	11

typedef struct tagSampleTile
{
	RECT rc;
    int frameX = 0;
    int frameY = 0;
} SAMPLE_TILE_INFO;

typedef struct tagTile
{
	Terrain terrain = Terrain::WALL;
	RECT rc;
    int frameX = 0;
    int frameY = 0;
    int hp = 0;
    bool playerSpawn = false;
    bool enemySpawn = false;
    bool itemSpawn = false;
} TILE_INFO;

inline void SetTerrain(TILE_INFO* rc)
{
    if (0 <= rc->frameX && rc->frameX <= 1)
    {
        if (0 <= rc->frameY && rc->frameY <= 1)
        {
            rc->terrain = Terrain::WALL;
            rc->hp = 2;
        }
        else if (2 <= rc->frameY && rc->frameY <= 3)
        {
            rc->terrain = Terrain::STEEL;
            rc->hp = 1;
        }
        else if (4 <= rc->frameY && rc->frameY <= 7)
        {
            rc->terrain = Terrain::WATER;
            rc->hp = 0;
        }

    }
    else if (4 <= rc->frameY && rc->frameY <= 5)
    {
        if (2 <= rc->frameX && rc->frameX <= 3)
        {
            rc->terrain = Terrain::GRASS;
            rc->hp = 0;
        }
        else if (4 <= rc->frameX && rc->frameX <= 5)
        {
            rc->terrain = Terrain::ICE;
            rc->hp = 0;
        }
        else if (6 <= rc->frameX && rc->frameX <= 7)
        {
            rc->terrain = Terrain::HQ;
            rc->hp = 0;
        }
    }
    else if (0 <= rc->frameX && rc->frameX <= 4 && rc->frameY == 8)
    {
        rc->terrain = Terrain::WALL;
        rc->hp = 2;
    }
    else
    {
        rc->terrain = Terrain::ROAD;
        rc->hp = 0;
    }
}

inline void SetSpawn(TILE_INFO* rc)
{
    if (rc->frameX == 2)
    {
        if (rc->frameY == 1)
        {
            rc->playerSpawn = true;
        }
        else if (rc->frameY == 2)
        {
            rc->enemySpawn = true;
        }
        else if (rc->frameY == 3)
        {
            rc->itemSpawn = true;
        }
    }
}