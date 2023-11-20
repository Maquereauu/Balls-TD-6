#include "Math.h"


Math::Vector2 Math::Vector2::upVector = Math::Vector2(0.f, -1.f);
Math::Vector2 Math::Vector2::downVector = Math::Vector2(0.f, 1.f);
Math::Vector2 Math::Vector2::leftVector = Math::Vector2(-1.f, 0.f);
Math::Vector2 Math::Vector2::rightVector = Math::Vector2(1.f, 0.f);

Math::Vector2 Math::Vector2::getNormalizeVector()
{
	float normal = (float)pow(_x, 2) + (float)pow(_y, 2);
	normal = pow(normal, 1 / 2.f);
	Math::Vector2 normalVector = Math::Vector2(x / normal, y / normal);

	return normalVector;
}

Math::Vector2::Vector2(float x, float  y) : sf::Vector2f(x, y), _x(this->x), _y(this->y)
{
}

Math::Vector2::Vector2() : Vector2(0.f, 0.f)
{
}


void Math::Vector2::setAll(float x, float y)
{
	_x = x;
	_y = y;
}

void Math::Vector2::normalizeVector()
{
	float normal = (float)pow(_x, 2) + (float)pow(_y, 2);
	normal = pow(normal, 1 / 2.f);

	_x = _x / normal;
	_y = _y / normal;
}

bool Math::Vector2::compareVector(Math::Vector2& vectorResult)
{
	if (_x == vectorResult._x && _y == vectorResult._y)
	{
		return true;
	}
	return false;
}

float Math::Vector2::scalarProduct(Math::Vector2& vector)
{
	return _x * vector._x + _y * vector._y;
}

float Math::Vector2::getAngle(Math::Vector2 vector)
{
	Math::Vector2 normalVector1 = this->getNormalizeVector();
	Math::Vector2 normalVector2 = vector.getNormalizeVector();

	float radian = acos(normalVector1.scalarProduct(normalVector2));

	return  (float)(radian * (180 / M_PI)); // envoie l'angle en degrès
}

void Math::Vector2::reBound(Math::Vector2* ballVector)
{
	if (this->compareVector(upVector))
	{
		ballVector->_x = -ballVector->_x;
	}
	else if (this->compareVector(rightVector))
	{
		ballVector->_y = -ballVector->_y;
	}
}

Math::Vector2 Math::Vector2::createVector(Math::Vector2 vector, float x1, float y1)
{
	return Math::Vector2::Vector2(x1 - vector._x, y1 - vector._y);
}