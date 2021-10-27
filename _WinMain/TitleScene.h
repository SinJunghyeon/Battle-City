#pragma once
#include "Config.h"
#include "GameEntity.h"

class Image;
class TitleScene : public GameEntity
{
private:
	
	HANDLE timeLate;	// ������� �ʱ�ȭ�� �۵����� �ʾƼ� cpp�� �ʱ�ȭ

	Image* backGround = nullptr;
	Image* selectIcon = nullptr;

	int iconPosY[2] = { WIN_SIZE_Y * 12/21, WIN_SIZE_Y * 13 / 20 };
	int iconPosArr = 0;

	int countFrameY = WIN_SIZE_Y + WIN_SIZE_Y / 2;
	int iconFrameX = 7;
	bool bIsSceneIcon = false;	// �÷��̾�� ������ ����

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	virtual ~TitleScene() = default;
};