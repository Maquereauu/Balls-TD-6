#include "GameManager.h"
#include "GameObject.h"
#include "EventManager.h"
#include "Window.h"
#include "GameObjectEnum.h"
#include "Tower.h"
#include "BlastBullet.h"
#include "Enemy.h"

GameManager* GameManager::pInstance = nullptr;

void GameManager::Create()
{
	if (GameManager::pInstance != nullptr)
		return;

	GameManager::pInstance = new GameManager();
	GameManager::pInstance->Initialize();
}

//void throwBullet()
//{
//	GameManager::Get()->MthrowBullet();
//}
void Upgrade()
{
	int result = 0;
	for (int i = 0; i < GameManager::Get()->GetTowerList().size(); i++) 
	{
		if (EventManager::Get()->m_oAreas[EventManager::Get()->getActuelIndex()]._x == GameManager::Get()->GetTowerList()[i]->getPos().x && EventManager::Get()->m_oAreas[EventManager::Get()->getActuelIndex()]._y == GameManager::Get()->GetTowerList()[i]->getPos().y)
		{
			result = i;
		}
	}
	GameManager::Get()->MUpgrade(*GameManager::Get()->GetTowerList()[result]);
};

void PosetaTour() {
	GameManager::Get()->MPosetaTour();
}

void SelectTowerUn() 
{
	GameManager::Get()->MselectTowerUn();
}

void SelectTowerDeux()
{
	GameManager::Get()->MselectTowerDeux();
}

void SelectTowerTroi()
{
	GameManager::Get()->MselectTowerTroi();
}

void quit()
{
	GameManager::Get()->Mquit();
}

void retry()
{
	GameManager::Get()->Mretry();
}
//
void GameManager::Initialize() 
{
	/*
	* INIT objets
	*/
	TowerCreated = -1;
	_width = new int(1920);
	_height = new int(1080);
	_o_window = new Window(*_width, *_height);
	_window = _o_window->getWindow();
	_mousePos = new sf::Vector2i();
	_o_bullet = new std::vector<Bullet*>();
	o_model = new FileReader();
	_entities.resize(GoLabel::Total);
	money = 4000;
	metal = 3;
	health = 100;
	//File Reader
	o_model->readFile("models.csv");
	if (!font.loadFromFile("Arial.ttf"))
	{
		// error...
	}
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Green);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(500,15);


	textMetal.setFont(font);
	textMetal.setCharacterSize(24);
	textMetal.setFillColor(sf::Color::Green);
	textMetal.setStyle(sf::Text::Bold | sf::Text::Underlined);
	textMetal.setPosition(700, 15);


	winText.setFont(font);
	winText.setString("You won!");
	winText.setCharacterSize(48);
	winText.setFillColor(sf::Color::Yellow);
	winText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	winText.setPosition(500, 200);
	

	loseText.setFont(font);
	loseText.setString("You lost :(");
	loseText.setCharacterSize(48);
	loseText.setFillColor(sf::Color::Red);
	loseText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	loseText.setPosition(500, 200);

	if (!_texture.loadFromFile("image.png"));
	_background = new sf::Sprite(_texture);
	_background->setScale(*_width / _background->getLocalBounds().width,
		*_height / _background->getLocalBounds().height);
	//Game Area
	/*_entities.resize(GoLabel::Total);
	GameObject* o_leftSide = new GameObject(*_width / 4, *_height, 0.f, 0.f, 0.f, GoLabel::border);
	GameObject* o_rigthSide = new GameObject(*_width / 4, *_height, (*_width / 4) * 3, 0.f, 0.f, GoLabel::border);
	GameObject* o_top = new GameObject((*_width / 4) * 2, *_height * 0.1, (*_width / 4), 0.f, 0.f, GoLabel::border);
	GameObject* o_restart = new GameObject(100, 100, 0, 0.f, 0.f, GoLabel::border);
	o_leftSide->getShape().setFillColor(sf::Color::Color(128, 128, 128, 255));
	o_rigthSide->getShape().setFillColor(sf::Color::Color(128, 128, 128, 255));
	o_top->getShape().setFillColor(sf::Color::Color(128, 128, 128, 255));
	o_restart->getShape().setFillColor(sf::Color::Green);
	_o_tower = new Tower();*/
	_waves = { { 0,0,0,0,0,1,1 } ,{ 0,0,0,0,1,1,1 } ,{ 0,0,0,0,1,1,2 } };
	_o_tower.push_back(new Tower(920, 700, 1));
	_o_door = new GameObject(150, 150, 1500, 500, 10, GoLabel::Door);

	uhdSelectTowerDeux = new GameObject(100, 100, 140, 15, 0, GoLabel::Door);
	uhdSelectTowerUn = new GameObject(100, 100, 30, 15, 0, GoLabel::Door);
	uhdSelectTowertroi = new GameObject(100, 100, 250, 15, 0, GoLabel::Door);

	/*
	* INIT events
	*/

	EventManager::Get()->AddArea(110, 120, 1860, 950, GameArea::Maps);
	EventManager::Get()->AddArea(30, 15, 100, 100, GameArea::SelectFirstTurret);
	EventManager::Get()->AddArea(140, 15, 100, 100, GameArea::SelectSecondTurret);
	EventManager::Get()->AddArea(250, 15, 100, 100, GameArea::SelectThirdTurret);
	EventManager::Get()->AddArea(250, 15, 100, 100, GameArea::SelectThirdTurret);


	EventManager::Get()->AddEvent(GameArea::Quit, sf::Event::EventType::Closed, &quit);
	EventManager::Get()->AddEvent(GameArea::SelectFirstTurret, sf::Event::EventType::MouseButtonPressed, &SelectTowerUn);
	EventManager::Get()->AddEvent(GameArea::SelectSecondTurret, sf::Event::EventType::MouseButtonPressed, &SelectTowerDeux);
	EventManager::Get()->AddEvent(GameArea::SelectThirdTurret, sf::Event::EventType::MouseButtonPressed, &SelectTowerTroi);
	EventManager::Get()->AddEvent(GameArea::Maps, sf::Event::EventType::MouseButtonPressed, &PosetaTour);

}
//
void GameManager::Mretry()
{
	// retire les bulletes en vie
	//std::vector<GameObject*>().swap(_entities[GoLabel::bullet]);
	//_entities[GoLabel::bullet].clear();
	// retire les bricks en vie
	//std::vector<GameObject*>().swap(_entities[GoLabel::brick]);
	//_entities[GoLabel::brick].clear();
	// ajoute les nouvelles bricks pour �tre en vie

}

