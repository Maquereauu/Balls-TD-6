#include "BlastBullet.h"

BlastBullet::BlastBullet() : Bullet(getRadius(), getPos().x, getPos().y, getSpeed(), getDamage())
{
	BlastZone = getRadius() * 3;
};

void BlastBullet::onCollisionEnter(GameObject* object) 
{
	Bullet Blast(BlastZone, getPos().x, getPos().y, 0 ,6);
};