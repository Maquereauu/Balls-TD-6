#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
private:
	int _damage;
	float _speed;
	GameObject* _target;
public:
	//std::string _side;

	//Bullet();
	Bullet(float radius, float x, float y, float speed, int _Damage);
	float getRadius();
	float getSpeed();
	float getDamage();
	GameObject* getTarget();
	void setTarget(GameObject* gameObject);
	void setVectorTowardsTarget();
	void onCollisionEnter(GameObject* object) override;
	//void onCollisionEnter(GameObject* object) override;
};
