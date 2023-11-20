#pragma once

#include "Collider.h"

#include <string>

class AABBCollider;

class CircleCollider : public Collider
{
public:
	float& _sizeX;
	float& _sizeY;

	CircleCollider(float& posX, float& posY, float& _sizeX, float& _sizeY);

	bool isColliding(const AABBCollider& o_AABBCollider) override; // Collide with AABB
	bool isColliding(const CircleCollider& o_circleCollider) override; // Collide with Circle

	std::string checkCollidingSide(const AABBCollider& o_AABBCollider) override; // Collide side with AABB
	std::string checkCollidingSide(const CircleCollider& o_circleCollider) override; // Collide side with Circle
};