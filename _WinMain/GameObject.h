#pragma once

// ������ ������� ������ ���� �⺻���� ������ �Ǵ� Ŭ����
// �ʱ�ȭ (�޸� �Ҵ�), 1ȸ�� ����
// ������Ʈ, ���������� �����Ӹ��� ����
// ���, ���������� �����Ӹ��� ����
// �޸� ����, 1ȸ�� ����

/*
	��� : �ߺ��Ǵ� �ڵ带 ���� �� �ִ�.
	�߻�ȭ : ���Ǽ��迡 �ִ� ��ü�� ���Ӱ�ü�� �ʿ��� �����͸� �߷��� ��.

	Ŭ���� �߻�ȭ : Ŭ���� �� ����Ǵ� ������� �߷��� ��.
*/

#include "GameEntity.h"
#include "Config.h"

class Image;
class GameObject : public GameEntity
{
//private:	// �ܺ� Ŭ������ �����Ű�� �ʴ´�.
protected:	// ��ӵ� Ŭ������ �����Ų��.
//public:		// ��� �ܺ� Ŭ������ �����Ų��.
	POINTFLOAT pos;
	RECT shape;
	float moveSpeed;
	int bodySize;

	MoveDir moveDir;

	Image* img;

public:
	void Move();

	// this�� nullptr�̴�. �ڵ������ �Լ��� ��ü�� ȣ�������� ��ü�� ����. ����
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline RECT GetShape() { return this->shape; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline int GetBodySize() { return this->bodySize; }
	inline void SetBodySize(int bodySize) { this->bodySize = bodySize; }
	inline MoveDir GetMoveDir() { return this->moveDir; }

	GameObject();
	~GameObject();
};

