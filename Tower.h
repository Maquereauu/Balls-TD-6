#pragma once
#include "GameObject.h"

class Bullet;

class Tower : public GameObject
{
private:
	float _AS;
	int _cost;
	int _buildingCost;
	int _damage;
	int _level;
	int _range;
	int _bulletSpeed;
	int _type;
	sf::Clock o_timer;
	float timer;
public:
	std::vector<Bullet*>* _bulletList;
	GameObject* _area;
	Tower(int posX, int posY, int type);
	void shoot(GameObject* enemy);
	void enemyInSight(GameObject* enemy);
	void giveStats();
	void upgrade();
	bool canUpgrade();
};

