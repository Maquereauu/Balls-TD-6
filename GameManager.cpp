#include "GameManager.h"
#include "GameObject.h"
#include "EventManager.h"
#include "Window.h"
#include "Bullet.h"



GameManager* GameManager::pInstance = nullptr;

void GameManager::Create()
{
	if (GameManager::pInstance != nullptr)
		return;

	GameManager::pInstance = new GameManager();
	GameManager::pInstance->Initialize();
}

void GameManager::Initialize() 
{
	
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
	_width = new int(1920);
	_height = new int(1080);
	_o_window = new Window(*_width, *_height);
	_window = _o_window->getWindow();
	_mousePos = new sf::Vector2i();
	_o_bullet = new std::vector<Bullet*>();

	//Game Area
	_entities.resize(GoLabel::total);
	GameObject* o_leftSide = new GameObject(*_width / 4, *_height, 0.f, 0.f, 0.f, GoLabel::border);
	GameObject* o_rigthSide = new GameObject(*_width / 4, *_height, (*_width / 4) * 3, 0.f, 0.f, GoLabel::border);
	GameObject* o_top = new GameObject((*_width / 4) * 2, *_height * 0.1, (*_width / 4), 0.f, 0.f, GoLabel::border);
	GameObject* o_restart = new GameObject(100, 100, 0, 0.f, 0.f, GoLabel::border);
	o_leftSide->getShape().setFillColor(sf::Color::Color(128, 128, 128, 255));
	o_rigthSide->getShape().setFillColor(sf::Color::Color(128, 128, 128, 255));
	o_top->getShape().setFillColor(sf::Color::Color(128, 128, 128, 255));
	o_restart->getShape().setFillColor(sf::Color::Green);
	_o_tower = new Tower();

	/*
	* INIT events
	*/

	EventManager::Get()->AddArea(*_width / 4.f, *_height * 0.1, (*_width / 4.f) * 3, *_height * 0.9, GameArea::Game);
	EventManager::Get()->AddArea(0, 0, 100, 100, GameArea::Restart);

	EventManager::Get()->AddEvent(GameArea::Game, sf::Event::EventType::MouseButtonPressed, &throwbullet);
	EventManager::Get()->AddEvent(GameArea::Game, sf::Event::EventType::MouseMoved, &movetower);
	EventManager::Get()->AddEvent(GameArea::Restart, sf::Event::EventType::MouseButtonPressed, &retry);
	EventManager::Get()->AddEvent(GameArea::Quit, sf::Event::EventType::Closed, &quit);
}
//
void GameManager::Mretry()
{
	// retire les bulletes en vie
	std::vector<GameObject*>().swap(_entities[GoLabel::bullet]);
	//_entities[GoLabel::bullet].clear();
	// retire les bricks en vie
	std::vector<GameObject*>().swap(_entities[GoLabel::brick]);
	//_entities[GoLabel::brick].clear();
	// ajoute les nouvelles bricks pour �tre en vie

}

void GameManager::Mquit()
{
	_window->close();
}

void GameManager::MthrowBullet()
{
	Math::Vector2 mouseVector = Math::Vector2::createVector(_o_tower->getPos(), _mousePos->x, _mousePos->y).getNormalizeVector();

	if (mouseVector.y < 0 && Math::Vector2::leftVector.getAngle(mouseVector) >= 10 && Math::Vector2::leftVector.getAngle(mouseVector) <= 170)
	{
		if (timer > 0.3)
		{
			for (int i = 0; i < _o_bullet->size(); i++)
			{
				if (std::find(_entities[GoLabel::bullet].begin(), _entities[GoLabel::bullet].end(), _o_bullet->at(i)) == _entities[GoLabel::bullet].end())
				{
					_o_bullet->at(i)->_isDestroyed = false;
					_o_bullet->at(i)->_side = "";
					_entities[GoLabel::bullet].push_back(_o_bullet->at(i));
					_o_tower->fire(mouseVector, _o_bullet->at(i));
					timer = o_timer.restart().asSeconds();;
					break;
				}
			}
		}
	}
}

void GameManager::MmoveTower()
{
	Math::Vector2 mouseVector = Math::Vector2::createVector(_o_tower->getPos(), _mousePos->x, _mousePos->y).getNormalizeVector();
	if (mouseVector.y < 0 && Math::Vector2::leftVector.getAngle(mouseVector) >= 15 && Math::Vector2::leftVector.getAngle(mouseVector) <= 165)
	{
		_o_tower->move(mouseVector);
	}
}

void GameManager::addToEntity(int iLabel, GameObject* o_gameObject)
{
	if (iLabel == -1)
		return;

	_entities[iLabel].push_back(o_gameObject);
}