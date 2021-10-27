#pragma once
#include "GameEntity.h"

class Image;
class LoadingScene : public GameEntity
{
private:
	Image* backGround;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	virtual ~LoadingScene() = default;
};

