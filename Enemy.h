#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject {
private:
    int maxHealth;
    int currentHealth;

public:
    Enemy(float radius, float x, float y, float speed, int maxHealth);
    Enemy();
    float getRadius();
    void takeDamage(int damage);
    bool isAlive() const;
};

#endif // ENEMY_H
