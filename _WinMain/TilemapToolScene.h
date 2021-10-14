#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"

class Image;
class TilemapToolScene : public GameEntity
{
private:
	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TILE_COUNT_Y * SAMPLE_TILE_COUNT_X];
	TILE_INFO tileInfo[TILE_COUNT_Y * TILE_COUNT_X];
	Image* sampleImage;

	// 배경 이미지
	Image* backGround;

	SAMPLE_TILE_INFO	selectedSampleTile;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void Save(int saveIndex = 0);
	void Load(int loadIndex = 0);
};