void GameManager::Mquit()
{
	_window->close();
}

//void GameManager::MthrowBullet()
//{
//	Math::Vector2 mouseVector = Math::Vector2::createVector(_o_tower->getPos(), _mousePos->x, _mousePos->y).getNormalizeVector();
//
//	if (mouseVector.y < 0 && Math::Vector2::leftVector.getAngle(mouseVector) >= 10 && Math::Vector2::leftVector.getAngle(mouseVector) <= 170)
//	{
//		if (timer > 0.3)
//		{
//			for (int i = 0; i < _o_bullet->size(); i++)
//			{
//				if (std::find(_entities[GoLabel::Bullets].begin(), _entities[GoLabel::Bullets].end(), _o_bullet->at(i)) == _entities[GoLabel::Bullets].end())
//				{
//					_o_bullet->at(i)->_isDestroyed = false;
//					_o_bullet->at(i)->_side = "";
//					_entities[GoLabel::Bullets].push_back(_o_bullet->at(i));
//					//_o_tower->shoot(mouseVector, _o_bullet->at(i));
//					timer = o_timer.restart().asSeconds();;
//					break;
//				}
//			}
//		}
//	}
//}
void GameManager::launchGame()
{
	//_win = false;
	sf::Clock o_clock;
	float deltaTime = 0.f;
	//timer = 0.f;
	timerSpawn = 3.f;
	int enemiesCounter = 0;
	int wave = 0;
	while (_window && _window->isOpen())
	{
		EventManager::Get()->Update(_window);
		if (health <= 0) {
			_window->draw(loseText);
			_window->display();

			continue;
		}
		if(wave< _waves.size())
		{
			if (enemiesCounter < _waves[wave].size())
			{
				if (timerSpawn > 2) {
					new Enemy(150 - 50 * _waves[wave][enemiesCounter], 550 - 50 * _waves[wave][enemiesCounter], _waves[wave][enemiesCounter]);
					enemiesCounter++;
					timerSpawn = o_timerSpawn.restart().asSeconds();;
				}
			}
		}
		else {
			_window->draw(winText);
			_window->display();
		}
		for (int i = 0; i < _entities[GoLabel::Blasts].size(); i++)
		{
			for (int j = 0; j < _entities[GoLabel::Enemies].size(); j++)
			{
				_entities[GoLabel::Blasts][i]->collide(_entities[GoLabel::Enemies][j]);
			}
		}
		for (int i = 0; i < _entities[GoLabel::Manstre].size(); i++)
		{
			for (int j = 0; j < _entities[GoLabel::Enemies].size(); j++)
			{
				_entities[GoLabel::Manstre][i]->collide(_entities[GoLabel::Enemies][j]);
			}
		}
		for (int i = 0; i < _towers.size(); i++)
		{
			for (int j = 0; j < _entities[GoLabel::Enemies].size(); j++)
			{
				if (_towers[i]->_area->isColliding(*_towers[i]->_firstEnemy))
				{
					if (_towers[i]->_firstEnemy->getPos().x < _entities[GoLabel::Enemies][j]->getPos().x)
					{
						_towers[i]->_firstEnemy = _entities[GoLabel::Enemies][j];
					}
				}
				else if (_towers[i]->_firstEnemy != _entities[GoLabel::Enemies][j])
				{
					_towers[i]->_firstEnemy = _entities[GoLabel::Enemies][j];
				}
			}
			_towers[i]->stateMachine();
		}

		for (int j = 0; j < _towers.size(); j++)
		{
			if (_towers[j]->_type != 2)
			{
				for (int i = 0; i < _entities[GoLabel::Bullets].size(); i++)
				{
					for (int k = 0; k < _towers[j]->_bulletList->size(); k++)
					{
						if (_towers[j]->_bulletList->at(k) == _entities[GoLabel::Bullets][i]) {
							for (int l = 0; l < _entities[GoLabel::Enemies].size(); l++)
							{
								if (_towers[j]->_bulletList->at(k)->getTarget() == _entities[GoLabel::Enemies][l])
								{
									_towers[j]->_bulletList->at(k)->collide(_entities[GoLabel::Enemies][l]);
								}
							}
						}
					}
				}
			}
			else {
				for (int i = 0; i < _entities[GoLabel::Blasts].size(); i++)
				{
						for (int k = 0; k < _towers[j]->_blastList->size(); k++)
						{
							if (_towers[j]->_blastList->at(k) == _entities[GoLabel::Blasts][i]) {
								for (int l = 0; l < _entities[GoLabel::Enemies].size(); l++)
								{
									if (_towers[j]->_blastList->at(k)->getTarget() == _entities[GoLabel::Enemies][l])
									{
										_towers[j]->_blastList->at(k)->collide(_entities[GoLabel::Enemies][l]);
									}
								}
							}
					}
				}
			}
		}

		for (int i = 0; i < _entities[GoLabel::Enemies].size(); i++)
		{
			_entities[GoLabel::Enemies][i]->collide(_o_door);
		}


		for (int i = 0; i < _towers.size(); i++)
		{
			if(_towers[i]->_type != 2)
			{
				for (int j = 0; j < _towers[i]->_bulletList->size(); j++)
				{
					if (!(_towers[i]->_bulletList->at(j)->isColliding(*(_towers[i]->_area))))
					{
						_towers[i]->_bulletList->at(j)->_isDestroyed = true;
					}
					else
					{
						_towers[i]->_bulletList->at(j)->setVectorTowardsTarget();
					}
					if(_towers[i]->_bulletList->at(j)->getTarget())
					{
						if (_towers[i]->_bulletList->at(j)->getTarget()->_isDestroyed)
						{
							_towers[i]->_bulletList->at(j)->_isDestroyed = true;
						}
					}

				}
			}
			else {
				for (int j = 0; j < _towers[i]->_blastList->size(); j++)
				{
					if (!(_towers[i]->_blastList->at(j)->isColliding(*(_towers[i]->_area))))
					{
						_towers[i]->_blastList->at(j)->_isDestroyed = true;
					}
					else
					{
						_towers[i]->_blastList->at(j)->setVectorTowardsTarget();
					}

				}
			}
		}

		for (int i = 0; i < _entities.size(); i++)
		{
			for (int j = 0; j < _entities[i].size(); j++)
			{
				if (_entities[i][j]->destroyObject()) {
					_entities[i].erase(std::remove(_entities[i].begin(), _entities[i].end(), _entities[i][j]), _entities[i].end());
				}
			}
		}
		for (int i = 0; i < _entities.size(); i++)
		{
			for (int j = 0; j < _entities[i].size(); j++)
			{
				_entities[i][j]->moveShape(deltaTime, _entities[i][j]->getVect());
			}
		}

		_window->clear();
		_window->draw(*_background);
		for (int i = 0; i < GoLabel::Total; i++)
		{
			_o_window->winDraw(_entities[i]);
		}
		text.setString("Money: " + std::to_string(money));
		textMetal.setString("Metal: " + std::to_string(metal));
		_window->draw(text);
		_window->draw(textMetal);
		_window->display();
		if (_entities[GoLabel::Enemies].size() == 0 && enemiesCounter == _waves[wave].size())
		{
			wave++;
			enemiesCounter = 0;
			timerSpawn = 3.f;
			metal++;
		}
		deltaTime = o_clock.restart().asSeconds();
		//timer = o_timer.getElapsedTime().asSeconds();
		timerSpawn = o_timerSpawn.getElapsedTime().asSeconds();
	}
}

