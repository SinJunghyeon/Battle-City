#pragma once
#include "Config.h"
#include "GameEntity.h"

class Image;
class GameOverScene : public GameEntity
{
private:
	Image* gameOver = nullptr;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

