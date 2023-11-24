#pragma once
#include "Bullet.h"
class BlastBullet : public Bullet
{
private:
	float BlastZone;
	Bullet* Blast;
public:
	BlastBullet(float radius, float x, float y, float speed, int damage);
	void onCollisionEnter(GameObject* object) override;
};

