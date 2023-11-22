#include "Enemy.h"

Enemy::Enemy(int maxHp)
    : maxHp(maxHp), Hp(maxHp) {}

void Enemy::takeDamage(int damage) {
    Hp -= damage;
    if (Hp < 0) {
        Hp = 0;
    }
}

bool Enemy::isAlive() const {
    return Hp > 0;
}
