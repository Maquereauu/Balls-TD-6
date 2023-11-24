#include "BlastBullet.h"

BlastBullet::BlastBullet(float radius, float x, float y, float speed, int damage) : Bullet(radius, x,y,speed,damage)
{
	BlastZone = getRadius() * 10;
	GameManager::Get()->addToEntity(this);
};

void BlastBullet::onCollisionEnter(GameObject* object) 
{
	Blast = new Bullet(BlastZone, getPos().x, getPos().y, 0, getDamage());
	Blast->setPos(getPos(0.5).x - BlastZone, getPos(0.5).y - BlastZone);
	GameManager::Get()->addToEntity(GoLabel::Manstre,Blast);
	GameManager::Get()->addToEntity(Blast);
	_isDestroyed = true;
};	
