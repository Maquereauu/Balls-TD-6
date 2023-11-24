#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "GameManager.h"

typedef void (*event)();

template<typename T>
void (T::* function)();

void A();
void B();



struct Area
{
	float _x;
	float _y;
	float _width;
	float _height;
	GameManager::GameArea _eGameArea;
	Area(float x, float y, float width, float height, GameManager::GameArea eGameArea)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		_eGameArea = eGameArea;
	}
};

class EventManager
{
private:
	static EventManager* pInstance;
	EventManager();

public:

	std::vector<Area> m_oAreas;
	std::map<int, std::map<sf::Event::EventType, event>> _dict;
	//std::map<sf::Event::EventType, function> _dictmet;

	static void Create()
	{
		if (pInstance != nullptr)
			return;

		pInstance = new EventManager();
	}

	static EventManager* Get()
	{
		return pInstance;
	}

	void AddEvent(GameManager::GameArea area, sf::Event::EventType eEventType, event oFunction)
	{
		_dict[area][eEventType] = oFunction;
	}

	void AddArea(float fX, float fY, float fWidth, float fHeight, GameManager::GameArea eGameArea)
	{
		m_oAreas.push_back(Area(fX, fY, fWidth, fHeight, eGameArea));
	}

	void CheckEvent(GameManager::GameArea area, sf::Event::EventType eventName);

	void Update(sf::RenderWindow* _window);
	std::vector<Area> GetAreaVector();
};

