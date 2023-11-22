#include "Enemie.h"

Enemie::Enemie(int maxHp)
    : maxHp(maxHp), Hp(maxHp) {}

void Enemie::takeDamage(int damage) {
    Hp -= damage;
    if (Hp < 0) {
        Hp = 0;
    }
}

bool Enemie::isAlive() const {
    return Hp > 0;
}
