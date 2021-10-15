#pragma once
#include "Config.h"
#include "GameEntity.h"

class ButtonFunction;
class Button;
class Image;
class TitleScene : public GameEntity
{
private:
	
	HANDLE timeLate;	//������� �ʱ�ȭ�� �۵����� �ʾƼ� cpp�� �ʱ�ȭ

	Image* pbackGround = nullptr;
	Image* pSelectIcon = nullptr;

	LPARGUMENT_PTR arg;

	int iconPosY[2] = { WIN_SIZE_Y * 3 / 5, WIN_SIZE_Y * 2 / 3 };
	int iconPosNum = 0;

	int countFrameY = WIN_SIZE_Y + WIN_SIZE_Y / 2;
	int selectIcon = 7;
	bool bIsSceneIcon = false;	//�÷��̾�� ������ ����
	int elapsedCount=0;

	int textNum = 1;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void SetText(int textNum) { this->textNum; }
	int GetTextNum() { return this->textNum; }
};