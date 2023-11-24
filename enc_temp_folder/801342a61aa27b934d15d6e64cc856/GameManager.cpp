#include "GameManager.h"
#include "GameObject.h"
#include "EventManager.h"
#include "Window.h"
#include "GameObjectEnum.h"
#include "Tower.h"
#include "Bullet.h"

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
	GameManager::Get()->MUpgrade(*GameManager::Get()->GetTowerList()[GameManager::Get()->GetTowerList().size()-1]);
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
	money = 400;
	metal = 3;
	health = 100;
	//File Reader
	o_model->readFile("models.csv");
	if (!font.loadFromFile("Arial.ttf"))
	{
		// error...
	}
	text.setFont(font);
	text.setString("Hello world");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Green);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(200,15);
	

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
	_o_tower.push_back(new Tower(100, 100, 1));
	_o_enemy = new GameObject(50, 50, 300, 300, 10, GoLabel::Enemies);
	_o_enemy->setVector(1.0, 0.f);
	_o_door = new GameObject(150, 150, 1500, 300, 10, GoLabel::Door);

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
	// ajoute les nouvelles bricks pour être en vie

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
	timer = 0.f;

	while (_window && _window->isOpen())
	{
		EventManager::Get()->Update(_window);

		for (int i = 0; i < _entities[GoLabel::Bullets].size(); i++)
		{
			for (int j = 0; j < _entities[GoLabel::Enemies].size(); j++)
			{
				_entities[GoLabel::Bullets][i]->collide(_entities[GoLabel::Enemies][j]);
			}
		}

		for (int i = 0; i < _entities[GoLabel::Enemies].size(); i++)
		{
			_entities[GoLabel::Enemies][i]->collide(_o_door);
		}

		for (int i = 0; i < _towers.size(); i++)
		{
			for (int j = 0; j < _entities[GoLabel::Enemies].size(); j++)
				_towers[i]->stateMachine(_entities[GoLabel::Enemies][j]);
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

		for (int i = 0; i < _towers.size(); i++)
		{
			for(int j = 0;j < _towers[i]->_bulletList->size();j++)
			{
				if (!(_towers[i]->_bulletList->at(j)->isColliding(*(_towers[i]->_area))))
				{
					_entities[GoLabel::Bullets].erase(std::remove(_entities[GoLabel::Bullets].begin(), _entities[GoLabel::Bullets].end(), _towers[i]->_bulletList->at(j)), _entities[GoLabel::Bullets].end());
				}
				else
				{
					_towers[i]->_bulletList->at(j)->setVectorTowardsTarget();
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
		for (int i = 0; i < GoLabel::Total; i++)
		{
			_o_window->winDraw(_entities[i]);
		}
		_window->draw(text);
		_window->display();

		deltaTime = o_clock.restart().asSeconds();
		timer = o_timer.getElapsedTime().asSeconds();
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
	if (TowerCreated != -1) {
		for (int i = 0; i<_o_tower.size();i++) 
		{
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
			_o_tower.push_back(new Tower(_mousePos->x, _mousePos->y, TowerCreated));
			metal = metal - GameManager::Get()->_modelStats[0][TowerLabel::buildingCost][TowerCreated][0];
			
			EventManager::Get()->AddArea(_mousePos->x, _mousePos->y, 100, 100, GameArea::TowerArea);
			EventManager::Get()->AddEvent(GameArea::Maps, sf::Event::EventType::MouseButtonPressed, &Upgrade);
			TowerCreated = -1;
		}
		
	}
};

void GameManager::MUpgrade(Tower latour)
{
	if(latour.canUpgrade() == false)
		return;

	if (money < GameManager::Get()->_modelStats[0][TowerLabel::cost][TowerCreated][0])
		return;

	latour.upgrade();
};

std::vector<Tower*>& GameManager::GetTowerList()
{
	return _o_tower;
};