//void GameManager::MmoveTower()
//{
//	Math::Vector2 mouseVector = Math::Vector2::createVector(_o_tower->getPos(), _mousePos->x, _mousePos->y).getNormalizeVector();
//	if (mouseVector.y < 0 && Math::Vector2::leftVector.getAngle(mouseVector) >= 15 && Math::Vector2::leftVector.getAngle(mouseVector) <= 165)
//	{
//		_o_tower->move(mouseVector);
//	}
//}

void GameManager::addToEntity(int iLabel, GameObject* o_gameObject)
{
	if (iLabel == -1)
		return;

	_entities[iLabel].push_back(o_gameObject);
}

void GameManager::addToEntity(Tower* o_tower)
{
	_towers.push_back(o_tower);
}

void GameManager::addToEntity(Enemy* o_enemy)
{
	_enemies.push_back(o_enemy);
}

void GameManager::addToEntity(BlastBullet* o_blastBullet)
{
	_blastBullets.push_back(o_blastBullet);
}

void GameManager::addToEntity(Bullet* o_bullet)
{
	_blastRadius.push_back(o_bullet);
}
void GameManager::MselectTowerUn()
{
	TowerCreated = 0;
};

void GameManager::MselectTowerDeux()
{
	TowerCreated = 1;
};

void GameManager::MselectTowerTroi()
{
	TowerCreated = 2;
};

