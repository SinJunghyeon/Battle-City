#pragma once
#include "Config.h"
#include "Singleton.h"

class DestroyCountManager : public Singleton<DestroyCountManager>
{
private:
	int* destroyCount;

public:
	void Release() { SAFE_DELETE(destroyCount) };

	inline void SetDestroyCount(int* destroyCount) { this->destroyCount = destroyCount; }
	inline int* GetDestroyCount() { return this->destroyCount; }
	virtual ~DestroyCountManager() = default;
};