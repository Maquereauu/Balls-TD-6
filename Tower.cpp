#include "Tower.h"

#include "Bullet.h"

Tower::Tower(int posX,int posY , int type) : GameObject(100,100, posX, posY,0, GoLabel::Towers)
{
	_type = type;
	_level = 0;
	giveStats();
	_bulletList = new std::vector<Bullet*>();
}

void Tower::shoot() {

}

void Tower::upgrade() {
	_level += 1;
	giveStats();
}

bool Tower::canUpgrade() {
	return(_level <= 4 ? true : false);
}

void Tower::giveStats() {
	_AS = GameManager::Get()->_modelStats[GoLabel::Towers][TowerLabel::as][_type][_level];
	_cost = GameManager::Get()->_modelStats[GoLabel::Towers][TowerLabel::cost][_type][_level];
	_buildingCost = GameManager::Get()->_modelStats[GoLabel::Towers][TowerLabel::buildingCost][_type][0];
	_damage = GameManager::Get()->_modelStats[GoLabel::Towers][TowerLabel::damage][_type][_level];
	_range = GameManager::Get()->_modelStats[GoLabel::Towers][TowerLabel::range][_type][_level];
	_bulletSpeed = GameManager::Get()->_modelStats[GoLabel::Towers][TowerLabel::bulletSpeed][_type][_level];
	for (int i = 0; i < 6; i++) {
		_bulletList->push_back(new Bullet(15, _posX, _posY, _bulletSpeed, _damage));
	}
}