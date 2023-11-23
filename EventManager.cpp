#include "EventManager.h"

EventManager* EventManager::pInstance = nullptr;

EventManager::EventManager() {
	//Initialize();
	//_dict[sf::Event::MouseButtonPressed] = &A;
	//_dict[sf::Event::Closed] = &B;
	//_dictmet[sf::Event::Closed] = &Cannon::cannonMove;
}


void A()
{
	//Cannon.Fire()
}

void B()
{
	//window.close en changeant une variable membre
}

void EventManager::CheckEvent(GameManager::GameArea area, sf::Event::EventType eventName) {
	if (_dict.find(area) != _dict.end() && _dict[area].find(eventName) != _dict[area].end()) {
		_dict[area][eventName]();
	}
}

void EventManager::Update(sf::RenderWindow* _window) {
	// update all
	sf::Event event;
	*GameManager::Get()->_mousePos = sf::Mouse::getPosition(*_window);
	while (_window->pollEvent(event))
	{
		for (int i = 0; i < m_oAreas.size(); i++)
		{
			if ((GameManager::_mousePos->x >= m_oAreas[i]._x && GameManager::Get()->_mousePos->x <= (m_oAreas[i]._width)) && (GameManager::Get()->_mousePos->y >= m_oAreas[i]._y && GameManager::Get()->_mousePos->y <= m_oAreas[i]._height))
			{
				CheckEvent(m_oAreas[i]._eGameArea, event.type);
				std::cout << Get()->_mousePos->x;
			}
			else {
				CheckEvent(GameManager::GameArea::Quit, event.type);
			}
		}
	}
}