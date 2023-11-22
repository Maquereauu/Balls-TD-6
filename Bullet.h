#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
private:
	int Damage;
	GameObject* Target;
	float speed;

public:
	std::string _side;

	//Bullet();
	Bullet(float radius, float x, float y, float speed, int _Damage, GameObject* _Target);
	float getRadius();
	float getSpeed();
	float getDamage();
	GameObject* getTarget();
	//void onCollisionEnter(GameObject* object) override;
};