void GameManager::MPosetaTour()
{
	int impossible = 0;
	std::cout << TowerCreated;
	std::cout << "towercreated:" << TowerCreated;
	if (TowerCreated != -1) {
		for (int i = 0; i<_o_tower.size();i++) 
		{
			std::cout << "towercreated:" << TowerCreated;
			if (metal < GameManager::Get()->_modelStats[0][TowerLabel::buildingCost][TowerCreated][0])
			{
				impossible = impossible + 1;
			}
			if ((_mousePos->x >= _o_tower[i]->getPos().x - 100 && _mousePos->x <= (100 + _o_tower[i]->getPos().x)) && (_mousePos->y >= _o_tower[i]->getPos().y - 100 && _mousePos->y <= (100 + _o_tower[i]->getPos().y))) 
			{
				impossible = impossible + 1;
			}
		}
		if (impossible == 0)
		{
			std::cout << "towercreated:" << TowerCreated;
			_o_tower.push_back(new Tower(_mousePos->x, _mousePos->y, TowerCreated));
			metal = metal - GameManager::Get()->_modelStats[0][TowerLabel::buildingCost][TowerCreated][0];
			EventManager::Get()->AddArea(_mousePos->x, _mousePos->y, 100, 100, GameArea::TowerArea);
			_o_tower[_o_tower.size() - 1]->setIndexArea(_o_tower.size() - 1);
			EventManager::Get()->AddEvent(GameArea::TowerArea, sf::Event::EventType::KeyPressed, &Upgrade);
			TowerCreated = -1;
		}
		
	}
};

void GameManager::MUpgrade(Tower latour)
{
	if (latour.canUpgrade() == false) {
		return;
	}
		
	if (money < GameManager::Get()->_modelStats[0][TowerLabel::cost][latour._type][latour._level])
		return;

	if ((_mousePos->x < latour.getPos().x - 100 && _mousePos->x >(100 + latour.getPos().x)) && (_mousePos->y < latour.getPos().y - 100 && _mousePos->y >(100 + latour.getPos().y)))
		return;

	latour.upgrade();
	money = money - GameManager::Get()->_modelStats[0][TowerLabel::cost][latour._type][latour._level];
};

std::vector<Tower*>& GameManager::GetTowerList()
{
	return _o_tower;
};
