#pragma once

#include <string>

class AABBCollider;
class CircleCollider;

class Shape;

class Collider
{
private:
	// enum pour les cotés des colliders
	typedef enum sides
	{
		left,
		top,
		right,
		bottom
	};

public:
	float& _posX;
	float& _posY;

	Collider(float& posX, float& posY);

	bool colliding(Collider* o_OtherCollider); // Check witch method of children if there is collide
	std::string collidingSide(Collider* o_OtherCollider); // Check witch method of children the collide side

	virtual bool isColliding(const AABBCollider& o_AABBCollider) = 0; // method defined by children
	virtual bool isColliding(const CircleCollider& o_circleCollider) = 0; // method defined by children

	virtual std::string checkCollidingSide(const AABBCollider& o_AABBCollider) = 0; // method defined by children
	virtual std::string checkCollidingSide(const CircleCollider& o_circleCollider) = 0; // method defined by children
};
