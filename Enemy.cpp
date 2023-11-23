#include "Enemy.h"

Enemy::Enemy(float radius, float x, float y, float speed, int maxHealth)
    : GameObject(radius, x, y, speed, -1), maxHealth(maxHealth), currentHealth(maxHealth) {
    setVector(0.f, 0.f);
}

Enemy::Enemy() : Enemy(15.f, 700.f, 500.f, 180.f, 100) {}; // Exemple avec 100 comme santé maximale

float Enemy::getRadius() {
    return _sizeX / 2;
}

void Enemy::takeDamage(int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

bool Enemy::isAlive() const {
    return currentHealth > 0;
}
