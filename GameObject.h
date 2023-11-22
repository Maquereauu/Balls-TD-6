#pragma once

#include <string>
#include <vector>
#include <map>
#include "GameObjectEnum.h"
#include "ModelsEnum.h"
#include "GameManager.h"
#include "Math.h"
class sf::Shape;
class Collider;

class GameObject
{
public:
	//std::map<std::string, int> _sides = { {"left",1},{"top",2},{"right",3},{"bottom",4} };
	float _speed;
	bool _isDestroyed;

protected:
	float _sizeX;
	float _sizeY;
	float _posX;
	float _posY;
	float _rotate;
	float deltaTime;
	std::vector<GameObject*> _collidingWith;
	sf::Shape* _graphic;
	Collider* _collider;
	Math::Vector2 _vector;

public:
	GameObject(float sizeX, float sizeY, float posX, float posY, float speed, int iLabel); // rectangle
	GameObject(float radius, float posX, float posY, float speed, int iLabel); // ball

	// movements
	void moveShape(float deltaTime, const Math::Vector2& direction);
	void rotateShape(float rotateDegree);

	void setOrigin(float fRatioX, float fRatioY);
	void setOriginCenter();
	//void setOriginPointOnBase();
	void setPos(float x, float y);
	void setVector(float x, float y);
	Math::Vector2 getPos(float fRatioX = 0, float fRatioY = 0);
	const Math::Vector2 getVect();
	sf::Shape& getShape();

	bool destroyObject();

	// event for collision 
	bool isColliding(const GameObject& object);
	void collideList(const std::vector<GameObject*>& list);
	void collide(GameObject* object);
	std::string checkCollidingSide(const GameObject& object);
	//void bounce(std::string side);

	void launchCollisionEnter(GameObject* object);  // virtual permet l'override pour les enfants de la classe
	void launchCollisionStay();
	void launchCollisionExit(GameObject* object);

	virtual void onCollisionEnter(GameObject* object);  // virtual permet l'override pour les enfants de la classe
	virtual void onCollisionStay();
	virtual void onCollisionExit(GameObject* object);
};

