#include "Tower.h"
#include "BlastBullet.h"
#include "TowerStates.h"
Tower::Tower(int posX,int posY , int type) : GameObject(100,100, posX, posY,0, GoLabel::Towers)
{
	_type = type;
	_level = 0;
	_bulletList = new std::vector<Bullet*>();
	_blastList = new std::vector<BlastBullet*>();
	giveStats();
	_area = new GameObject(_range, _posX + _sizeX / 2 - _range, _posY + _sizeY / 2 - _range, 0, GoLabel::Areas);
	timer = 1 / _AS +1;
	GameManager::Get()->addToEntity(this);
	_state = TowerStates::idle;
	_firstEnemy = new GameObject(100, 100, -1000, -1000, 0, -1);
}

void Tower::shoot(GameObject* enemy) {
	if (timer > 1/_AS)
	{
		if (_type != 2)
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
					_bulletList->at(i)->setTarget(enemy);
					timer = o_timer.restart().asSeconds();;
					break;
				}
			}
		}
		else {
			for (int i = 0; i < _blastList->size(); i++)
			{
				if (std::find(GameManager::Get()->_entities[GoLabel::Blasts].begin(), GameManager::Get()->_entities[GoLabel::Blasts].end(), _blastList->at(i)) == GameManager::Get()->_entities[GoLabel::Blasts].end())
				{
					_blastList->at(i)->_isDestroyed = false;
					GameManager::Get()->_entities[GoLabel::Blasts].push_back(_blastList->at(i));
					float x = _posX + _sizeX / 2 - (_blastList->at(i)->getRadius());
					float y = _posY + _sizeY / 2 - (_blastList->at(i)->getRadius());
					Math::Vector2 enemyVector = Math::Vector2::createVector(Math::Vector2(_posX, _posY), enemy->getPos().x, enemy->getPos().y).getNormalizeVector();
					_blastList->at(i)->setPos(x, y);
					_blastList->at(i)->setVector(enemyVector.x, enemyVector.y);
					_blastList->at(i)->getShape().setFillColor(sf::Color::Green);
					_blastList->at(i)->setTarget(enemy);
					timer = o_timer.restart().asSeconds();;
					break;
				}
			}
		}
		}
	timer = o_timer.getElapsedTime().asSeconds();
}

void Tower::enemyInSight() {
	if (_area->isColliding(*_firstEnemy))
	{
		_state = TowerStates::shoot;
	}
	else {
		_state = TowerStates::idle;
	}
}

void Tower::stateMachine() {
	switch (_state) {
	case TowerStates::idle:
		enemyInSight();
		break;
	case TowerStates::shoot:
		shoot(_firstEnemy);
		enemyInSight();
		break;
	}
}

void Tower::upgrade() {
	_level += 1;
	giveStats();
	_area->_sizeX = _range;
	_area->_sizeY = _range;
	_area->setPos(_posX + _sizeX / 2 - _range, _posY + _sizeY / 2 - _range);
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
	_bulletSpeed = GameManager::Get()->_modelStats[0][TowerLabel::bulletSpeed][_type][0];
	for(int i = 0;i<5;i++)
	{
		if (_type != 2)
		{
			_bulletList->push_back(new Bullet(15, _posX + _sizeX / 2 - 15, _posY + _sizeY / 2 - 15, _bulletSpeed, _damage));
		}
		else {
			_blastList->push_back(new BlastBullet(15, _posX + _sizeX / 2 - 15, _posY + _sizeY / 2 - 15, _bulletSpeed, _damage));
		}
	}
}