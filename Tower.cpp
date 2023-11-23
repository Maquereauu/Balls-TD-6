#include "Tower.h"

#include "Bullet.h"
#include "TowerStates.h"
Tower::Tower(int posX,int posY , int type) : GameObject(100,100, posX, posY,0, GoLabel::Towers)
{
	_type = type;
	_level = 0;
	_bulletList = new std::vector<Bullet*>();
	giveStats();
	_area = new GameObject(_range, _posX + _sizeX / 2 - _range, _posY + _sizeY / 2 - _range, 0, GoLabel::Areas);
	timer = 1 / _AS +1;
	GameManager::Get()->addToEntity(this);
	_state = TowerStates::idle;
}

void Tower::shoot(GameObject* enemy) {
	if (timer > 1/_AS)
	{
		for (int i = 0; i < _bulletList->size(); i++)
		{
			if (std::find(GameManager::Get()->_entities[GoLabel::Bullets].begin(), GameManager::Get()->_entities[GoLabel::Bullets].end(), _bulletList->at(i)) == GameManager::Get()->_entities[GoLabel::Bullets].end())
			{
				_bulletList->at(i)->_isDestroyed = false;
				GameManager::Get()->_entities[GoLabel::Bullets].push_back(_bulletList->at(i));
				float x = _posX + _sizeX / 2 - (_bulletList->at(i)->getRadius());
				float y = _posY + _sizeY / 2 - (_bulletList->at(i)->getRadius());
				Math::Vector2 enemyVector = Math::Vector2::createVector(Math::Vector2(_posX, _posY), enemy->getPos().x, enemy->getPos().y).getNormalizeVector();
				_bulletList->at(i)->setPos(x, y);
				_bulletList->at(i)->setVector(enemyVector.x, enemyVector.y);
				_bulletList->at(i)->getShape().setFillColor(sf::Color::Green);
				timer = o_timer.restart().asSeconds();;
				break;
			}
		}
	}
	timer = o_timer.getElapsedTime().asSeconds();
}

void Tower::enemyInSight(GameObject* enemy) {
	if (_area->isColliding(*enemy))
	{
		_state = TowerStates::shoot;
	}
	else {
		_state = TowerStates::idle;
	}
}

void Tower::stateMachine(GameObject* enemy) {
	switch (_state) {
	case TowerStates::idle:
		enemyInSight(enemy);
		break;
	case TowerStates::shoot:
		shoot(enemy);
		enemyInSight(enemy);
		break;
	}
}

void Tower::upgrade() {
	_level += 1;
	giveStats();
}

bool Tower::canUpgrade() {
	return(_level <= 3 ? true : false);
}

void Tower::giveStats() {
	_AS = GameManager::Get()->_modelStats[0][TowerLabel::as][_type][_level];
	_cost = GameManager::Get()->_modelStats[0][TowerLabel::cost][_type][_level];
	_buildingCost = GameManager::Get()->_modelStats[0][TowerLabel::buildingCost][_type][0];
	_damage = GameManager::Get()->_modelStats[0][TowerLabel::damage][_type][_level];
	_range = GameManager::Get()->_modelStats[0][TowerLabel::range][_type][_level];
	_bulletSpeed = GameManager::Get()->_modelStats[0][TowerLabel::bulletSpeed][_type][_level];
	for(int i = 0;i<5;i++)
	_bulletList->push_back(new Bullet(15, _posX + _sizeX / 2 - 15, _posY + _sizeY / 2 - 15, _bulletSpeed, _damage));
}