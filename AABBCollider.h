#pragma once

#include "Collider.h"

#include <string>
#include <iostream>

class CircleCollider;

class AABBCollider : public Collider
{
public:
	float& _sizeX;
	float& _sizeY;

	AABBCollider(float& posX, float& posY, float& sizeX, float& sizeY);

	bool isColliding(const AABBCollider& o_AABBCollider) override; // Collide with AABB
	bool isColliding(const CircleCollider& o_circleCollider) override; // Collide with Circle

	std::string checkCollidingSide(const AABBCollider& o_AABBCollider) override; // Collide side with AABB
	std::string checkCollidingSide(const CircleCollider& o_circleCollider) override; // Collide side with AABB
};
