#include "GameObject.h"

#include<SFML/Graphics.hpp>

#include "Collider.h"
#include "AABBCollider.h"
#include "CircleCollider.h"

GameObject::GameObject(float sizeX, float sizeY, float posX, float posY, float speed, int iLabel)
{
	_sizeX = sizeX;
	_sizeY = sizeY;
	_posX = posX;
	_posY = posY;
	_isDestroyed = false;
	_collider = new AABBCollider(_posX, _posY, _sizeX, _sizeY);

	sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(_sizeX, _sizeY));
	rectangle->setFillColor(sf::Color::Blue);
	rectangle->setPosition(_posX, _posY);
	_graphic = rectangle;
	GameManager::Get()->addToEntity(iLabel, this);
}

GameObject::GameObject(float radius, float posX, float posY, float speed, int iLabel)
{
	_sizeX = radius * 2;
	_sizeY = radius * 2;
	_posX = posX;
	_posY = posY;
	_speed = speed;
	_isDestroyed = false;
	_collider = new CircleCollider(_posX, _posY, _sizeX, _sizeY);

	sf::CircleShape* circle = new sf::CircleShape(radius);
	circle->setFillColor(sf::Color::Red);
	circle->setPosition(_posX, _posY);
	_graphic = circle;

	GameManager::Get()->addToEntity(iLabel, this);
}

sf::Shape& GameObject::getShape()
{
	return *_graphic;
}


bool GameObject::isColliding(const GameObject& object)
{
	return _collider->colliding(object._collider);
}

std::string GameObject::checkCollidingSide(const GameObject& object)
{
	return _collider->collidingSide(object._collider);
}

void GameObject::collideList(const std::vector<GameObject*>& list)
{
	for (int i = 0; i < list.size(); i++) {
		if (isColliding(*list[i])) {
			//std::cout << _collidingWith.size() << std::endl;
			//std::cout << checkCollidingSide(*list[i]) << std::endl;
			if (std::find(_collidingWith.begin(), _collidingWith.end(), list[i]) != _collidingWith.end()) {
				launchCollisionStay();
				list[i]->launchCollisionStay();
			}
			else {
				launchCollisionEnter(list[i]);
				list[i]->launchCollisionEnter(this);
			}
		}
		else {
			if (std::find(_collidingWith.begin(), _collidingWith.end(), list[i]) != _collidingWith.end()) {
				launchCollisionExit(list[i]);
				list[i]->launchCollisionExit(this);
			}
		}
	}
}

void GameObject::collide(GameObject* object)
{
	if (isColliding(*object)) {
		//std::cout << _collidingWith.size() << std::endl;
		if (std::find(_collidingWith.begin(), _collidingWith.end(), object) != _collidingWith.end()) {
			launchCollisionStay();
			object->launchCollisionStay();
		}
		else {
			launchCollisionEnter(object);
			object->launchCollisionEnter(this);
		}
	}
	else {
		if (std::find(_collidingWith.begin(), _collidingWith.end(), object) != _collidingWith.end()) {
			launchCollisionExit(object);
			object->launchCollisionExit(this);
		}
	}
}

/* void GameObject::bounce(std::string side)
{
	int i = _sides[side];
	switch (i)
	{
	case 1: // left
		_vector.x *= -1;
		break;
	case 2: // top
		_vector.y *= -1;
		break;
	case 3: // right
		_vector.x *= -1;
		break;
	case 4: // bottom
		_vector.y *= -1;
		break;
	}

}*/

void GameObject::moveShape(float deltaTime, const Math::Vector2& direction)
{
	_posX = _posX + (direction.x * deltaTime) * _speed;
	_posY = _posY + (direction.y * deltaTime) * _speed;

	_graphic->setPosition(_posX, _posY);
}

void GameObject::rotateShape(float rotateDegree)
{
	_rotate += rotateDegree;
	_graphic->setRotation(_rotate);
}


void GameObject::setOrigin(float fRatioX, float fRatioY)
{

	_graphic->setOrigin(_sizeX * fRatioX, _sizeY * fRatioY);
}

void GameObject::setOriginCenter()
{
	setOrigin(1 / 2.f, 1 / 2.f);
}

/*void GameObject::setOriginPointOnBase()
{
	setOrigin(1 / 2.f, 3 / 4.f);
}*/
Math::Vector2 GameObject::getPos(float fRatioX, float fRatioY)
{
	return Math::Vector2::Vector2(_posX + (_sizeX * fRatioX), _posY + (_sizeY * fRatioY));
}

void GameObject::setVector(float x, float y)
{
	_vector.x = x;
	_vector.y = y;
}

const Math::Vector2 GameObject::getVect()
{
	return _vector;
}

void GameObject::setPos(float x, float y) {
	_posX = x;
	_posY = y;
}

bool GameObject::destroyObject()
{
	return _isDestroyed;
}


void GameObject::launchCollisionEnter(GameObject* object)
{
	_collidingWith.push_back(object);
	//std::cout << checkCollidingSide(*object) << std::endl; //à modif
	onCollisionEnter(object);
}

void GameObject::launchCollisionStay()
{
	//B)
	onCollisionStay();
}

void GameObject::launchCollisionExit(GameObject* object)
{
	_collidingWith.erase(std::remove(_collidingWith.begin(), _collidingWith.end(), object), _collidingWith.end());
	onCollisionExit(object);
}

void GameObject::onCollisionEnter(GameObject* object) {}

void GameObject::onCollisionStay() {}

void GameObject::onCollisionExit(GameObject* object) {}

