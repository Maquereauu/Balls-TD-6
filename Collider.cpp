#include "Collider.h"

#include <iostream>

#include "AABBCollider.h"
#include "CircleCollider.h"

Collider::Collider(float& posX, float& posY) : _posX(posX), _posY(posY) {}; // constructor


bool Collider::colliding(Collider* o_OtherCollider)
{
	// Check which method of children if there is collide

	/* verification which child is used */
	const AABBCollider* AABB = dynamic_cast<AABBCollider*>(o_OtherCollider);
	const CircleCollider* circle = dynamic_cast<CircleCollider*>(o_OtherCollider);

	if (AABB != nullptr)
	{
		return isColliding(*AABB);
	}
	else if (circle != nullptr)
	{
		return isColliding(*circle);
	}
	else
	{
		return false;
	}

}

std::string Collider::collidingSide(Collider* o_OtherCollider)
{
	// Check which method of children the collide side

	/* verification which child is used */
	const AABBCollider* AABB = dynamic_cast<AABBCollider*>(o_OtherCollider);
	const CircleCollider* circle = dynamic_cast<CircleCollider*>(o_OtherCollider);

	if (AABB != nullptr)
	{
		return checkCollidingSide(*AABB);
	}
	else if (circle != nullptr)
	{
		return checkCollidingSide(*circle);
	}
	else
	{
		return "none";
	}


}