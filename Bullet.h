#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	std::string _side;

	Bullet();
	Bullet(float radius, float x, float y, float speed);

	float getRadius();
	void onCollisionEnter(GameObject* object) override;
};

