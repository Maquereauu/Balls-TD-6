#include "AABBCollider.h"
#include "CircleCollider.h"
#include "Math.h"

AABBCollider::AABBCollider(float& posX, float& posY, float& sizeX, float& sizeY) : _sizeX(sizeX), _sizeY(sizeY), Collider(posX, posY) {};

bool AABBCollider::isColliding(const AABBCollider& o_AABBCollider)
{
	// rectangle collide rectangle
	if ((_posX + _sizeX < o_AABBCollider._posX) || (o_AABBCollider._posX + o_AABBCollider._sizeX < _posX))
	{
		return false;
	}

	else if ((_posY + _sizeY < o_AABBCollider._posY) || (o_AABBCollider._posY + o_AABBCollider._sizeY < _posY))
	{
		return false;
	}

	//std::cout << "collide AABB to AABB" << std::endl;
	return true;
}

bool AABBCollider::isColliding(const CircleCollider& o_circleCollider)
{
	//only works with squares
	float x = fabs(o_circleCollider._posX + o_circleCollider._sizeX / 2 - _posX - _sizeX / 2) - _sizeX / 2;
	float y = fabs(o_circleCollider._posY + o_circleCollider._sizeY / 2 - _posY - _sizeY / 2) - _sizeY / 2;

	if (x > 0) {
		if (y > 0) {
			if (x * x + y * y < o_circleCollider._sizeX / 2 * o_circleCollider._sizeX / 2)
			{
				//std::cout << "collide AABB to Circle" << std::endl;
				return true;
			}
		}
		else {
			if (x < o_circleCollider._sizeX / 2)
			{
				//std::cout << "collide AABB to Circle" << std::endl;
				return true;
			}
		}
	}
	else {
		if (y < o_circleCollider._sizeX / 2) {
			//std::cout << "collide AABB to Circle" << std::endl;
			return true;
		}
	}
	return false;
}

std::string AABBCollider::checkCollidingSide(const AABBCollider& o_AABBCollider)
{
	/* Renvoie le coté sur lequel on collide à partir des dimensions du vecteur entre les deux centres des GameObjects */
	Math::Vector2 centerToCenter((((o_AABBCollider._posX + (o_AABBCollider._sizeX / 2)) - (_posX + (_sizeX / 2)))) / ((_sizeX + o_AABBCollider._sizeX) / 2), (((o_AABBCollider._posY + (o_AABBCollider._sizeY / 2)) - (_posY + (_sizeY / 2)))) / ((_sizeY + o_AABBCollider._sizeY) / 2));
	if (std::abs(centerToCenter.x) >= std::abs(centerToCenter.y)) {
		return (centerToCenter.x > 0) ? "left" : "right";
	}
	return (centerToCenter.y > 0) ? "top" : "bottom";
}

std::string AABBCollider::checkCollidingSide(const CircleCollider& o_circleCollider)
{
	/* Renvoie le coté sur lequel on collide à partir des dimensions du vecteur entre les deux centres des GameObjects */
	Math::Vector2 centerToCenter((((o_circleCollider._posX + (o_circleCollider._sizeX / 2)) - (_posX + (_sizeX / 2)))) / ((_sizeX + o_circleCollider._sizeX) / 2), (((o_circleCollider._posY + (o_circleCollider._sizeY / 2)) - (_posY + (_sizeY / 2)))) / ((_sizeY + o_circleCollider._sizeY) / 2));
	//std::cout << (_posY + _sizeY / 2) << "/" << o_circleCollider._posY << "/" << o_circleCollider._sizeX << std::endl;
	//std::cout << std::abs(centerToCenter.x) << "/" << std::abs(centerToCenter.y) << std::endl;
	if (std::abs(centerToCenter.x) >= std::abs(centerToCenter.y)) {
		return (centerToCenter.x > 0) ? "left" : "right";
	}
	return (centerToCenter.y > 0) ? "top" : "bottom";
}