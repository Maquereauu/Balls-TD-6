#pragma once
#include "Bullet.h"
class BlastBullet : public Bullet
{
private:
	float BlastZone;

public:
	BlastBullet();
	void onCollisionEnter(GameObject* object) override;
};

