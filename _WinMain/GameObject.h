#pragma once

#include "Config.h"
#include "GameEntity.h"
#include "MapConfig.h"

enum class ecTankState { IDLE, MOVE, FIRE, DAMAGED, DIE };

class Image;
class GameObject : public GameEntity
{
protected:
	POINTFLOAT pos;
	RECT shape;
	float moveSpeed;
	int bodySize;

	MoveDir moveDir;

	Image* img;

	// 타일 정보
	TILE_INFO* tile;
  
public:
	void Move();

	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }

	inline RECT GetShape() { return this->shape; }
	inline void SetShape(RECT shape) { this->shape = shape; }
	
	// 21.10.18 WJ - GetMoveSpeed() 추가했습니다.
	inline float GetMoveSpeed() { return this->moveSpeed; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	

	inline int GetBodySize() { return this->bodySize; }
	inline void SetBodySize(int bodySize) { this->bodySize = bodySize; }

	inline MoveDir GetMoveDir() { return this->moveDir; }
	inline void SetMoveDir(MoveDir moveDir) { this->moveDir = moveDir; }

	GameObject();
	virtual ~GameObject() = default;
};

