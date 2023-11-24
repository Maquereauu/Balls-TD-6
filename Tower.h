#pragma once
#include "GameObject.h"

class Bullet;
class BlastBullet;
class Tower : public GameObject
{
private:
	float _AS;
	int IndexArea;
	int _cost;
	int _buildingCost;
	int _damage;

	int _range;
	int _bulletSpeed;
	sf::Clock o_timer;
	float timer;
	int _state;
public:
	int _level;
	int _type;
	std::vector<Bullet*>* _bulletList;
	std::vector<BlastBullet*>* _blastList;
	GameObject* _firstEnemy;
	GameObject* _area;
	Tower(int posX, int posY, int type);
	void shoot(GameObject* enemy);
	void enemyInSight();
	void giveStats();
	void upgrade();
	bool canUpgrade();
	void stateMachine();
	void setIndexArea(int index);
	int getIndexArea();
};

