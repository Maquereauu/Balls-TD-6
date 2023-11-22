#pragma once
#include "GameObject.h"

class Bullet;

class Tower : public GameObject
{
private:
	int _AS;
	int _cost;
	int _buildingCost;
	int _damage;
	int _level;
	int _range;
	int _bulletSpeed;
	int _type;
	std::vector<Bullet*>* _bulletList;
	Tower(int posX,int posY,int type);
public:
	void shoot();
	void giveStats();
	void upgrade();
	bool canUpgrade();
};

