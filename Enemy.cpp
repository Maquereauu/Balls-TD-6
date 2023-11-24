#include "Enemy.h"
#include "Tower.h"
#include "BlastBullet.h"
Enemy::Enemy(float posx, float posy, int type) : GameObject(50 + 100 * type, 50 + 100 * type, posx, posy, 0, GoLabel::Enemies) {
    _type = type;
    _maxHealth = GameManager::Get()->_modelStats[1][EnemyLabel::maxHp][_type][0];
    _currentHealth = _maxHealth;
    _speedEnemy = GameManager::Get()->_modelStats[1][EnemyLabel::speed][_type][0];
    _speed = _speedEnemy;
    setVector(1.0, 0.f);
}


float Enemy::getRadius() {
    return _sizeX / 2;
}

void Enemy::takeDamage(int damage) {
    _currentHealth -= damage;
    if (_currentHealth < 0) {
        //_currentHealth = 0;
        _isDestroyed = true;
    }
}

void Enemy::dealDamage() {
    GameManager::Get()->health -= _currentHealth;
    setPos(-1000, -1000);
    _currentHealth = 0;
    _isDestroyed = true;
}

bool Enemy::isAlive() const {
    return _currentHealth > 0;
}

void Enemy::onCollisionEnter(GameObject* object) {
    if (object == GameManager::Get()->_o_door)
    {
        dealDamage();
    }
    else {
        if (std::find(GameManager::Get()->_blastRadius.begin(), GameManager::Get()->_blastRadius.end(), object) != GameManager::Get()->_blastRadius.end()) {
            for (int i = 0; i < GameManager::Get()->_blastRadius.size(); i++)
            {
                std::vector<Bullet*> _blastRadius = GameManager::Get()->_blastRadius;
                int damageTaken = (*std::find(_blastRadius.begin(), _blastRadius.end(), object))->getDamage();
                _currentHealth -= damageTaken;
                if (_currentHealth <= 0) {
                    GameManager::Get()->money += damageTaken + _currentHealth;
                    _currentHealth = 0;

                    setPos(-1000, -1000);
                    _isDestroyed = true;
                }
                else {
                    GameManager::Get()->money += damageTaken;
                }
            }
        }
        else
        {
            for (int i = 0; i < GameManager::Get()->_towers.size(); i++)
            {
                if (GameManager::Get()->_towers[i]->_type != 2)
                {
                    std::vector<Bullet*>* bulletList = GameManager::Get()->_towers[i]->_bulletList;
                    if (std::find(bulletList->begin(), bulletList->end(), object) != bulletList->end())
                    {
                        int damageTaken = (*std::find(bulletList->begin(), bulletList->end(), object))->getDamage();
                        _currentHealth -= damageTaken;
                        if (_currentHealth <= 0) {
                            GameManager::Get()->money += damageTaken + _currentHealth;
                            _currentHealth = 0;
                            setPos(-1000, -1000);
                            _isDestroyed = true;
                        }
                        else {
                            GameManager::Get()->money += damageTaken;
                        }
                    }
                }
                else {
                    std::vector<BlastBullet*>* blastList = GameManager::Get()->_towers[i]->_blastList;
                    if(std::find(blastList->begin(), blastList->end(), object) != blastList->end())
                    {
                        int damageTaken = (*std::find(blastList->begin(), blastList->end(), object))->getDamage();
                        _currentHealth -= damageTaken;
                        if (_currentHealth <= 0) {
                            GameManager::Get()->money += damageTaken + _currentHealth;
                            _currentHealth = 0; 
                            setPos(-1000, -1000);
                            _isDestroyed = true;
                        }
                        else {
                            GameManager::Get()->money += damageTaken;
                        }
                    }
                }
            }
        }
    }
    std::cout << _currentHealth << std::endl;
}