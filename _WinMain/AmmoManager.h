#pragma once
#include "Config.h"
#include "GameEntity.h"

class GameObject;
class Ammo;
class AmmoManager : public GameEntity
{
private:
	vector<Ammo*> vecAmmos;
	vector<Ammo*>::iterator itAmmos;

	int ammoMaxCount = 1;

	GameObject* owner = nullptr;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void Fire();

	inline void SetOwner(GameObject* owner) { this->owner = owner; }
	void SetAmmoSpeed(float ammoSpeed);

	inline vector<Ammo*> GetAmmos() { return this->vecAmmos; }

	virtual ~AmmoManager() = default;
};

