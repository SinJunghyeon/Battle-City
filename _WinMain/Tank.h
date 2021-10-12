#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"

class Tank : public GameObject	// ��Ӱ���
{
public:
	POINTFLOAT barrelEnd;
	float barrelSize;
	float barrelAngle;

	int ammoCount;
	Ammo* ammoPack;
	//Ammo ammo[ammoCount];

	MoveDir moveDir;

	bool isAlive;


public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void RotateBarrelAngle(float rotateAngle);
	void Fire();
	void Reload();
	void ProcessInputKey();

	// �ǽ�3. ��ũ�� �����¿�(WASD)�� ����������.
	void Move(MoveDir dir);

	inline void SetBarrelAngle(float angle) { this->barrelAngle = angle; }
	inline void SetIsAlive(bool alive) { this->isAlive = alive; }

	Tank();
	~Tank();
};

