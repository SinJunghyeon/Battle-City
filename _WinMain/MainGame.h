#pragma once
#include "Config.h"
#include "GameEntity.h"

// �츮�� ������ ���� ����
class Image;
class MainGame : public GameEntity
{
private:
	// Ÿ�̸�
	HANDLE hTimer;

	// UI
	char text[128];

	int mousePosX;
	int mousePosY;
	int clickedMousePosX;
	int clickedMousePosY;

	// �����
	Image* backBuffer;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};