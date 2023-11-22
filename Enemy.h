#ifndef ENEMY_H
#define ENEMY_H

#include"GameObject.h

class Enemy : public GameObject{
private:
    int maxHp;
    int Hp;

public:
    Enemy(int maxHp);
    void takeDamage(int damage);
    bool isAlive() const;
};

#endif // ENEMY_H
