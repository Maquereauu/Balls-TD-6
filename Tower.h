#pragma once
#include "GameObject.h"
class Tower : public GameObject
{
private:
	int _AS;
	int _cost;
	int _buildingCost;
	int _damage;
	int _level;
	int _range;
	int _type;
	Tower(int posX,int posY,int type);
public:
	void shoot();
};

