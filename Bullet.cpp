#include "Bullet.h"
#include "GameObjectEnum.h"

Bullet::Bullet(float radius, float x, float y, float _speed, int _Damage, GameObject* _Target) : GameObject(radius, x, y, speed, -GoLabel::Bullet) // create a bullet with is parent
{
    Damage = _Damage;
    Target = _Target;
    speed = _speed;
    //setOriginCenter();
    setVector(0.f, 0.f);
}

//Bullet::Bullet() : Bullet(15.f, 700.f, 500.f, 180.f, 0, NULL) {};

float Bullet::getRadius() {
    return _sizeX / 2;
}
GameObject* Bullet::getTarget() 
{
    return Target;
};

float Bullet::getSpeed() 
{
    return speed;
};

float Bullet::getDamage() 
{
    return Damage;
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