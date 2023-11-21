#include "CircleCollider.h"

#include "AABBCollider.h"
#include "Math.h"

CircleCollider::CircleCollider(float& posX, float& posY, float& _sizeX, float& _sizeY) : _sizeX(_sizeX), _sizeY(_sizeY), Collider(posX, posY) {};

bool CircleCollider::isColliding(const AABBCollider& o_AABBCollider)
{
	//only works with squares
	float x = fabs(_posX + _sizeX / 2 - o_AABBCollider._posX - o_AABBCollider._sizeX / 2) - o_AABBCollider._sizeX / 2;
	float y = fabs(_posY + _sizeY / 2 - o_AABBCollider._posY - o_AABBCollider._sizeY / 2) - o_AABBCollider._sizeY / 2;

	if (x > 0) {
		if (y > 0) {
			if (x * x + y * y < _sizeX / 2 * _sizeX / 2)
			{
				//std::cout << "collide AABB to Circle" << std::endl;
				return true;
			}
		}
		else {
			if (x < _sizeX / 2)
			{
				//std::cout << "collide AABB to Circle" << std::endl;
				return true;
			}
		}
	}
	else {
		if (y < _sizeX / 2) {
			//std::cout << "collide AABB to Circle" << std::endl;
			return true;
		}
	}
	return false;
}
}


bool CircleCollider::isColliding(const CircleCollider& o_circleCollider)
{
	// ball collide ball
	if ((_posX + _sizeX < o_circleCollider._posX) || (o_circleCollider._posX + o_circleCollider._sizeX < _posX))
	{
		return false;
	}

	else if ((_posY + _sizeY < o_circleCollider._posY) || (o_circleCollider._posY + o_circleCollider._sizeY < _posY))
	{
		return false;
	}

	//std::cout << "collide Circle to Circle" << std::endl;
	return true;
}

std::string CircleCollider::checkCollidingSide(const AABBCollider& o_AABBCollider)
{
	Math::Vector2 centerToCenter((((o_AABBCollider._posX + (o_AABBCollider._sizeX / 2)) - (_posX + (_sizeX / 2)))) / ((_sizeX + o_AABBCollider._sizeX) / 2), (((o_AABBCollider._posY + (o_AABBCollider._sizeY / 2)) - (_posY + (_sizeY / 2)))) / ((_sizeY + o_AABBCollider._sizeY) / 2));
	//std::cout << (o_AABBCollider._posY + o_AABBCollider._sizeY / 2) << "/" << _posY << "/" << _radius << std::endl;
	//std::cout << std::abs(centerToCenter.x) << "/" << std::abs(centerToCenter.y) << std::endl;
	if (std::abs(centerToCenter.x) >= std::abs(centerToCenter.y)) {
		return (centerToCenter.x > 0) ? "left" : "right";
	}
	return (centerToCenter.y > 0) ? "top" : "bottom";
}

std::string CircleCollider::checkCollidingSide(const CircleCollider& o_circleCollider)
{
	Math::Vector2 centerToCenter((((o_circleCollider._posX + (o_circleCollider._sizeX / 2)) - (_posX + (_sizeX / 2)))) / ((_sizeX + o_circleCollider._sizeX) / 2), (((o_circleCollider._posY + (o_circleCollider._sizeY / 2)) - (_posY + (_sizeY / 2)))) / ((_sizeY + o_circleCollider._sizeY) / 2));
	//std::cout << (o_AABBCollider._posY + o_AABBCollider._sizeY / 2) << "/" << _posY << "/" << _radius << std::endl;
	//std::cout << std::abs(centerToCenter.x) << "/" << std::abs(centerToCenter.y) << std::endl;
	if (std::abs(centerToCenter.x) >= std::abs(centerToCenter.y)) {
		return (centerToCenter.x > 0) ? "left" : "right";
	}
	return (centerToCenter.y > 0) ? "top" : "bottom";
}