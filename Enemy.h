#ifndef ENEMIE_H
#define ENEMIE_H

class Enemie {
private:
    int maxHp;
    int Hp;

public:
    Enemie(int maxHp);
    void takeDamage(int damage);
    bool isAlive() const;
};

#endif // ENEMY_H
