#pragma once

// 앞으로 만들어질 게임의 가장 기본적인 구조가 되는 클래스
// 초기화 (메모리 할당), 1회만 진행
// 업데이트, 지속적으로 프레임마다 진행
// 출력, 지속적으로 프레임마다 진행
// 메모리 해제, 1회만 진행

/*
	상속 : 중복되는 코드를 줄일 수 있다.
	추상화 : 현실세계에 있는 객체를 게임객체에 필요한 데이터만 추려낸 것.

	클래스 추상화 : 클래스 간 공통되는 내용들을 추려낸 것.
*/

#include "GameEntity.h"
#include "Config.h"

class Image;
class GameObject : public GameEntity
{
//private:	// 외부 클래스에 노출시키지 않는다.
protected:	// 상속된 클래스에 노출시킨다.
//public:		// 모든 외부 클래스에 노출시킨다.
	POINTFLOAT pos;
	RECT shape;
	float moveSpeed;
	int bodySize;

	MoveDir moveDir;

	Image* img;

public:
	void Move();

	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }

	inline RECT GetShape() { return this->shape; }
	
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	
	inline int GetBodySize() { return this->bodySize; }

	inline void SetBodySize(int bodySize) { this->bodySize = bodySize; }

	inline MoveDir GetMoveDir() { return this->moveDir; }
	inline void SetMoveDir(MoveDir moveDir) { this->moveDir = moveDir; }

	GameObject();
	~GameObject();
};

