#include "Bullet.h"
#include "GameObjectEnum.h"

Bullet::Bullet(float radius, float x, float y, float speed, int damage) : GameObject(radius, x, y, speed, -1) // create a bullet with is parent
{
    _damage = damage;
    _speed = _speed;
    //setOriginCenter();
    setVector(0.f, 0.f);
}

//Bullet::Bullet() : Bullet(15.f, 700.f, 500.f, 180.f, 0, NULL) {};

float Bullet::getRadius() {
    return _sizeX / 2;
}
GameObject* Bullet::getTarget()
{
    return _target;
};

void Bullet::setTarget(GameObject* gameObject)
{
     _target = gameObject;
};

float Bullet::getSpeed() 
{
    return _speed;
};

float Bullet::getDamage() 
{
    return _damage;
};
/*   void Bullet::onCollisionEnter(GameObject* object) {
*    std::string collidingSide = checkCollidingSide(*object);
*    if (collidingSide != _side)
*    {
*        bounce(collidingSide);
*    }
*    _side = collidingSide;
     }
*/ 

void Bullet::onCollisionEnter(GameObject* object)
{
    _isDestroyed = true;
    setPos(-1000, -1000);
}

void Bullet::setVectorTowardsTarget() {
    if(_target)
    {
        Math::Vector2 enemyVector = Math::Vector2::createVector(Math::Vector2(_posX + _sizeX / 2, _posY + _sizeY / 2), _target->getPos(0.5).x, _target->getPos(0.5).y).getNormalizeVector();
        setVector(enemyVector.x, enemyVector.y);
    }
}