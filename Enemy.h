#include "GameObject.h"

class Enemy : public GameObject {
private:
    int _maxHealth;
    int _currentHealth;
    int _speedEnemy;
    int _type;
public:
    Enemy(float posx, float posy,int type);
    float getRadius();
    void takeDamage(int damage);
    bool isAlive() const;
    void dealDamage();
    void onCollisionEnter(GameObject* object) override;
};

