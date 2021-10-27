#pragma once
#include "Config.h"
#include "GameEntity.h"

class Image;
class StageScene : public GameEntity
{
private:
	Image* stageImage = nullptr;
	Image* stageNum = nullptr;
	Image* background = nullptr;
	Image* background2 = nullptr;
	
	int stageImageSizeX = 37 * 5;
	int stageImageSizeY = 7 * 5;

	int startTopImagePosY = -(WIN_SIZE_Y / 2);
	int startBottomImagePosY = WIN_SIZE_Y + WIN_SIZE_Y / 2;

	bool isAnimation = true;

	int stageN = 1;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	inline int GetStageNum() { return this->stageN; }
	inline void SetStageNum(int num) { this->stageN = num; }

	virtual ~StageScene() = default;
};

